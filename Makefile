# vim: foldenable foldmethod=marker foldlevel=1

default: clean fmt custom_prompt

# {{{1 Actions.

# {{{2 Projects.

custom_prompt:
	go build -o bin/$@ cmd/custom_prompt.go

# {{{2 Sync configurations.

sync_gentoolet:
	./conf/gentoolet/sync.sh

# {{{2 Maintenance.
fmt:
	gofmt -w -l cmd
	gofmt -w -l lib

clean:
	rm -f bin/*

