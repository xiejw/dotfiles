# vim: foldenable foldmethod=marker foldlevel=1

default: clean fmt custom_prompt

# {{{1 Actions.

# {{{2 Projects.

custom_prompt:
	go build -o bin/$@ cmd/custom_prompt.go

# {{{2 Sync configurations.

# {{{2 Maintenance.
fmt:
	gofmt -w -l cmd
	gofmt -w -l pkg

clean:
	rm -f bin/*

