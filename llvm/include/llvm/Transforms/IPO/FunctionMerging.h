//===- Transforms/FunctionMerging.h - function merging passes  ---*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
/// \file

//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_FUNCTION_MERGING_H
#define LLVM_TRANSFORMS_FUNCTION_MERGING_H

#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AssumptionCache.h"
#include "llvm/Analysis/DemandedBits.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include <llvm/Analysis/DependenceAnalysis.h>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Analysis/Passes.h"
#include "llvm/IR/PassManager.h"

#include "llvm/Transforms/Instrumentation.h"

namespace llvm {

class FunctionMerging : public ModulePass {
  StringSet<> AlwaysPreserved;
  bool shouldPreserveGV(const GlobalValue &GV);
  size_t mergeBySimilarity(Module &M, int Metrics);
  size_t mergeByPairwise(Module &M);

public:
  static char ID;
  FunctionMerging() : ModulePass(ID) {
    initializeFunctionMergingPass(*PassRegistry::getPassRegistry());
  }
  bool runOnModule(Module &M) override;
  void getAnalysisUsage(AnalysisUsage &AU) const override;
};

} // namespace llvm
#endif
