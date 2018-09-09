#!/bin/sh

TARGET="/home/xiejw/Workspace/dotfiles/conf/$HOSTNAME"

echo "Sync kernel config."
cp -f /usr/src/linux/.config $TARGET/kernel.config

echo "Sync /etc/portage/make.conf."
cp -f /etc/portage/make.conf $TARGET/make.conf
