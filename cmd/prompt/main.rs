use std::fmt::Write;

mod env {

    pub mod vim {
        use std::process::Command;

        /// Checks whether vim is running in background.
        pub fn runnning_in_bg() -> bool {
            // stdin is pipe for output. So, inherit is required to work with
            // `-T`. For macOS, `-T` is needed as it will give all background
            // vims otherwise.
            let output = if cfg!(target_os = "macos") {
                Command::new("ps")
                    .arg("-T")
                    .stdin(std::process::Stdio::inherit())
                    .output()
                    .expect("failed to execute process")
            } else {
                Command::new("ps")
                    .output()
                    .expect("failed to execute process")
            };
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

    // Writes git info if under git repository.
    if let Some(branch_name) = env::git::branch_name() {
        o.write_fmt(format_args!(
            "({}{}) ", // tailing space is important.
            branch_name,
            if env::git::has_pending_files() {
                "*"
            } else {
                ""
            },
        ))
        .unwrap();
    }

    // Writes vim info.
    o.write_fmt(format_args!(
        "{}",
        if env::vim::runnning_in_bg() {
            "--vim-- " // tailing space is important.
        } else {
            ""
        }
    ))
    .unwrap();

    print!("{}", &o);
}
