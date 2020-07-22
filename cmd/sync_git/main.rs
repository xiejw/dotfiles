extern crate shellexpand;

use std::process::Command;

fn main() {
    let mut command = Command::new("ls");
    command.current_dir(shellexpand::tilde("~/Workspace").as_ref());
    if let Ok(mut child) = command.spawn() {
        child.wait().expect("command wasn't running");
        println!("Child has finished its execution!");
    } else {
        println!("ls command didn't start");
    }
    println!("Hello");
}
