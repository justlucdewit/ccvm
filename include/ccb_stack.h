#ifndef CCVM_CCB_STACK_H
#define CCVM_CCB_STACK_H

#include <stdint.h>
#include <stdlib.h>

typedef struct ccb_stack {
    uint32_t* data;
    size_t stack_pointer;
    size_t stack_frame_pointer;
    size_t size;
    size_t capacity;
} ccb_stack_t;

/// Initializes a new stack
/// \return A pointer to the new stack
ccb_stack_t* ccvm_stack_init();

/// Frees the given stack
/// \param stack The stack to free
void ccvm_stack_free(ccb_stack_t* stack);

/// Pops a value from the stack
/// \param stack The stack to pop from
void ccvm_stack_pop(ccb_stack_t* stack);

/// Pushes a value to the stack
/// \param stack The stack to push to
/// \param value The value to push
void ccvm_stack_push(ccb_stack_t* stack, uint32_t value);


#endif // CCVM_CCB_STACK_H