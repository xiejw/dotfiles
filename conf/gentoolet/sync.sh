#!/bin/sh

TARGET="/home/xiejw/Workspace/dotfiles/conf/$HOSTNAME"

echo "Sync /etc/portage/make.conf."
cp -f /etc/portage/make.conf $TARGET/make.conf
