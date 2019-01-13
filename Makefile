# vim: foldenable foldmethod=marker foldlevel=1

default: clean fmt prompt_util

# {{{1 Actions.

# {{{2 Projects.

prompt_util:
	go build -o bin/$@ cmd/prompt_util/main.go

# {{{2 Sync configurations.

sync_gentoolet:
	./conf/gentoolet/sync.sh

# {{{2 Maintenance.
fmt:
	gofmt -w -l cmd

clean:
	rm -f bin/*

