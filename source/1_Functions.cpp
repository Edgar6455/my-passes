#include "1_Functions.hpp"

using namespace llvm;


PreservedAnalyses FunctionsPass::run(Function &F, FunctionAnalysisManager&)
{
  errs() << "Found function: " << F.getName() << "\n";
  return PreservedAnalyses::all();
}


// Registration for new pass manager
PassPluginLibraryInfo getFunctionsPassPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "1_functions", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "1_functions") {
                      FPM.addPass(FunctionsPass());
                      return true;
                    }
                    return false;
                });
  }};
}
