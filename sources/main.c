// Libc headers
#include <stdio.h>

// Custom headers
#include <cmdparser.h>
#include <ccb_loader.h>
#include <ccb_runner.h>

static cmdp_action_t callback_function(cmdp_process_param_st *params);

static struct
{
    bool b;
    bool h;
    bool d;
    char* f;
} arg = {0};


static cmdp_command_st g_command = {
    .doc = "CC Virtual Machine, Bytecode interpreter for .ccb files.\nUsage: ccvm -f test.ccb\n\n",
    .options =
        (cmdp_option_st[]){
            {'b', "bytecode", "Display loaded bytecode for debugging", CMDP_TYPE_BOOL, &arg.b},
            {'h', "help", "Show this help screen", CMDP_TYPE_BOOL, &arg.h},
            {'f', "file", "File to load", CMDP_TYPE_STRING_PTR, &arg.f},
            {'d', "Debug", "Show ending state of the VM after exiting", CMDP_TYPE_BOOL, &arg.d},
            {0},
        },
    .fn_process = callback_function,
};

int main(int argc, char **argv) {
    return cmdp_run(argc - 1, argv + 1, &g_command, NULL);
}


static cmdp_action_t callback_function(cmdp_process_param_st *params) {
    if (params->opts == 0 || arg.h || arg.f == NULL)
        return CMDP_ACT_SHOW_HELP;
    
    // Create, print, and free the binary from test.ccb
    ccvm_binary_t* bin_exe = ccvm_binary_load(arg.f);
    if (bin_exe == NULL) {
        return 1;
    }

    if (arg.b)
        ccvm_binary_print(bin_exe);

    ccvm_run_bytecode(bin_exe, arg.d);

    ccvm_binary_free(bin_exe);

    return CMDP_ACT_OK;
}