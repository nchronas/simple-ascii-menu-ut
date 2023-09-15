#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdint.h>
#include <cmocka.h>
#include "../commands.h"

void test_execute_command_help(void **state) {
    (void) state; // Unused parameter

    // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    execute_command("help", NULL, 0);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "This is where a description of the commands would be\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}


void test_execute_command_led_on(void **state) {
    (void) state; // Unused parameter

    // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    char *parameters[] = {"on"};
    execute_command("led", parameters, 1);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Led is on\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

void test_execute_command_led_off(void **state) {
    (void) state; // Unused parameter

    // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    char *parameters[] = {"off"};
    execute_command("led", parameters, 1);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Led is off\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

void test_execute_command_led_blink(void **state) {
    (void) state; // Unused parameter

    // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    char *parameters[] = {"blink", "5"};
    execute_command("led", parameters, 2);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Led is blinking with 5 Hz\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

void test_execute_command_button(void **state) {
    (void) state; // Unused parameter

    // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    execute_command("button", NULL, 0);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Button status: pressed\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

void test_execute_command_unknown_command(void **state) {
    (void) state; // Unused parameter

    // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    execute_command("unknown", NULL, 0);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Command not found\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

void test_execute_command_led_blink_invalid(void **state) {
    (void) state; // Unused parameter

     // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    char *parameters[] = {"blink"};
    execute_command("led", parameters, 1);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Led blinking command wrong parameters\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

void test_execute_command_led_invalid(void **state) {
    (void) state; // Unused parameter

     // Redirect stdout to a file for testing
    FILE *fake_stdout = freopen("test_output.txt", "w", stdout);
    assert_non_null(fake_stdout);

    char *parameters[] = {"invalid"};
    execute_command("led", parameters, 1);

    // Close the file and reopen stdout
    fclose(fake_stdout);
    freopen("/dev/tty", "w", stdout);

    // Read the contents of the file
    FILE *output_file = fopen("test_output.txt", "r");
    assert_non_null(output_file);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), output_file);

    // Check the output
    char expected[] = "Led command wrong parameters\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_execute_command_help),
        cmocka_unit_test(test_execute_command_led_on),
        cmocka_unit_test(test_execute_command_led_off),
        cmocka_unit_test(test_execute_command_led_blink),
        cmocka_unit_test(test_execute_command_button),
        cmocka_unit_test(test_execute_command_unknown_command),

        cmocka_unit_test(test_execute_command_led_blink_invalid),
        cmocka_unit_test(test_execute_command_led_invalid),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
