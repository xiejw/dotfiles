package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"os/exec"
)

// Executes the `cmd` with `args`, and returns the output as list of string.
func execCmd(cmd string, args ...string) ([]string, error) {
	var outputs []string
	cmdExec := exec.Command(cmd, args...)
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

func main() {
	if branch, err := getActiveBranch(); err != nil {
		os.Exit(3)
	} else {
		fmt.Printf(" \\[\\033[1;36m\\][ %s ]\\[\\033[0m\\] ", branch)
	}
}
