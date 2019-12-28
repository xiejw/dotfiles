# Install from Source Code

Most Debian distributions, e.g., stretch, contain very old `tmux`, which does not
support the configuration file in this repo. So, compile it from source is one
solution.


    git clone https://github.com/tmux/tmux.git
    sudo apt install automake pkg-config libevent-dev libncurses-dev
    sh autogen.sh
    ./configure
    make
    sudo make install

# Tmux Cheatsheet

## General

Note the `tmux.conf` in this repro uses `ctrl-o` as `PREFIX`.  Shortcuts (see
https://gist.github.com/andreyvit/2921703 as reference):

|                 | Key               | Comment                                                      |
| --------------- | ------------------| ------------------------------------------------------------ |
| Special         | `PREFIX r`        | Reload config file `tmux.conf`.                              |
|                 | `PREFIX :`        | Execute a tmux command line.                                 |
|                 | `PREFIX t`        | Display a clock.                                             |
| Window          | `PREFIX c`        | Creates a new window                                         |
|                 | `PREFIX 1 ...`    | Switch to window 1. ... 9                                    |
|                 | `PREFIX p`        | previous window                                              |
|                 | `PREFIX n`        | next window                                                  |
|                 | `PREFIX l`        | 'last' (previously used)  window                             |
|                 | `PREFIX w`        | choose window from list                                      |
|                 | `PREFIX ,`        | rename the current window                                    |
|                 | `PREFIX &`        | kill  the current window                                     |
| Pane Split      | `PREFIX "`        | split vertically (top/bottom)                                |
|                 | `PREFIX s`        | split vertically (top/bottom)                                |
|                 | `PREFIX %`        | split horizontally (left/right)                              |
|                 | `PREFIX v`        | split horizontally (left 0.66 /right 0.33)                   |
| Pane Navigation | `PREFIX <left>`   | go to the next pane on the left                              |
|                 | `PREFIX <right>`  |                                                              |
|                 | `PREFIX <up>`     |                                                              |
|                 | `PREFIX <down>`   |                                                              |
|                 | `PREFIX [hjkl]`   | go to next pane on the left, down, up, right.                |
|                 | `PREFIX o`        | go to the next pane (cycle through all of them)              |
|                 | `PREFIX ;`        | go to the ‘last’ (previously used) pane                      |
| Pane Move       | `PREFIX {`        | move the current pane to left                                |
|                 | `PREFIX }`        | move the current pane to right                               |
|                 | `PREFIX !`        | move the current pane into a new separate window             |
| Pane Layout     | `PREFIX <space>`  | switch to the next layout                                    |
|                 | `PREFIX [JKHL]`   | (Repeated) Resize the pane left, right, down, up by 5 lines. |
| Pane Zoom       | `PREFIX z`        | Toggle: zoom (max)/unzoom (restore) the current pane         |
|                 | `PREFIX x`        | kill the current pane                                        |
|                 | `PREFIX q`        | display pane numbers for a short while (if you type the number, move cursor there). |

## Session

    Function               Key/CMD
    New                    tmux new -s <session_name>
    List                   tmux ls
    Attach                 tmux attach -t <session_name>
    Rename                 [tmux] PREFIX $
    Detach                 [tmux] PREFIX d
    Detach others          [tmux] PREFIX D
    Switch                 [tmux] :choose-tree

## Other Cmds

    Set pane sizes         select-layout even-vertical
    Set pane sizes         select-layout even-horizontal
    Renumber window        move-window -s <original_number> -t <new_number>

## Copy Mode

Press `PREFIX [` enters _Copy Mode_. After quitting, press `PREFIX ]` to paste
the selection.

    Function                vi
    Back to indentation     ^
    Clear selection         Escape
    Copy selection          Enter
    Cursor down             j
    Cursor left             h
    Cursor right            l
    Cursor to bottom line   L
    Cursor to middle line   M
    Cursor to top line      H
    Cursor up               k
    Delete entire line      d
    Delete to end of line   D
    End of line             $
    Goto line               :
    Half page down          C-d
    Half page up            C-u
    Next page               C-f
    Next word               w
    Paste buffer            p
    Previous page           C-b
    Previous word           b
    Quit mode               q
    Scroll down             C-Down or J
    Scroll up               C-Up or K
    Search again            n
    Search backward         ?
    Search forward          /
    Start of line           0
