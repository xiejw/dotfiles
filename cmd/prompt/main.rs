mod env {

    pub mod vim {
        use std::process::Command;

        /// Checks whether vim is running in background.
        pub fn runnning_in_bg() -> bool {
            let output = Command::new("ps")
                .output()
                .expect("failed to execute process");
            std::str::from_utf8(&output.stdout).unwrap().contains("vim")
        }
    }

    pub mod git {
        use std::process::Command;

        /// Checks whether current git repository has pending files.
        pub fn has_pending_files() -> bool {
            let output = Command::new("git")
                .arg("status")
                .arg("-s")
                .output()
                .expect("failed to execute process");
            output.stdout.len() > 0
        }

        /// branch name, if present..
        pub fn branch_name() -> Option<String> {
            let output = Command::new("git")
                .arg("branch")
                .arg("--no-color")
                .output()
                .expect("failed to execute process");
            let mut lines = std::str::from_utf8(&output.stdout).unwrap().lines();
            loop {
                if let Some(line) = lines.next() {
                    if line.len() >= 3 && line.starts_with("*") {
                        return Some(line[2..].to_string());
                    }
                }
                break;
            }
            None
        }
    }
}

fn main() {
    println!("vim runnning_in_bg: {}", env::vim::runnning_in_bg());
    println!("git has_pending_files: {}", env::git::has_pending_files());
    println!(
        "git branch name: {}",
        env::git::branch_name().unwrap_or("(empty)".to_string())
    )
}
