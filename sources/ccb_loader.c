#include <ccb_loader.h>

#define CCVM_MAGIC_NUMBER 0xDEADBEEF
#define CCVM_VERSION_MAJOR 0x0001
#define CCVM_VERSION_MINOR 0x0000

void SwapBytes(void *pv, size_t n)
{
    char *p = pv;
    size_t lo, hi;
    for(lo=0, hi=n-1; hi>lo; lo++, hi--)
    {
        char tmp=p[lo];
        p[lo] = p[hi];
        p[hi] = tmp;
    }
}

ccvm_binary_t* ccvm_binary_load(char* path) {
    // Open the file
    FILE* file = fopen(path, "rb");

    // Check if the file exists
    if (file == NULL) {
        printf("File '%s' could not be opened", path);
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);

    // Allocate memory for the binary
    ccvm_binary_t* binary = malloc(sizeof(ccvm_binary_t));
    binary->buffer = malloc(file_size);

    // Read the file into memory
    fseek(file, 0, SEEK_SET);
    fread(binary->buffer, file_size, 1, file);

    // Set the binary properties
    // - Magic number is the first 4 bytes
    // - Version major is the next 2 bytes
    // - Version minor is the next 2 bytes
    // - Buffer is the rest of the file
    // Read them in reverse order because of little endian
    binary->magic_number = *(uint32_t*)binary->buffer;
    binary->version_major = *(uint16_t*)(binary->buffer + 4);
    binary->version_minor = *(uint16_t*)(binary->buffer + 6);
    binary->buffer_size = file_size;

    SwapBytes(&binary->magic_number, sizeof(binary->magic_number));
    SwapBytes(&binary->version_major, sizeof(binary->version_major));
    SwapBytes(&binary->version_minor, sizeof(binary->version_minor));

    // Check if the magic number is correct
    // printf("test %X", binary->magic_number);
    if (binary->magic_number != CCVM_MAGIC_NUMBER) {
        printf("File '%s' is not a valid CCVM binary, magicnumber should be '0xDEADBEEF' but is '0x%X'", path, binary->magic_number);
        return NULL;
    }

    // Check if the version is supported
    if (binary->version_major != CCVM_VERSION_MAJOR || binary->version_minor != CCVM_VERSION_MINOR) {
        printf("File '%s' is not a supported version for CCVM %i.%i", path, CCVM_VERSION_MAJOR, CCVM_VERSION_MINOR);
        return NULL;
    }

    fclose(file);
    return binary;
}

void ccvm_binary_free(ccvm_binary_t* binary) {
    free(binary->buffer);
    free(binary);
}

void print_binary_buffer(uint8_t* buffer, size_t buffer_size) {
    uint32_t i = 0;
    char ascii_buffer[17] = {0};

    for (i = 0; i < buffer_size; i++) {
        // Print the address
        if (i % 16 == 0) {
            printf("%08X    ", i);
        }

        // Put char in buffer
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            ascii_buffer[i % 16] = buffer[i];
        } else {
            ascii_buffer[i % 16] = '.';
        }

        printf("%.2X ", buffer[i]);

        // Print a space every 4 bytes
        if ((i + 1) % 8 == 0) {
            printf(" ");
        }

        // Print a new line every 16 bytes
        if ((i + 1) % 16 == 0) {
            printf(" %s\n", ascii_buffer);

            // Reset the ascii buffer
            memset(ascii_buffer, 0, 17);
        }
    }

    // Fill the rest of the line with spaces
    while (i % 16 != 0) {
        printf("   ");

        // Print a space every 4 bytes
        if ((i + 1) % 8 == 0) {
            printf(" ");
        }

        i++;
    }

    printf(" %s\n", ascii_buffer);
}

void ccvm_binary_print(ccvm_binary_t* binary) {
    printf("ccvm_binary_t @ 0x%X:\n", binary);
    printf("\tmagic_number: 0x%X\n", binary->magic_number);
    printf("\tversion_major: %i\n", binary->version_major);
    printf("\tversion_minor: %i\n", binary->version_minor);
    printf("\tbuffer_size: %i\n", binary->buffer_size);

    // Print the buffer
    printf("\tbuffer: \n\n");
    print_binary_buffer(binary->buffer, binary->buffer_size);
}