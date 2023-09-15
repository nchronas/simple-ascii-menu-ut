#include "CommandProcessor.h"
#include <cstdlib>

void CommandProcessor::print_help_menu() {
    std::cout << "This is where a description of the commands would be" << std::endl;
}

void CommandProcessor::print_button_command() {
    int pressed = rand() % 2;
    std::cout << "Button status: " << (pressed ? "pressed" : "Not pressed") << std::endl;
}

void CommandProcessor::print_led_command() {
    if(par.empty()) {
        std::cout << "Led command wrong parameters" << std::endl;
        return;
    }

    if (par[0] == "on") {
        std::cout << "Led is on" << std::endl;
    } else if (par[0] == "off") {
        std::cout << "Led is off" << std::endl;
    } else if (par[0] == "blink") {
        if (par.size() != 2) {
            std::cout << "Led blinking command wrong parameters" << std::endl;
        } else {
            std::cout << "Led is blinking with " << par[1] << " Hz" << std::endl;
        }
    } else {
        std::cout << "Led command wrong parameters" << std::endl;
    }
}

bool CommandProcessor::process_buffer(const std::string& buffer) {
    if (buffer.empty()) {
        return true;
    }

    size_t pos = buffer.find(FIELD_SEPARATOR);
    cmd = buffer.substr(0, pos);

    if (pos != std::string::npos) {
        par.clear();
        std::string rest = buffer.substr(pos + 1);

        while ((pos = rest.find(FIELD_SEPARATOR)) != std::string::npos) {
            par.push_back(rest.substr(0, pos));
            rest.erase(0, pos + 1);
        }

        if (!rest.empty()) {
            par.push_back(rest);
        }
    }

    std::cout << "Command " << cmd << " parsed with " << par.size() << " arguments" << std::endl;

    return false;
}
