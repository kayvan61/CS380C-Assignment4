#pragma once

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"

  
struct LoopA : public llvm::AnalysisInfoMixin<LoopA> {
  using Result = std::vector<uint64_t>;
  // Main entry point, takes IR unit to run the pass on (&F) and the
  // corresponding pass manager (to be queried if need be)
  Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

private:
   static llvm::AnalysisKey Key;
   friend struct llvm::AnalysisInfoMixin<LoopA>;
};

struct PrintLoopAna: public llvm::PassInfoMixin<PrintLoopAna> {
    llvm::PreservedAnalyses run(llvm::Function& F, llvm::FunctionAnalysisManager& FAM) {
        auto& a = FAM.getResult<LoopA>(F);
        llvm::errs() << a.front() << "\n";
        return llvm::PreservedAnalyses::all();
    }
};
 
