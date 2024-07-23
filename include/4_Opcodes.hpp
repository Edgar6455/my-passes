#pragma once

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;


struct OpcodesPass : public PassInfoMixin<OpcodesPass>
{
  PreservedAnalyses run(Function &F, FunctionAnalysisManager&);

  static bool isRequired() { return true; }
};


// Registration for new pass manager
PassPluginLibraryInfo getOpcodesPassPluginInfo();

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo()
{ return getOpcodesPassPluginInfo(); }

