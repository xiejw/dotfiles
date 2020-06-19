# Golang

## Install

Go [official site](http://golang.org) to download. It is recommended **not** to
use Linux distro package to install, as it could be super old.

Typically, the install can be done via:

    sudo tar -C /usr/local -xzf go$VERSION.$OS-$ARCH.tar.gz


## Other Common Cmds

    go mod init <mod_path>  # initialize the go.mod.
    go get -u package/name  # upgrade to latest version.
    go mod tidy             # clean up go.mod file.
