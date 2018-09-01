# vim: foldenable foldmethod=marker foldlevel=1

#{{{1 Configurations.
GO=GOPATH=$(shell pwd) go

# {{{1 Actions.
# {{{2 Set up.
default: clean fmt prompt_util

# {{{2 Projects.

prompt_util:
	$(GO) build -o bin/$@ prompt_util/main

# {{{2 Maintenance.
fmt:
	gofmt -w -l src

clean:
	rm -f bin/*

