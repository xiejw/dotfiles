# Install Configuration Files

## Install

- Golang: See [golang](doc/golang.md#install) doc for golang installation.
- Compile:

        mkdir -p ~/Workspace
        cd ~/Workspace/dotfiles
        PATH=$PATH:/usr/local/go/bin make
        # clean up the go pkg folder due to missing $GOPATH
        rm -rf ~/go

- Other dependencies:

        [macOS] brew install ctags urlview graphviz
        [ubuntu] sudo apt-get install exuberant-ctags urlview graphviz

## Bashrc

Append the following block at the end of `~/.bashrc`, `~/.bash_profile`, or
`~/.profile`.

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Kitty

    mkdir -p  ~/.config/kitty
    rm ~/.config/kitty/kitty.conf
    ln -sf ~/Workspace/dotfiles/conf/kitty.conf ~/.config/kitty/kitty.conf
    ln -sf ~/Workspace/dotfiles/conf/zoom_toggle.py ~/.config/kitty/

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

- Install `ncurses-base` and `ncurses-term` on centos for `unsuitable terminal: screen-256color-bc` error.
- See [here](doc/tmux.md#tmux-cheatsheet) for cheatsheet.
- See [here](doc/tmux.md#install) for installing from source code.

# Configuration for Daily Tools

## Brew (macOS)

- See [here](doc/brew.md).

## XMonad

- See [manpage](https://xmonad.org/manpage.html) for default key bindings.
- See [here](doc/xmonad_cheatsheet.md) for layout cheatsheet.

