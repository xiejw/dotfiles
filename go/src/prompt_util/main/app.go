package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
	"os/exec"
	"runtime"
	"strings"
)

var (
	flagDebug = flag.Bool("debug", false, "Enable debug logging.")
)

// Executes the `cmd` with `args`, and returns the output as list of string.
func execCmd(cmd string, args ...string) ([]string, error) {
	var outputs []string
	cmdExec := exec.Command(cmd, args...)
	cmdExec.Stdin = os.Stdin

	stdout, err := cmdExec.StdoutPipe()
	if err != nil {
		return outputs, err
	}

	cmdExec.Start()

	r := bufio.NewReader(stdout)
	for {
		line, _, err := r.ReadLine()
		if err == nil {
			outputs = append(outputs, string(line))
		} else if err == io.EOF {
			break // detect exec error or return code
		} else {
			return nil, err
		}
	}
	// This includes non-zero return code
	if err = cmdExec.Wait(); err != nil {
		return outputs, err
	}
	return outputs, nil
}

// Fetches the active branch name (starting with *). If not in git folder.
// returns "".
func getActiveBranch() (string, error) {
	// Fetch all branches.
	outputs, err := execCmd("git", "branch", "--no-color")
	if err != nil {
		return "", err
	} else if len(outputs) == 0 {
		return "", fmt.Errorf("Cannot find any branch")
	}

	for _, line := range outputs {
		// Find the active branch. At least 3 chars
		if len(line) >= 3 && line[0] == '*' {
			return line[2:], nil
		}
	}

	return "", fmt.Errorf("Cannot find active branch")
}

func getBranchPendingFiles() ([]string, error) {
	return execCmd("git", "status", "-s")
}

func getVimInBackground() (bool, error) {
	var outputs []string
	var err error

	if runtime.GOOS == "darwin" {
		outputs, err = execCmd("ps", "-T")
	} else {
		outputs, err = execCmd("ps")
	}

	if err != nil {
		return false, err
	}

	for _, line := range outputs {
		if strings.Contains(line, "vim") {
			return true, nil
		}
	}
	return false, nil
}

func getVirtualEnvName() string {
	name := os.Getenv("VIRTUAL_ENV")
	if name == "" {
		return name
	}

	// Convert /path/to/env as /p/t/env for short format.
	s := strings.Split(name, "/")
	output := make([]string, 0, len(s))
	final := len(s) - 1
	for i, part := range s {
		switch {
		case len(part) == 0 || i == final:
			output = append(output, part)
		default:
			output = append(output, string(part[0]))
		}
	}
	return strings.Join(output, "/")
}

type Status struct {
	HasVimInBg    bool
	GitMasterName string // "" means not inside git folder.
	GitLocalChane bool
	VirtualEnv    string // "" means "no"
}

// Should print right " ".
func printPromot(status Status) {
	vim_info := ""
	if status.HasVimInBg {
		vim_info = "--vim-- "
	}

	git_info := ""
	if status.GitMasterName != "" {
		status_symbol := ""
		if status.GitLocalChane {
			status_symbol = "*"
		}
		git_info = fmt.Sprintf(
			"(%s%s) ", status.GitMasterName, status_symbol)
	}

	virtual_env_info := ""
	if status.VirtualEnv != "" {
		virtual_env_info = fmt.Sprintf(
			"[py:%s] ", status.VirtualEnv)
	}

	fmt.Printf("%s%s%s", git_info, vim_info, virtual_env_info)
}

func handleUnexpectedError(err error) {
	if *flagDebug && err != nil {
		fmt.Printf("E %v\n", err)
	}
}

func main() {
	flag.Parse()

	vim, err := getVimInBackground()
	handleUnexpectedError(err)

	branch_name, err := getActiveBranch()
	handleUnexpectedError(err)

	virtual_env_name := getVirtualEnvName()

	has_pending_files := false
	if branch_name != "" {
		pending_files, err := getBranchPendingFiles()
		handleUnexpectedError(err)
		has_pending_files = len(pending_files) > 0
	}

	status := Status{
		HasVimInBg:    vim,
		GitMasterName: branch_name,
		GitLocalChane: has_pending_files,
		VirtualEnv:    virtual_env_name,
	}

	printPromot(status)
}
