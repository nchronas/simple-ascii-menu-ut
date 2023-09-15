#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "CommandProcessor.h" // Assuming your code is in a file named CommandProcessor.h

TEST(CommandProcessorTest, ProcessBufferTest) {
    CommandProcessor processor;

    std::string buffer = "led,on";
    bool result = processor.process_buffer(buffer);

    EXPECT_FALSE(result);
    EXPECT_EQ(processor.get_command(), "led");
    ASSERT_EQ(processor.get_parameters().size(), 1);
    EXPECT_EQ(processor.get_parameters()[0], "on");
}

TEST(CommandProcessorTest, PrintHelpMenuTest) {
    CommandProcessor processor;

    testing::internal::CaptureStdout();
    processor.print_help_menu();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "This is where a description of the commands would be\n");
}

TEST(CommandProcessorTest, PrintLedCommandTest) {
    CommandProcessor processor;

    std::vector<std::string> validCommands = {"on", "off", "blink,2"};
    std::vector<std::string> expectedOutputs = {"Led is on\n", "Led is off\n", "Led is blinking with 2 Hz\n"};

    for (size_t i = 0; i < validCommands.size(); ++i) {
        processor.process_buffer("led," + validCommands[i]);

        testing::internal::CaptureStdout();
        processor.print_led_command();
        std::string output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, expectedOutputs[i]);
    }
}

TEST(CommandProcessorTest, PrintButtonCommandTest) {
    CommandProcessor processor;

    // Simulate button press
    srand(1);
    testing::internal::CaptureStdout();
    processor.print_button_command();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Button status: pressed\n");

    // Simulate button not pressed
    srand(2);
    testing::internal::CaptureStdout();
    processor.print_button_command();
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Button status: Not pressed\n");
}

TEST(CommandProcessorTest, ProcessInvalidLedCommandTest) {
    CommandProcessor processor;

    std::string buffer = "led,invalid_command";
    bool result = processor.process_buffer(buffer);

    EXPECT_FALSE(result);

    testing::internal::CaptureStdout();
    processor.print_led_command();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Led command wrong parameters\n");
}

// Add more tests as needed

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
