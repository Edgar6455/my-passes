#include "6_AddToSub.hpp"

using namespace llvm;

PreservedAnalyses AddToSub::run(Module &M, ModuleAnalysisManager&)
{
  bool Modified = false;

  for (Function& F : M)
  {
    bool functionMessage = false;

    for (BasicBlock& BB : F)
    {
      for (auto Inst = BB.begin(), IE = BB.end(); Inst != IE; ++Inst)
      {
        // Skip if not a binary operator
        auto *BinOp = dyn_cast<BinaryOperator>(Inst);
        if (!BinOp)
          continue;

        // Skip if not an instruction add with integer type
        unsigned Opcode = BinOp->getOpcode();
        if (Opcode != Instruction::Add || !BinOp->getType()->isIntegerTy())
          continue;

        IRBuilder<> Builder(BinOp);

        // Create an instruction representing (a - b)
        BinaryOperator *NewValue = BinaryOperator::CreateSub(
          BinOp->getOperand(0),
          BinOp->getOperand(1)
        );

        // Preserve the `nsw` flag if it is set on the `Add` instruction
        if (BinOp->hasNoSignedWrap())
          NewValue->setHasNoSignedWrap(true);

        if (!functionMessage)
        {
          errs() << "In function " << F.getName() << ":\n";
          functionMessage = true;
        }
        errs() << *BinOp << " -> " << *NewValue << "\n";

        // Replace (a + b) with (a - b)
        ReplaceInstWithInst(&BB, Inst, NewValue);
        Modified = true;
      }
    }
  }

  // Define the output file path
  std::string outputFilePath = "output-for-add-to-sub.ll";

  // Write the modified module to a new LLVM IR text file
  std::error_code EC;
  raw_fd_ostream OS(outputFilePath, EC, sys::fs::OF_None);
  if (EC) {
    errs() << "Error opening file: " << EC.message() << "\n";
    return PreservedAnalyses::all();
  }

  // Print the module to the file in LLVM IR format
  M.print(OS, nullptr);

  return Modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}

// Registration for new pass manager
PassPluginLibraryInfo getAddToSubPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "6_add-to-sub", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "6_add-to-sub") {
                      MPM.addPass(AddToSub());
                      return true;
                    }
                    return false;
                });
  }};
}
