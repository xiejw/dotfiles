# Install Configuration Files

## Bashrc

Append the following block at the end of ~/.bashrc

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

## Golang `third_party` Libraries and Binaries

All Golang `third_party` libraries and binaries are installed in `/opt/go`.

Create folder:

    sudo mkdir -p /opt/go; sudo chrown $(whoami) /opt/go;

Installed libraries:

    GOPATH=/opt/go go get -u github.com/jstemmer/gotags
    GOPATH=/opt/go go get -u github.com/yqylovy/goimportdot

Dependencies:

    brew install ctags graphviz
