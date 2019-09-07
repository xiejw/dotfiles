Brew
====

Install in Custom Folder
------------------------

    cd ~/Workspace
    mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
    export PATH=~/Workspace/homebrew/bin:$PATH

Common Packages to Install
--------------------------

    brew install tmux
    brew install graphviz
    brew install bash-completion
    brew install

Command CLI
-----------

    brew update
    brew upgrade
    brew cask upgrade
    brew doctor
    brew cleanup

    brew info package_name
