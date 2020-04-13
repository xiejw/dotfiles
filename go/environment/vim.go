package environment

import (
	"runtime"
	"strings"

	"github.com/xiejw/lunar/exec"
)

// Checks whether the vim is running in bash background.
func IsVimInBackground() (bool, error) {
	var outputs []string
	var err error

	if runtime.GOOS == "darwin" {
		outputs, err = exec.RunCmd("ps", "-T")
	} else {
		outputs, err = exec.RunCmd("ps")
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
