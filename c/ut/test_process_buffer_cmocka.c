#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../commands.h"

void test_process_buffer_valid_input(void **state) {
    (void) state; // Unused parameter

    char *command;
    char *parameters[MAX_COMMAND_PARAMETERS];
    uint8_t args;
    char buffer[MAX_INPUT_CHARACTERS];

    // Test a valid input buffer
    strcpy(buffer, "led,on,5");
    bool result = process_buffer(&command, parameters, &args, buffer);

    // Check the result
    assert_true(result == false);  // The function should return false for valid input
    assert_string_equal(command, "led");
    assert_int_equal(args, 2);
    assert_string_equal(parameters[0], "on");
    assert_string_equal(parameters[1], "5");
}

void test_process_buffer_empty_input(void **state) {
    (void) state; // Unused parameter

    char *command = NULL;
    char *parameters[MAX_COMMAND_PARAMETERS];
    uint8_t args;
    char buffer[MAX_INPUT_CHARACTERS];

    // Test an empty input buffer
    strcpy(buffer, "");
    bool result = process_buffer(&command, parameters, &args, buffer);

    // Check the result
    assert_true(result == true);  // The function should return true for an empty input
    assert_null(command);
    assert_int_equal(args, 0);
    assert_null(parameters[0]);
}

void test_process_buffer_invalid_input(void **state) {
    (void) state; // Unused parameter

    char *command;
    char *parameters[MAX_COMMAND_PARAMETERS];
    uint8_t args;
    char buffer[MAX_INPUT_CHARACTERS];

    // Test an invalid input buffer
    strcpy(buffer, "invalid,,input");
    bool result = process_buffer(&command, parameters, &args, buffer);

    // Check the result
    assert_true(result == false);  // The function should return false for invalid input
    assert_string_equal(command, "invalid");
    assert_int_equal(args, 1);  // No valid arguments
    assert_string_equal(parameters[0], "input");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_process_buffer_valid_input),
        cmocka_unit_test(test_process_buffer_empty_input),
        cmocka_unit_test(test_process_buffer_invalid_input),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
