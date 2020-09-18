#!/usr/bin/env zsh
dwmblocks &
fixbl &
dunst -config ~/.config/dunst/dunstrc &
rmspot
keebs 0
sudo rntpd
[[ -f /etc/X11/xorg.conf ]] && couch || sleep 3; desk
