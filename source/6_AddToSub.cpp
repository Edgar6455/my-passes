#include "6_AddToSub.hpp"

using namespace llvm;


PreservedAnalyses AddToSub::run(Function &F, FunctionAnalysisManager&)
{
  bool Modified = false;
  bool functionMessage = false;

  for (BasicBlock &BB : F)
  {
    for (auto Inst = BB.begin(), IE = BB.end(); Inst != IE; ++Inst)
    {
      // Skip if not an binary operator
      auto *BinOp = dyn_cast<BinaryOperator>(Inst);
      if (!BinOp)
        continue;

      // Skip if not an instruction add with integer type
      unsigned Opcode = BinOp->getOpcode();
      if (Opcode != Instruction::Add || !BinOp->getType()->isIntegerTy())
        continue;


      IRBuilder<> Builder(BinOp);

      // Create an instruction representing (a - (~b + 1))
      Instruction *NewValue = BinaryOperator::CreateSub(
        BinOp->getOperand(0),
        Builder.CreateAdd(
          Builder.CreateNot(BinOp->getOperand(1)),
          ConstantInt::get(BinOp->getType(), 1)
          )
        );

      if (!functionMessage)
      {
        errs() << "In function " << F.getName() << ":\n";
        functionMessage = true;
      }
      errs() << *BinOp << " -> " << *NewValue << "\n";

      // Replace (a + b) with (a - (~b + 1))
      ReplaceInstWithInst(&BB, Inst, NewValue);
      Modified = true;
    }
  }

  return Modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}


// Registration for new pass manager
PassPluginLibraryInfo getAddToSubPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "6_add-to-sub", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "6_add-to-sub") {
                      FPM.addPass(AddToSub());
                      return true;
                    }
                    return false;
                });
  }};
}
