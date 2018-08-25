# Install Configuration Files

## Bashrc

Append the following block at the end of ~/.bashrc

    # Customized
    export DOTFILES=~/Workspace/dotfiles
    source ~/Workspace/dotfiles/conf/bashrc

## Tmux

Link the file:

    ln -sf ~/Workspace/dotfiles/conf/tmux.conf ~/.tmux.conf

Shortcuts (see https://gist.github.com/andreyvit/2921703 as reference):

| Key               | Comment                                              |
| ------------------| -----------------------------------------------------|
| `ctrl-o c`        | Creates a new window                                 |
| `ctrl-o 1 ...`    | Switch to window 1. ... 9                            |
| `ctrl-o p`        | previous window                                      |
| `ctrl-o n`        | next window                                          |
| `ctrl-o l`        | 'last' (previously used)  window                     |
| `ctrl-o w`        | choose window from list                              |
| ------------------| -----------------------------------------------------|
| `ctrl-o ,`        | rename the current window                            |
| `ctrl-o &`        | kill  the current window                             |
| ------------------| -----------------------------------------------------|
| `ctrl-o "`        | split vertically (top/bottom)                        |
| `ctrl-o s`        | split vertically (top/bottom)                        |
| `ctrl-o %`        | split horizontally (left/right)                      |
| `ctrl-o v`        | split horizontally (left 0.66 /right 0.33)           |
| ------------------| -----------------------------------------------------|
| `ctrl-o <left>`   | go to the next pane on the left                      |
| `ctrl-o <right>`  |                                                      |
| `ctrl-o <up>`     |                                                      |
| `ctrl-o <down>`   |                                                      |
| `ctrl-o [hjkl]`   | go to next pane on the left, down, up, right.        |
| `ctrl-o o`        | go to the next pane (cycle through all of them)      |
| `ctrl-o ;`        | o to the ‘last’ (previously used) pane               |
| ------------------| -----------------------------------------------------|
| `ctrl-o {`        | move the current pane to the previous position       |
| `ctrl-o }`        | move the current pane to the next position           |
| `ctrl-o ctrl-o`   | rotate window ‘up’ (i.e. move all panes)             |
| `ctrl-o alt-o`    | rotate window ‘down’ (i.e. move all panes)           |
| `ctrl-o !`        | move the current pane into a new separate window     |
| ------------------| -----------------------------------------------------|
| `ctrl-o <space>`  | switch to the next layout                            |
| `ctrl-o :resize-pane -[LRDU] <size>`  | Resize the pane left, right, down, up with `size` lines. |
| `ctrl-o [JKHL]`   | Resize the pane left, right, down, up with 5 lines.  |
| ------------------| -----------------------------------------------------|
| `ctrl-o z`        | Toggle: zoom (max)/unzoom (restore) the current pane |
| `ctrl-o x`        | kill the current pane                                |
| `ctrl-o q`        | display pane numbers for a short while (if you type the number, move cursor there. |
| ------------------| -----------------------------------------------------|

(Note the `tmux.conf` in this repro uses `ctrl-o` as prefix.)

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
