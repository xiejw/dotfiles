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

        /// Checks whether current git repository has pending files..
        pub fn has_pending_files() -> bool {
            let output = Command::new("git")
                .arg("status")
                .arg("-s")
                .output()
                .expect("failed to execute process");
            output.stdout.len() > 0
        }
    }
}

fn main() {
    println!("vim runnning_in_bg: {}", env::vim::runnning_in_bg());
    println!("git has_pending_files: {}", env::git::has_pending_files());
}
