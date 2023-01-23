#ifndef CCVM_CCB_RUNNER_H
#define CCVM_CCB_RUNNER_H

#include <stdio.h>

#include <cmdparser.h>
#include <ccb_loader.h>
#include <ccb_instructions.h>
#include <ccb_vm.h>

/// Runs the bytecode in the given binary
/// \param binary The binary to run
/// \param debug Whether to print debug information after running
void ccvm_run_bytecode(ccvm_binary_t* binary, bool debug);

#endif // CCVM_CCB_RUNNER_H