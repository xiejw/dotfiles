package environment

import (
	"fmt"

	"github.com/xiejw/lunar/exec"
)

// Fetches the active branch name (starting with *).
//
// If not in git folder, returns "" for branch name. If found any branch name,
// the second return element will indicate whether the branch has pending files
// (local changes).
func ActiveBranch() (string, bool, error) {
	branchName, err := getActiveBranch()
	if err != nil {
		return "", false, err
	}

	pendingFiles, err := getBranchPendingFiles()
	if err != nil {
		return "", false, err
	}

	hasPendingFiles := len(pendingFiles) > 0
	return branchName, hasPendingFiles, nil
}

func getActiveBranch() (string, error) {
	// Fetch all branches.
	outputs, err := exec.RunCmd("git", "branch", "--no-color")
	if err != nil {
		return "", err
	}

	if len(outputs) == 0 {
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
	return exec.RunCmd("git", "status", "-s")
}
