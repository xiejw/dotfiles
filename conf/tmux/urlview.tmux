#!/usr/bin/env bash
#
# This script copies from https://github.com/tmux-plugins/tmux-urlview.

cmd=urlview

tmux bind-key "u" capture-pane -J \\\; \
  save-buffer "${TMPDIR:-/tmp}/tmux-buffer" \\\; \
  delete-buffer \\\; \
  split-window -l 10 "$cmd '${TMPDIR:-/tmp}/tmux-buffer'"
