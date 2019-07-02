package main

import (
	"flag"
	"fmt"

	env "github.com/xiejw/dotfiles/pkg/environment"
)

var flagDebug = flag.Bool("debug", false, "Enable debug logging.")

// Records the current status of environment.
type Status struct {
	HasVimInBg    bool
	GitMasterName string // "" means not inside git folder.
	GitLocalChane bool
	VirtualEnv    string // "" means "no"
}

func (status *Status) printPrompt() {
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
		git_info = fmt.Sprintf("(%s%s) ", status.GitMasterName, status_symbol)
	}

	virtual_env_info := ""
	if status.VirtualEnv != "" {
		virtual_env_info = fmt.Sprintf("[py:%s] ", status.VirtualEnv)
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
	hasVimInBg, err := env.IsVimInBackground()
	handleUnexpectedError(err)

	gitBranchName, hasPendingFiles, err := env.ActiveBranch()
	handleUnexpectedError(err)

	virtualEnvName, err := env.VirtualEnvName()
	handleUnexpectedError(err)

	// Stage 2: Prints the the prompt.
	status := &Status{
		HasVimInBg:    hasVimInBg,
		GitMasterName: gitBranchName,
		GitLocalChane: hasPendingFiles,
		VirtualEnv:    virtualEnvName,
	}
	status.printPrompt()
}
