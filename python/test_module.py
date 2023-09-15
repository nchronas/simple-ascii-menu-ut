import unittest
from unittest.mock import patch
from io import StringIO
from io import BytesIO
import sys

# Import the CommandProcessor class from your code
from simple_menu import CommandProcessor

class TestCommandProcessor(unittest.TestCase):

    def test_print_help_menu(self):
        processor = CommandProcessor()
        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.print_help_menu()
            output = mock_stdout.getvalue().strip()
            self.assertEqual(output, "This is where a description of the commands would be")

    def test_print_button_command(self):
        processor = CommandProcessor()
        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.print_button_command()
            output = mock_stdout.getvalue().strip()
            self.assertIn(output, ["Button status: pressed", "Button status: Not pressed"])

    def test_print_led_command(self):
        processor = CommandProcessor()

        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.par = ["on"]
            processor.print_led_command()
            output = mock_stdout.getvalue().strip()
            self.assertEqual(output, "Led is on")

        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.par = ["off"]
            processor.print_led_command()
            output = mock_stdout.getvalue().strip()
            self.assertEqual(output, "Led is off")

        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.par = ["blink", "5"]
            processor.print_led_command()
            output = mock_stdout.getvalue().strip()
            self.assertEqual(output, "Led is blinking with 5 Hz")

        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.par = ["blink"]
            processor.print_led_command()
            output = mock_stdout.getvalue().strip()
            self.assertEqual(output, "Led blinking command wrong parameters")

        with patch('sys.stdout', new_callable=StringIO) as mock_stdout:
            processor.par = ["invalid"]
            processor.print_led_command()
            output = mock_stdout.getvalue().strip()
            self.assertEqual(output, "Led command wrong parameters")

    def test_process_buffer(self):
        processor = CommandProcessor()
        self.assertTrue(processor.process_buffer(""))
        self.assertFalse(processor.process_buffer("help"))
        self.assertEqual(processor.cmd, "help")
        self.assertEqual(processor.par, [])

        self.assertFalse(processor.process_buffer("led,on"))
        self.assertEqual(processor.cmd, "led")
        self.assertEqual(processor.par, ["on"])

        self.assertFalse(processor.process_buffer("button"))
        self.assertEqual(processor.cmd, "button")
        self.assertEqual(processor.par, [])

        self.assertFalse(processor.process_buffer("invalid_command"))
        self.assertEqual(processor.cmd, "invalid_command")
        self.assertEqual(processor.par, [])
