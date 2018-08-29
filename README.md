# Install Configuration Files

## Bashrc

Append the following block at the end of ~/.bashrc

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

See [here](tmux_cheatsheet.md) for cheatsheet.

## Xmonad

See [manpage](https://xmonad.org/manpage.html) for default key bindings.

See [here](xmonad_cheatsheet.md) for layout cheatsheet.

## Golang `third_party` Libraries and Binaries

All Golang `third_party` libraries and binaries are installed in `/opt/go`.

Create folder:

    sudo mkdir -p /opt/go; sudo chrown $(whoami) /opt/go;

Installed libraries:

    GOPATH=/opt/go go get -u github.com/jstemmer/gotags
    GOPATH=/opt/go go get -u github.com/yqylovy/goimportdot

Dependencies:

    [macOS] brew install ctags graphviz
    [ubuntu] sudo apt-get install exuberant-ctags graphviz
