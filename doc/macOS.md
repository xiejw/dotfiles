## macOS Configuraiton

### System Preference

- In `Finder`, preference,
  - In `Advanced`, set `Search the Current Folder` in `When performing a search`.
- In `Docker`, Choose a small size and disable auto-hide.
- In `Keyboard`, disable `CapsLock`.
- In `Spotlight`
  - In `Privacy`, remove `~/Downloads` in Spotlight.
  - In `Search Results`, remove `Music, Movies, Mail`.
- In `Mission Control`
  - Set the left-top corner for `Put Display to Sleep`.
  - Disable `Automatically rearrange Spaces based on most recent use`.
  - Set `Group windows by application`.
- In `General`
  - Set number of Recent Items to `None`.
  - Uncheck `Allow Handoff between this Mac and your iCloud devices`

- In `TimeMachine`, remove

        ~/Downloads
        ~/VirtualBox VMs
        ~/Library/Containers/com.docker.docker


### Applications

- For `IINA`, turn on `2x window during start up` and `Float Window`.
- For `Screenshot`, click `Options` and uncheck `Show Floating Thumbnail`.

### Other Tips

#### Disable All Notifications for non-Personal devices.

Set up the Do Not Disturb to make it 24-hour.

#### Clean History

    # Clear paste board.

    # Use `unset HISTFILE` to temporarily suspend tracking in current shell.
    ~/.bash_history

