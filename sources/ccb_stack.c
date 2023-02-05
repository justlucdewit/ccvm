#include <ccb_stack.h>

#define STACK_INIT_CAPACITY 64

ccb_stack_t* ccvm_stack_init() {
    ccb_stack_t* stack = malloc(sizeof(ccb_stack_t));
    stack->data = malloc(sizeof(uint32_t) * STACK_INIT_CAPACITY);
    stack->stack_pointer = 0;
    stack->stack_frame_pointer = 0;
    stack->size = 0;
    stack->capacity = STACK_INIT_CAPACITY;
    return stack;
}

void ccvm_stack_free(ccb_stack_t* stack) {
    free(stack->data);
    free(stack);
}

uint32_t ccvm_stack_pop(ccb_stack_t* stack) {
    if (stack->size == 0) {
        return 0;
    }

    stack->stack_pointer--;
    stack->size--;
    return stack->data[stack->stack_pointer];
}

void ccvm_stack_push(ccb_stack_t* stack, uint32_t value) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, sizeof(uint32_t) * stack->capacity);
    }
    
    stack->data[stack->stack_pointer] = value;
    stack->stack_pointer++;
    stack->size++;
}
