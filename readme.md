# Install Configuration Files

## Install

- Compile:

        mkdir -p ~/Workspace
        cd ~/Workspace
        git clone git@github.com:xiejw/dotfiles.git
        cd dotfiles
        CC=clang make

## Bashrc

Append the following block at the end of `~/.profile`.

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bash_profile

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

- Install `ncurses-base` and `ncurses-term` on centos for `unsuitable terminal: screen-256color-bc` error.
- See [here](doc/tmux.md#tmux-cheatsheet) for cheatsheet.
- See [here](doc/tmux.md#install) for installing from source code.

## Kitty

    mkdir -p  ~/.config/kitty
    rm ~/.config/kitty/kitty.conf
    ln -sf ~/Workspace/dotfiles/conf/kitty.conf ~/.config/kitty/kitty.conf
    ln -sf ~/Workspace/dotfiles/conf/zoom_toggle.py ~/.config/kitty/

## XMonad

- See [manpage](https://xmonad.org/manpage.html) for default key bindings.
- See [here](doc/xmonad_cheatsheet.md) for layout cheatsheet.

## Clang/LLVM

To compile llvm

```
git clone https://github.com/llvm/llvm-project.git
cd llvm-project
mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_ENABLE_PROJECTS='clang;clang-format;lld;compiler-rt' \
        -DLLVM_ENABLE_ASSERTIONS=NO \
        -DLLVM_ENABLE_THREADS=NO \
        -DLLVM_TARGETS_TO_BUILD="X86" \
        -DLLVM_USE_NEWPM=ON \
        -DLLVM_USE_LINKER=lld \
        ../llvm/
```
where compiler-rt is needed for asan. Install `cmake ninja` ahead of time.
