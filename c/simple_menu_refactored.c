#include <stdio.h>
#include "commands.h"

int main() {
    char *cmd;
    char *par[MAX_COMMAND_PARAMETERS];
    uint8_t args;

    char buffer[MAX_INPUT_CHARACTERS];

    while(true) {
        printf("Enter a command :");
        scanf("%100s", buffer);

        if (process_buffer(&cmd, par, &args, buffer)) {
            continue;
        }

        printf("Command parsed %s.\n", cmd);

        execute_command(cmd, par, args);
    }

    return 0;
}
