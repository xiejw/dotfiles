# Install Configuration Files

## Bashrc

Append the following block at the end of ~/.bashrc

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

