extern crate shellexpand;

use std::process::Command;

fn expand_path(path: &str) -> String {
    shellexpand::tilde(path).into_owned()
}

fn main() {
    let mut command = Command::new("ls");
    command.current_dir(expand_path("~/Workspace"));
    if let Ok(mut child) = command.spawn() {
        child.wait().expect("command wasn't running");
        println!("Child has finished its execution!");
    } else {
        println!("ls command didn't start");
    }
    println!("Hello");
}
