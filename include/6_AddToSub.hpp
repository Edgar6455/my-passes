#pragma once

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/FileSystem.h>

using namespace llvm;


struct AddToSub : public PassInfoMixin<AddToSub>
{
  PreservedAnalyses run(Module &M, ModuleAnalysisManager&);

  static bool isRequired() { return true; }
};


// Registration for new pass manager
PassPluginLibraryInfo getAddToSubPluginInfo();

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo()
{ return getAddToSubPluginInfo(); }

