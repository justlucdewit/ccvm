#ifndef CCVM_CCB_INSTRUCTIONS_H
#define CCVM_CCB_INSTRUCTIONS_H

#include <ccb_vm.h>
#include <ccb_runner.h>

#include <stdio.h>
#include <stdlib.h>

/// @brief Opcode 0x00 Exit the VM
/// @param vm virtual machine struct
void ccvm_ccb_instruction_exit(ccvm_vm_t* vm);

/// @brief Opcode 0x10 Move literal to register
/// @param vm virtual machine struct
void ccvm_ccb_instruction_mov_lit_to_reg(ccvm_vm_t* vm);

/// @brief Opcode 0x11 Move register to register
/// @param vm virtual machine struct
void ccvm_ccb_instruction_mov_reg_to_reg(ccvm_vm_t* vm);

/// @brief Opcode 0x12 Push literal to stack
/// @param vm virtual machine struct
void ccvm_ccb_instruction_push_lit_to_stack(ccvm_vm_t* vm);

/// @brief Opcode 0x13 Push register to stack
/// @param vm virtual machine struct
void ccvm_ccb_instruction_push_reg_to_stack(ccvm_vm_t* vm);

/// @brief Opcode 0x14 Pop from stack to register
/// @param vm virtual machine struct
void ccvm_ccb_instruction_pop_stack_to_reg(ccvm_vm_t* vm);

/// The list of instructions
void (*ccvm_ccb_instructions[256])(ccvm_vm_t* vm);

#endif // CCVM_CCB_INSTRUCTIONS_H