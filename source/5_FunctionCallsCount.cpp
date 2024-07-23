#include "5_FunctionCallsCount.hpp"

using namespace llvm;


PreservedAnalyses FunctionCallsCount::run(Function &F, FunctionAnalysisManager&)
{
  unsigned FunctionCallCount = 0;

  for (const BasicBlock &BB : F)
  {
    for (const Instruction &I : BB)
    {
      // Check if the instruction is a call instruction
      if (const CallInst *CI = dyn_cast<CallInst>(&I))
        ++FunctionCallCount;
    }
  }

  // Print the function name and the count of direct function calls
  errs() << "Function: " << F.getName() << ", Direct Function Call Count: " << FunctionCallCount << "\n";

  return PreservedAnalyses::all();
}


// Registration for new pass manager
PassPluginLibraryInfo getFunctionCallsCountPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "5_function-calls-count", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "5_function-calls-count") {
                      FPM.addPass(FunctionCallsCount());
                      return true;
                    }
                    return false;
                });
  }};
}