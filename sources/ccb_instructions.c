#include <ccb_instructions.h>

// Helper functions
uint8_t get_uint8_from_vm(ccvm_vm_t* vm) {
    return vm->binary->buffer[vm->program_counter++];
}

uint32_t get_uint32_from_vm(ccvm_vm_t* vm) {
    uint32_t value = 0;
    value |= vm->binary->buffer[vm->program_counter] << 24;
    value |= vm->binary->buffer[vm->program_counter + 1] << 16;
    value |= vm->binary->buffer[vm->program_counter + 2] << 8;
    value |= vm->binary->buffer[vm->program_counter + 3];

    vm->program_counter += 4;
    return value;
}

// Instructions
void ccvm_ccb_instruction_exit(ccvm_vm_t* vm) {
    vm->is_running = 0;
}

void ccvm_ccb_instruction_mov_lit_to_reg(ccvm_vm_t* vm) {
    uint8_t register_id = get_uint8_from_vm(vm);
    uint32_t literal = get_uint32_from_vm(vm);
    
    vm->registers[register_id] = literal;
}

void ccvm_ccb_instruction_mov_reg_to_reg(ccvm_vm_t* vm) {
    uint8_t register_id_1 = get_uint8_from_vm(vm);
    uint8_t register_id_2 = get_uint8_from_vm(vm);
    
    vm->registers[register_id_1] = vm->registers[register_id_2];
}

// List of instructions
void (*ccvm_ccb_instructions[256])(ccvm_vm_t* vm) = {
    [0x00] = ccvm_ccb_instruction_exit,

    // Mov instructions
    [0x10] = ccvm_ccb_instruction_mov_lit_to_reg,
    [0x11] = ccvm_ccb_instruction_mov_reg_to_reg
};