use std::io::{self, Write};
use rand::Rng;

const FIELD_SEPARATOR: char = ',';

struct CommandProcessor {
    cmd: String,
    par: Vec<String>,
}

impl CommandProcessor {
    fn new() -> Self {
        CommandProcessor {
            cmd: String::new(),
            par: Vec::new(),
        }
    }

    fn process_buffer(&mut self, buffer: &str) -> String {
        if buffer.is_empty() {
            return String::from("");
        }

        let mut parts = buffer.splitn(2, FIELD_SEPARATOR);
        self.cmd = parts.next().unwrap().to_string();
        self.par = parts.next().unwrap_or("").split(FIELD_SEPARATOR).map(String::from).collect();

        if self.par.len() == 1 && self.par[0].is_empty() {
            self.par.clear();
        }

        format!("Command {} parsed with {} arguments", self.cmd, self.par.len())
    }

    fn execute_command(&self) -> String {
        match self.cmd.as_str() {
            "help" => self.print_help_menu(),
            "led" => self.print_led_command(),
            "button" => self.print_button_command(),
            _ => String::from("Command not found"),
        }
    }

    fn print_help_menu(&self) -> String {
        String::from("This is where a description of the commands would be")
    }

    fn print_button_command(&self) -> String {
        let pressed = rand::thread_rng().gen_bool(0.5);
        format!("Button status: {}", if pressed { "pressed" } else { "Not pressed" })
    }

    fn print_led_command(&self) -> String {
        if self.par.is_empty() {
            return String::from("Led command wrong parameters");
        }

        match self.par[0].as_str() {
            "on" => String::from("Led is on"),
            "off" => String::from("Led is off"),
            "blink" => {
                if self.par.len() != 2 {
                    return String::from("Led blinking command wrong parameters");
                }
                format!("Led is blinking with {} Hz", self.par[1])
            }
            _ => String::from("Led command wrong parameters"),
        }
    }
}

fn main() {
    let mut cp = CommandProcessor::new();

    loop {
        print!("Enter a command: ");
        io::stdout().flush().unwrap();

        let mut buffer = String::new();
        io::stdin().read_line(&mut buffer).unwrap();
        buffer = buffer.trim().to_string();

        if buffer.is_empty() {
            continue;
        }

        let output = cp.process_buffer(&buffer);

        if !output.is_empty() {
            println!("{}", output);
        }

        let execution_result = cp.execute_command();

        if !execution_result.is_empty() {
            println!("{}", execution_result);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_process_buffer() {
        let mut cp = CommandProcessor::new();
        assert_eq!(cp.process_buffer(""), "");

        let buffer = "led,on";
        assert_eq!(cp.process_buffer(buffer), "Command led parsed with 1 arguments");
        assert_eq!(cp.cmd, "led");
        assert_eq!(cp.par, vec!["on".to_string()]);
    }

    #[test]
    fn test_print_help_menu() {
        let cp = CommandProcessor::new();
        assert_eq!(cp.print_help_menu(), "This is where a description of the commands would be");
    }

    #[test]
    fn test_print_button_command() {
        let cp = CommandProcessor::new();
        let result = cp.print_button_command();
        assert!(result == "Button status: pressed" || result == "Button status: Not pressed");
    }

    #[test]
    fn test_print_led_command() {
        let mut cp = CommandProcessor::new();
        cp.par = vec!["on".to_string()];
        assert_eq!(cp.print_led_command(), "Led is on");

        cp.par = vec!["off".to_string()];
        assert_eq!(cp.print_led_command(), "Led is off");

        cp.par = vec!["blink".to_string(), "5".to_string()];
        assert_eq!(cp.print_led_command(), "Led is blinking with 5 Hz");

        cp.par = vec!["blink".to_string()];
        assert_eq!(cp.print_led_command(), "Led blinking command wrong parameters");
    }

    #[test]
    fn test_execute_command() {
        let mut cp = CommandProcessor::new();

        cp.cmd = "help".to_string();
        assert_eq!(cp.execute_command(), "This is where a description of the commands would be");

        cp.cmd = "button".to_string();
        let result = cp.execute_command();
        assert!(result == "Button status: pressed" || result == "Button status: Not pressed");

        cp.cmd = "led".to_string();
        assert_eq!(cp.execute_command(), "Led command wrong parameters");

        cp.cmd = "invalid".to_string();
        assert_eq!(cp.execute_command(), "Command not found");
    }
}
