# Golang

## Install

Go [official site](golang.org) to download. It is recommended not to use Linux
distro package to install.

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

