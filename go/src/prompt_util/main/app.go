package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"os/exec"
	"runtime"
	"strings"
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

// Fetches `pwd`.
func getPwd() (string, error) {
	outputs, err := execCmd("pwd")
	if err != nil {
		return "", err
	} else if len(outputs) == 0 {
		return "", fmt.Errorf("no output found")
	} else {
		return outputs[0], nil
	}
}

// Fetches the active branch name (starting with *).
func getActiveBranch() (string, error) {
	// Fetch all branches.
	outputs, err := execCmd("git", "branch", "--no-color")
	if err != nil {
		return "", err
	} else if len(outputs) == 0 {
		return "", fmt.Errorf("no output found")
	}

	for _, line := range outputs {
		// Find the active branch. At least 3 chars
		if len(line) >= 3 && line[0] == '*' {
			return line[2:], nil
		}
	}

	// should not reach here
	return "", fmt.Errorf("no active branch found")
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

func main() {
	vim, err := getVimInBackground()
	if err != nil {
		os.Exit(3)
	}

	vim_in_background := ""
	if vim {
		vim_in_background = " --vim--"
	}

	branch_name, err := getActiveBranch()
	if err != nil {
		if vim {
			fmt.Printf("%s ", vim_in_background)
		}
		os.Exit(3)
	}

	pending_files, err := getBranchPendingFiles()
	if err != nil {
		os.Exit(3)
	}

	if len(pending_files) > 0 {
		fmt.Printf("(%s*)%s ", branch_name, vim_in_background)
	} else {
		fmt.Printf("(%s)%s ", branch_name, vim_in_background)
	}
}
