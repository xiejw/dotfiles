# vim: foldenable foldmethod=marker foldlevel=1
#
C_FMT=docker run --rm -ti \
        --user `id -u ${USER}`:`id -g ${USER}` \
        -v `pwd`:/workdir xiejw/clang-format \
        /clang-format.sh

GO_FMT=gofmt -w -l

default: custom_prompt sync_git_repo

# {{{1 Actions.

# {{{2 Projects.

custom_prompt:
	go build -o bin/$@ cmd/$@/main.go

sync_git_repo:
	${CC} -std=c89 -Wall -Werror -I. -o bin/$@ cmd/$@/main.c

# {{{2 Sync configurations.

sync_gentoolet:
	./conf/gentoolet/sync.sh

# {{{2 Maintenance.
fmt:
	${GO_FMT} cmd
	${GO_FMT} go
	${C_FMT} cmd c

clean:
	rm -f bin/*

