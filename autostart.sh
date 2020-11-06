#!/usr/bin/env zsh

# only execute for ryuko
if [[ $HOST == "ryuko" ]]; then
  dwmblocks &
  fixbl &
  dunst -config ~/.config/dunst/dunstrc &
  #rmspot
  keebs 0
  sudo rntpd
  /usr/lib/kdeconnectd &
  if [[ -f /etc/X11/xorg.conf ]]; then 
    couch
    mstart
  else
    sleep 3
    desk
    sstart
  fi
fi
