package environment

import (
	"os"
	"strings"
)

func VirtualEnvName() (string, error) {
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
