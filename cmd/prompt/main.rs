use std::fmt::Write;

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
                    let line = line.as_bytes();
                    if line.len() >= 3 && line[0] == b'*' {
                        return Some(std::str::from_utf8(&line[2..]).unwrap().to_string());
                    }
                }
                break;
            }
            None
        }
    }
}

fn main() {
    let mut o = String::new();
    o.write_fmt(format_args!(
        "git has_pending_files: {}\n",
        env::git::has_pending_files()
    ))
    .unwrap();
    o.write_fmt(format_args!(
        "git branch name: {}\n",
        env::git::branch_name().unwrap_or("(empty)".to_string())
    ))
    .unwrap();

    // Writes vim info.
    o.write_fmt(format_args!(
        "{}",
        if env::vim::runnning_in_bg() {
            "--vim-- "
        } else {
            ""
        }
    ))
    .unwrap();
    println!("{}", &o);
}
