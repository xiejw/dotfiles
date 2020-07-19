mod env {
    use std::process::Command;

    pub fn vim() -> bool {
        let output = Command::new("ps")
            .output()
            .expect("failed to execute process");

        std::str::from_utf8(&output.stdout).unwrap().contains("vim")
    }
}

fn main() {
    // let output = Command::new("ls")
    //     .arg("-l")
    //     .arg("-h")
    //     .output()
    //     .expect("failed to execute process");
    //
    println!("contains vim: {}", env::vim());
}
