# Gentoo

## Portage Cheatsheet

    # Update
    emerge --sync
    [etc-update]
    [emerge --oneshot portage]
    emerge --update --deep --with-bdeps=y --newuse @world
    emerge -av --depclean
    revdep-rebuild -v

    # Check USE flags
    emerge -pv @world
    emerge -pv <package_name>


    # Check system info
    emerge --info

    # Install and uninstall
    emerge --ask <package>    # See USE and dep first.
    emerge -a unmerge <package>

    # Search
    emerge search pdf

    # Check package files
    equery files <package>

    # Find which (installed) package a file belongs to
    equery b <file>

## Install

### Pre-Install

#### Pre Pre-Install on VirtualBox

It is useful to ssh into the machine during install stage. So, before start the
new VM with install ISO file, ensure that the `host-only adapter` is configured
properly in your VM's network setting.


#### The Real Pre install

Set up the sshd before install. It is much easier to do installation in another
machine with copy-paste.

    ssh root@<vm_ip>

After that, modify the configure file `/etc/portage/make.conf` to use the
correct `USE` and `FEATURES` before install anything:

    USE="-doc -examples -emacs -debug"
    FEATURES="nodoc noman noinfo"

### Install

Compile Kernel

    sudo make
    sudo make modules_install
    sudo make install


### Post install

#### Time Zone

        cp /usr/share/zoneinfo/America/Los_Angeles /etc/localtime

#### Add User

        useradd -m -G users,wheel,audio -s /bin/bash <user_name>
        passwd <user_name>

#### Some Simple Twists

First, clean the domain name in loggin screen. Simply, delete the `.\O` in
`/etc/issue` file.

Then, add sudo:

    uncomment %sudo in /etc/sudoers
    groupadd sudo
    usermod -a -G sudo <user_name>

#### Install utilities:

Install necessary tools:

    emerge sudo vim dev-vcs/git app-portage/gentoolkit tux bash-completion
    EDITOR=vim git config --global -e
    ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

#### Set up Time in VirtualBox

The gentoo in VirtualBox might have time shift. For example, when the laptop
wakes up from sleep, the time is wrong. To fix that automatically, first,
install `virtualbox-guest-additions`:

    sudo emerge -a virtualbox-guest-additions
    sudo rc-update add virtualbox-guest-additions boot

There are some properties you can change also, e.g.,

    /usr/sbin/vboxguest-service  --timesync-set-threshold 1000

For reference, read the document here also
https://wiki.gentoo.org/wiki/System_time.

## Other Stuff

### OpenRC `init`

See [OpenRC](https://wiki.gentoo.org/wiki/OpenRC) for documentation.

    rc-update add sshd default
    rc-update del sshd default
    rc-update -v show          # -v lists all, not just enabled

### For syslog-ng
`/etc/syslog-ng/syslog-ng.conf` is the configuration file. By default, `tty12`
and `/var/log/messages` are the default output targets.

### For portage
`/var/log/emerge.log` shows the high-level status.
