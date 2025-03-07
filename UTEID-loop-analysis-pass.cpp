
#include "UTEID-loop-analysis-pass.h"

using namespace llvm;

LoopA::Result LoopA::run(Function &F, FunctionAnalysisManager &FAM) {
  F.print(errs());
  static uint64_t counter = 0;
  errs() << "hey from analysis\n";
  errs() << "Function "<< F.getName() << " got: " << counter << "\n";
  // get the loop information analysis passes
  auto v = std::vector<uint64_t>();
  v.push_back(counter++);
  return v;
}

llvm::AnalysisKey LoopA::Key;

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------

llvm::PassPluginLibraryInfo getLoopAnaPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "UTEID-Loop-Analysis-Pass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
              [](StringRef Name, FunctionPassManager &FPM,
                 ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "print<UTEID-loop-ana-pass>") {
                  FPM.addPass(PrintLoopAna());
                  return true;
                }
                return false;
            });
            PB.registerAnalysisRegistrationCallback(
                [](FunctionAnalysisManager &FAM) {
                  FAM.registerPass([&] { return LoopA(); });
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLoopAnaPluginInfo();
}
