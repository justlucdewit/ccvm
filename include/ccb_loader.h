#ifndef CCVM_CCB_LOADER_H
#define CCVM_CCB_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

typedef struct ccvm_binary {
    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    uint8_t* buffer;
    size_t buffer_size;
} ccvm_binary_t;

/// @brief Function that takes a path to a CCVM binary and loads it into ccvm_binary_t struct
/// @param path the path to the binary file (.ccb file)
/// @return a ccvm_binary_t struct containing the binary data
ccvm_binary_t* ccvm_binary_load(char* path);

/// @brief Function that frees the memory allocated for a ccvm_binary_t struct
/// @param binary the binary to free
void ccvm_binary_free(ccvm_binary_t* binary);

/// @brief Function that prints the contents of a ccvm_binary_t struct
/// @param binary the binary to print
void ccvm_binary_print(ccvm_binary_t* binary);

#endif // CCVM_CCB_LOADER_H