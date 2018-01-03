#{{{1 Configurations.
# {{{3 Vars.
# {{{2 Binaries.
GO=GOPATH=$(shell pwd)/go go

# {{{3 Colors.
RED=\033[0;31m
CYAN=\033[0;36m
PURPLE=\033[0;35m
NC=\033[0m # No Color

INFO_C=${PURPLE}

# {{{1 Actions.
# {{{3 Set up.
.PHONY: default clean fmt

default: clean fmt prompt_util

# {{{2 Projects.

prompt_util:
	$(GO) build -o bin/$@ prompt_util/main

# {{{3 Maintenance.
fmt:
	gofmt -w -l go/src

clean:
	rm -f bin/*

# vim: foldenable foldmethod=marker foldlevel=2
