# Install Configuration Files

## Install Golang

See [golang](doc/golang.md) doc for golang installation.

## Bashrc

Append the following block at the end of `~/.bashrc`, `~/.bash_profile`, or
`~/.profile`.

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

See [here](doc/tmux_cheatsheet.md) for cheatsheet.

# Other Configuration Files

- Xmonad (Linux Workstation)
  - See [manpage](https://xmonad.org/manpage.html) for default key bindings.
  - See [here](doc/xmonad_cheatsheet.md) for layout cheatsheet.

- Gentoo
  - See [here](doc/gentoo.md) for Gentoo related configuration files.

