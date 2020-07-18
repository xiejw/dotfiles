use std::process::Command;

fn main() {
    let output = Command::new("ls")
        .arg("-l")
        .arg("-h")
        .output()
        .expect("failed to execute process");

    println!("{}", std::str::from_utf8(&output.stdout).unwrap())
}
