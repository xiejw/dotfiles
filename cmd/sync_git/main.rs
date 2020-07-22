mod git {
    use std::path::Path;
    use std::process::Command;
    use colored::Colorize; // Pull traits for colors.

    fn expand_path(path: &str) -> String {
        shellexpand::tilde(path).into_owned()
    }

    pub fn sync_repo(path: &str) -> Result<(), &'static str> {
        let normalized_path = expand_path(path);

        if Path::new(&normalized_path).exists() {
        }


        let mut cmd = Command::new("git");
        cmd.arg("pull").arg("--rebase");
        cmd.current_dir(&normalized_path);

        println!("{}", format!("Pulling: {}", normalized_path).cyan().bold());

        if let Ok(mut child) = cmd.spawn() {
            let exit_result = child.wait();
            match &exit_result {
                Ok(status) => {
                    let exit_code = status.code().unwrap();
                    if exit_code != 0 {
                        return Err("exit code is nonzero");
                    }
                }
                Err(_) => return Err("no status from git pull"),
            }
            return Ok(());
        }

        Err("git command didn't start")
    }
}

fn main() {
    if let Err(err) = git::sync_repo("~/Workspace/dotfiles") {
        println!("error {}", err)
    }
}
