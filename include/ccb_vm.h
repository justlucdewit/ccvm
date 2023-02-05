#ifndef CCVM_CCB_VM_H
#define CCVM_CCB_VM_H

#include <ccb_loader.h>
#include <ccb_stack.h>

typedef struct ccvm_vm {
    ccvm_binary_t* binary;
    char is_running;
    size_t program_counter;
    uint32_t registers[8];
    ccb_stack_t* stack;
} ccvm_vm_t;

#endif