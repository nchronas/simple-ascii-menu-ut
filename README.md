# simple-ascii-menu-ut

<strong>TL/DR</strong> MGenerating unit tests with chatGPT for existing code


In the [previous article](), one of ChatGPT suggestions for improving the project was adding unit testing. So I will try to do that.

While I have experience in C, using [ceedling]() and [CMocka](), the other languages are unkown for me, so let's see what ChatGPT will suggest.

You can find the chatGPT chat link for the C code [here](https://chat.openai.com/share/08c308e7-a5ce-4313-a0e1-9883679e39c5)

You can find the chatGPT chat link for the Python code [here](https://chat.openai.com/share/0dd2d87d-97cd-4b9e-a389-21482f28b5ef)

# During development

## C language

### Refactoring

When I asked to create the unit test, for my suprised, chatGPT suggested to refactor the code and to remove functionality from main and put it into a function.

> First, you'll need to refactor your code a bit to make it more testable. Specifically, you should move the logic out of the main function and into  separate functions. This will allow you to test each function independently.


``` c
// Include headers...

void print_help_menu() {
    // ... unchanged
}

void print_button_command() {
    // ... unchanged
}

void print_led_command(char *parameters[], __uint8_t args) {
    // ... unchanged
}

bool process_buffer(char **command, char *parameters[], __uint8_t *args, char *buffer) {
    // ... unchanged
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
```

### First standalone test for process_buffer function

After the refactor happened, I asked ChatGPT to create tests for the process buffer. In the first question it created a generic code but afterwards I asked to add it's own scenarios. Investigating the scenarios, I think it did a good job covering all major areas. It gave a choice between 2 answers. The first answer was correct but the 2nd one used functions from cmocka even if it said that it was created for standalone.

#### Standalone

Running the first standalone test, you will see that the fifth test fails. The test checks for an input string without the command (",on") and  the scenario is completely valid, after a small search I saw that this is a limitation of the strtok. And that's the reason you should do unit test. I learned something more today.

#### cmocka

In the previous test, it created standalone tests, but it also mentioned the possibilty to use cmocka, a testing framework for C. So I thought to give it a try and generate code for cmocka. I asked how to install cmocka for my system and it worked perfectly, it even provided the github link. Trying to compile the unit test I encounter 2 issues, one that the stdint library header was missing and the 2nd was that cmocka needed to be exported to PATH. In both of these cases I asked ChatGPT to fix it and it did with the first try.

In the beginning 2 tests failed. The first one was the "empty_input" and it failed due to not initializing the command variable in the test. It was straightforward to fix. The 2nd failed test were in the "test_process_buffer_invalid_input" test. The interesting part is that the test was correct and my code wasn't. This was due to the strtok limitation that I explained above.

### instructions for adding cmocka from chatGPT

When I asked chatGPT to give me instructions for installing cmocka I got a comprehensive response (ommited some steps for readabilty): 

> To add CMocka to your system, you'll need to download and install it. Here are the steps you can follow:

 > 1. **Download CMocka**:

   > Visit the CMocka GitHub page: [https://github.com/clibs/cmocka](https://github.com/clibs/cmocka)

   > You can download the source code as a ZIP archive or use `git` to clone the repository.

   ```bash
   git clone https://github.com/clibs/cmocka.git
   ```

 > 2. **Build and Install CMocka**:

  > Once you have the source code, navigate to the CMocka directory in your terminal.

   ```bash
   cd cmocka
   ```

  > Build and install the library. If you're on Linux or macOS, you can use the following commands:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   ```

> 4. **Link Against CMocka in Your Project**:

 >  To use CMocka in your own projects, include the `cmocka.h` header file in your test files and link against the CMocka library when compiling.

 >  For example:

   ```bash
   gcc -o my_test my_test.c -lcmocka
   ```

 >  In this command, `my_test.c` is the name of your test file. The `-lcmocka` flag tells the compiler to link against the CMocka library.

> Remember that this is a basic overview of the process. Depending on your operating system and development environment, there might be slight differences in the installation process. Always refer to the official documentation or resources specific to your setup for the most accurate instructions.

### Tests for execute_command function

Finally I asked to create tests for the execute_command function with cmocka. The generated tests covered most of the issues besides inputing wrong number of arguments for the led command. When I asked to add these tests, it covered all issues. Again the compilation failed due to missing library headers of 
stdio and stdint and forgotten to copy paste one test. It also had an issue of handling the stdout as a way to test the correct functionality. I got an alternative from chatGPT that worked, I only had to do some small modifications. Overall it was a simple fix and in any case in a production I would use another way to test the functionality than the printf and cout.

``` c
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "commands.h"

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
    char expected[] = "This is where a description of the commands would be\nCommand help finished\n";
    assert_string_equal(buffer, expected);

    fclose(output_file);
}

// Add other test cases similarly...

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_execute_command_help),
        // Add other test cases here...
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

```
Fixed stdout tests


``` c
 cmocka_unit_test(test_execute_command_help),
        cmocka_unit_test(test_execute_command_led_on),
        cmocka_unit_test(test_execute_command_led_off),
        cmocka_unit_test(test_execute_command_led_blink),
        cmocka_unit_test(test_execute_command_button),
        cmocka_unit_test(test_execute_command_unknown_command),

        // Added later
        cmocka_unit_test(test_execute_command_led_blink_invalid),
        cmocka_unit_test(test_execute_command_led_invalid),
```
Summary of generated test scenarios

``` terminal
[==========] tests: Running 8 test(s).
[ RUN      ] test_execute_command_help
[       OK ] test_execute_command_help
[ RUN      ] test_execute_command_led_on
[       OK ] test_execute_command_led_on
[ RUN      ] test_execute_command_led_off
[       OK ] test_execute_command_led_off
[ RUN      ] test_execute_command_led_blink
[       OK ] test_execute_command_led_blink
[ RUN      ] test_execute_command_button
[       OK ] test_execute_command_button
[ RUN      ] test_execute_command_unknown_command
[       OK ] test_execute_command_unknown_command
[ RUN      ] test_execute_command_led_blink_invalid
[       OK ] test_execute_command_led_blink_invalid
[ RUN      ] test_execute_command_led_invalid
[       OK ] test_execute_command_led_invalid
[==========] tests: 8 test(s) run.
[  PASSED  ] 8 test(s).
```
Results

## Python

Generating unit tests for python was a breeze. It only required 5 questions, including solving some issues.

The scenarios were pretty good and had good coverage, equivelant to the C part.

The interesting part was that it didn't suggest a refactoring, which it did for the C language. And that left importand functionality untested.

``` terminal
...Command help parsed with 0 arguments
Command led parsed with 1 arguments
Command button parsed with 0 arguments
Command invalid_command parsed with 0 arguments
.
----------------------------------------------------------------------
Ran 4 tests in 0.001s

OK
Ran 4 tests in 0.0005726814270019531 seconds.
Errors: 0, Failures: 0
All tests passed!
```

# takeaways

I was Suprised to see that it suggested refactoring even if I didn't asked it. In my experience this is the way to go and one of the big problem areas when you are trying to introduce unit testing in legacy code. Usually the functionality is not cleanly structured into modules/functions and you end up with coupled functionality in a function, making testing a living hell. It was interesting that it didn't propose it for the python unit testing but only for the C part.

Generating, running and debugging the unit test was a breeze and definetely faster that I would have done it on my own. Definetely a positive experience and while generating code might be more complicated, creating unit tests through LLMs is definetely the way to go.