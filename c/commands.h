#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_COMMAND_CHARACTERS 6
#define MAX_COMMAND_PARAMETERS 5
#define FIELD_SEPERATOR        ","
#define MAX_INPUT_CHARACTERS   100

void print_help_menu();
void print_button_command();
void print_led_command(char *parameters[], __uint8_t args);
bool process_buffer(char **command, char *parameters[], __uint8_t *args, char *buffer);
void execute_command(char *cmd, char *par[], uint8_t args);

#endif // COMMANDS_H
