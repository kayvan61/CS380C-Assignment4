#include "UTEID-loop-opt-pass.h"

PreservedAnalyses LoopPass::run(Function &F, FunctionAnalysisManager &FAM) {
  errs() << "hey from opt ;)\n";
  // get the loop information analysis passes
  auto& li = FAM.getResult<LoopAnalysis>(F);
  LoopA::Result& temp = FAM.getResult<LoopA>(F);

  int counter = 0;
  Value* instr_to_move = nullptr;
  for(auto& BB: F) {
    for(auto& I: BB) {
      if(++counter == 3) {
        instr_to_move = &I;
        goto e;
      }
    }
    if(counter == 3) {
      break;
    }
  }
 e:
  instr_to_move->print(errs());
  dyn_cast<Instruction>(instr_to_move)->removeFromParent();
  errs() << "\n";
  
  counter = 0;
  for(auto& BB: F) {
    for(auto& I: BB) {
      if(++counter == 4) {
        dyn_cast<Instruction>(instr_to_move)->insertAfter(&I);
        goto done;
      }
    }
    if(counter == 3) {
      break;
    }
  }
 done:
  errs() << "Function "<< F.getName() << " got: " << temp.front() << " in opt from analysisMan\n";
  return PreservedAnalyses::all();
}

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getLoopOptPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "UTEID-Loop-Opt-Pass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "UTEID-loop-opt-pass") {
		                FPM.addPass(LoopSimplifyPass());
                    FPM.addPass(LoopPass());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLoopOptPluginInfo();
}
