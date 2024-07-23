#include "3_InstructionsInBB.hpp"

using namespace llvm;


PreservedAnalyses InstructionsInBB::run(Function &F, FunctionAnalysisManager&)
{
  errs() << "Function: " << F.getName() << "\n";

  for (const BasicBlock &BB : F)
  {
    errs() << "  Basic Block: " << BB.getName() << "\n";
    for (const Instruction &I : BB)
      errs() << "    Instruction: " << I << "\n";
  }

  return PreservedAnalyses::all();
}


// Registration for new pass manager
PassPluginLibraryInfo getInstructionsInBBPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "3_instructions-in-bb", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "3_instructions-in-bb") {
                      FPM.addPass(InstructionsInBB());
                      return true;
                    }
                    return false;
                });
  }};
}
