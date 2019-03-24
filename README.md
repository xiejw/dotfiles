# Install Configuration Files

## Install

- Golang: See [golang](doc/golang.md#install) doc for golang installation.
- Compile:

        cd ~/Workspace/dotfiles
        make

- Other dependencies:

        [macOS] brew install ctags urlview graphviz
        [ubuntu] sudo apt-get install exuberant-ctags urlview

## Bashrc

Append the following block at the end of `~/.bashrc`, `~/.bash_profile`, or
`~/.profile`.

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

- See [here](doc/tmux.md#tmux-cheatsheet) for cheatsheet.
- See [here](doc/tmux.md#install) for installing from source code.

## Xorg (Linux Workstation)

### Xmonad

- See [manpage](https://xmonad.org/manpage.html) for default key bindings.
- See [here](doc/xmonad_cheatsheet.md) for layout cheatsheet.

