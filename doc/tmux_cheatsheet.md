# Tmux Cheatsheet

Note the `tmux.conf` in this repro uses `ctrl-o` as `PREFIX`.  Shortcuts (see
https://gist.github.com/andreyvit/2921703 as reference):

copy mode search and cop-paste.

|                 | Key               | Comment                                                      |
| --------------- | ------------------| ------------------------------------------------------------ |
| Special         | `PREFIX r`        | Reload config file `tmux.conf`.                              |
|                 | `PREFIX :`        | Execute a tmux command line.                                 |
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

