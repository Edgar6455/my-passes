#include "2_BasicBlocksCount.hpp"

using namespace llvm;


PreservedAnalyses BasicBlocksCount::run(Function &F, FunctionAnalysisManager&)
{
  errs() << "Function name: " << F.getName() << "\n";

    int BBCount = 0;
    for (auto& BB : F)
      ++BBCount;

  errs() << "  Basic blocks count: " << BBCount << "\n";

  return PreservedAnalyses::all();
}


// Registration for new pass manager
PassPluginLibraryInfo getBasicBlocksCountPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "2_basic-blocks-count", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "2_basic-blocks-count") {
                      FPM.addPass(BasicBlocksCount());
                      return true;
                    }
                    return false;
                });
  }};
}
