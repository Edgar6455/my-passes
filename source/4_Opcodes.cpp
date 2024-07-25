#include "4_Opcodes.hpp"

using namespace llvm;


PreservedAnalyses OpcodesPass::run(Function &F, FunctionAnalysisManager&)
{
  errs() << "Function: " << F.getName() << "\n";

  for (const BasicBlock &BB : F)
  {
    for (const Instruction &I : BB)
    {
      if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
        errs() << "    Opcode: " << I << "\n";
      }
    }
  }

  return PreservedAnalyses::all();
}


// Registration for new pass manager
PassPluginLibraryInfo getOpcodesPassPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "4_opcodes", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "4_opcodes") {
                      FPM.addPass(OpcodesPass());
                      return true;
                    }
                    return false;
                });
  }};
}
