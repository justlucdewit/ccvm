#include <ccb_runner.h>

void ccvm_print_debug(ccvm_vm_t* vm) {
    printf("================================================\n");
    printf("=  VM Debug                                    =\n");
    printf("================================================\n");
    printf("Program counter: 0x%08X\n", vm->program_counter);
    printf("Registers:\n");
    for (int i = 0; i < 8; i++) {
        printf("  R%d: 0x%08X\n", i, vm->registers[i]);
    }

    printf("Stack:\n");
    for (int i = 0; i <= vm->stack->size; i++) {
        uint32_t val = ccvm_stack_pop(vm->stack);
        printf("  - 0x%.8X (%d)\n", val, val);
    }
}

void ccvm_run_bytecode(ccvm_binary_t* binary, bool debug) {
    // Create the VM
    ccvm_vm_t vm = {0};
    vm.binary = binary;
    vm.is_running = 1;
    vm.program_counter = 8;
    
    // Reset the registers
    memset(vm.registers, 0, sizeof(vm.registers));

    vm.stack = ccvm_stack_init();
    
    // Main loop
    while (vm.is_running) {
        // Get the opcode and increment the program counter
        uint8_t opcode = vm.binary->buffer[vm.program_counter++];

        // Get the instruction
        void (*instruction)(ccvm_vm_t* vm) = ccvm_ccb_instructions[opcode];

        if (instruction == NULL) {
            printf("Error: Unknown opcode 0x%02X", opcode);
            exit(1);
            return;
        }
        
        // Execute the instruction
        instruction(&vm);
    }

    if (debug)
        ccvm_print_debug(&vm);

    return;
}
