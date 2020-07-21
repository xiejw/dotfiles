# vim: foldenable foldmethod=marker foldlevel=1
#
C_FMT=docker run --rm -ti \
        --user `id -u ${USER}`:`id -g ${USER}` \
        -v `pwd`:/workdir xiejw/clang-format \
        /clang-format.sh

default: prompt sync_git_repo

# {{{1 Actions.

# {{{2 Projects.

prompt:
	rustc -o bin/$@ cmd/$@/main.rs

sync_git_repo:
	${CC} -std=c89 -Wall -Werror -I. -o bin/$@ cmd/$@/main.c

# {{{2 Maintenance.
fmt:
	rustfmt cmd/prompt/main.rs
	${C_FMT} cmd c

clean:
	rm -f bin/*

