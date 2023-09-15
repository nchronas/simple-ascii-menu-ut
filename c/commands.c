#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_help_menu() {
    printf("This is where a description of the commands would be\n");
}

void print_button_command() {
    int pressed = rand() % 2;
    printf("Button status: %s\n", pressed ? "pressed" : "Not pressed");
}

void print_led_command(char *parameters[], __uint8_t args) {
    if (args == 0) {
        printf("Led command wrong parameters\n");
        return;
    }

    if (strncmp("on", parameters[0], 5) == 0) {    
        printf("Led is on\n");
    } else if (strncmp("off", parameters[0], 5) == 0) {
        printf("Led is off\n");
    } else if (strncmp("blink", parameters[0], 5) == 0) {
        if (args != 2) {
            printf("Led blinking command wrong parameters\n");
        }
        printf("Led is blinking with %s Hz\n", parameters[1]);
    } else {
        printf("Led command wrong parameters\n");
    }
} 

bool process_buffer(char **command, char *parameters[], __uint8_t *args, char *buffer) {
    char *rest;

    if (buffer == NULL || strlen(buffer) == 0) {
        return true;
    }

    *command = strtok_r(buffer, FIELD_SEPERATOR, &rest);
    if (strlen(*command) == 0) {
        return true;
    }
    *args = 0;

    for (int i = 0; i < MAX_COMMAND_PARAMETERS; i++) {
        parameters[i] = strtok_r(rest, FIELD_SEPERATOR, &rest);
        if (parameters[i] == NULL) {
            break;
        }
        (*args)++;
    }
    printf("Command %s parsed with %d arguments\n", *command, *args);

    return false;
}

void execute_command(char *cmd, char *par[], uint8_t args) {
    if (strncmp("help", cmd, MAX_COMMAND_CHARACTERS) == 0) {
        if (args != 0) {
            printf("Command %s wrong arguments\n", cmd);
            return;
        }
        print_help_menu();
        printf("Command %s finished\n", cmd);
    } else if (strncmp("led", cmd, MAX_COMMAND_CHARACTERS) == 0) {
        print_led_command(par, args);
        printf("Command %s finished\n", cmd);
    } else if (strncmp("button", cmd, MAX_COMMAND_CHARACTERS) == 0) {
        if (args != 0) {
            printf("Command %s wrong arguments\n", cmd);
            return;
        }
        print_button_command();
        printf("Command %s finished\n", cmd);
    } else {
        printf("Command not found\n");
    }
}
