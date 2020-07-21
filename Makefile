# vim: foldenable foldmethod=marker foldlevel=1
#
C_FMT=docker run --rm -ti \
        --user `id -u ${USER}`:`id -g ${USER}` \
        -v `pwd`:/workdir xiejw/clang-format \
        /clang-format.sh

default: prompt sync_git_repo alias

# {{{1 Actions.

# {{{2 Projects.

prompt:
	cargo build --release

sync_git_repo:
	mkdir -p bin && ${CC} -std=c89 -Wall -Werror -I. -o bin/$@ cmd/$@/main.c

alias:
	ln -sf ../target/release/prompt bin/prompt

# {{{2 Maintenance.
fmt:
	rustfmt cmd/prompt/main.rs
	${C_FMT} cmd c

clean:
	rm -rf bin && cargo clean

