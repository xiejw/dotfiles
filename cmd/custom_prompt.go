package main

import (
	"flag"
	"fmt"
	"os"
	"strings"

	env "github.com/xiejw/dotfiles/lib/environment"
)

var (
	flagDebug = flag.Bool("debug", false, "Enable debug logging.")
)

func getVirtualEnvName() (string, error) {
	name := os.Getenv("VIRTUAL_ENV")
	if name == "" {
		return name, nil
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
	return strings.Join(output, "/"), nil
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

// A helper method to handle the error situation.
//
// The flag `debug` will enable the error printing. Otherwise, the program just
// eats the error message (no output will be produced).
func handleUnexpectedError(err error) {
	if *flagDebug && err != nil {
		fmt.Printf("E %v\n", err)
	}
}

func main() {
	flag.Parse()

	// Stage 1: Collect all informations in current envrinment.
	vim, err := env.IsVimInBackground()
	handleUnexpectedError(err)

	gitBranchName, hasPendingFiles, err := env.ActiveBranch()
	handleUnexpectedError(err)

	virtual_env_name, err := getVirtualEnvName()
	handleUnexpectedError(err)

	status := Status{
		HasVimInBg:    vim,
		GitMasterName: gitBranchName,
		GitLocalChane: hasPendingFiles,
		VirtualEnv:    virtual_env_name,
	}

	printPromot(status)
}
