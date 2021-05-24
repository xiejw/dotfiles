# vim: foldenable foldmethod=marker foldlevel=1
#
C_FMT=docker run --rm -ti \
        --user `id -u ${USER}`:`id -g ${USER}` \
        -v `pwd`:/workdir xiejw/clang-format \
        /clang-format.sh

CFLAGS=-std=c99 -O2 -Wall -Werror -pedantic -Wno-c11-extensions ${CLAGS}

default: prompt sync_git_repo

# {{{1 Actions.

# {{{2 Projects.

prompt:
	mkdir -p bin && ${CC} ${CFLAGS} -I. -o bin/$@ cmd/$@/main.c

sync_git_repo:
	mkdir -p bin && ${CC} ${CFLAGS} -I. -o bin/$@ cmd/$@/main.c

# {{{2 Maintenance.
fmt:
	${C_FMT} cmd c

clean:
	rm -rf bin

