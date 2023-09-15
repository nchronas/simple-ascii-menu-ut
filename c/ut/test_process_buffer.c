#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

// Include your source file
#include "../commands.h"

void test_process_buffer() {
    char *command;
    char *parameters[MAX_COMMAND_PARAMETERS];
    uint8_t args;

    // Test case 1: Valid input with one argument
    char buffer1[] = "led,on";
    process_buffer(&command, parameters, &args, buffer1);
    assert(strcmp(command, "led") == 0);
    assert(strcmp(parameters[0], "on") == 0);
    assert(args == 1);

    // Test case 2: Valid input with multiple arguments
    char buffer2[] = "led,blink,5";
    process_buffer(&command, parameters, &args, buffer2);
    assert(strcmp(command, "led") == 0);
    assert(strcmp(parameters[0], "blink") == 0);
    assert(strcmp(parameters[1], "5") == 0);
    assert(args == 2);

    // Test case 3: Empty input
    char buffer3[] = "";
    assert(process_buffer(&command, parameters, &args, buffer3) == true);

    // Test case 4: No arguments
    char buffer4[] = "button";
    process_buffer(&command, parameters, &args, buffer4);
    assert(strcmp(command, "button") == 0);
    assert(args == 0);

    // Test case 5: Invalid input (no command)
    char buffer5[] = ",on";
    assert(process_buffer(&command, parameters, &args, buffer5) == true);
}

int main() {
    test_process_buffer();
    return 0;
}
