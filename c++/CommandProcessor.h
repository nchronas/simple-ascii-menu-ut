#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <iostream>
#include <vector>

#define MAX_COMMAND_CHARACTERS 6
#define MAX_COMMAND_PARAMETERS 5
#define FIELD_SEPARATOR        ","
#define MAX_INPUT_CHARACTERS   100

class CommandProcessor {
private:
    std::string cmd;
    std::vector<std::string> par;

public:
    void print_help_menu();
    void print_button_command();
    void print_led_command();
    bool process_buffer(const std::string& buffer);

    std::string get_command() const {
        return cmd;
    }

    std::vector<std::string> get_parameters() const {
        return par;
    }

    bool has_parameters() const {
        return !par.empty();
    }
};

#endif // COMMAND_PROCESSOR_H
