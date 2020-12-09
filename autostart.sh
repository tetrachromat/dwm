#!/usr/bin/env zsh

# only execute for ryuko
if [[ $HOST == "ryuko" ]]; then
  dwmblocks &
  fixbl &
  #rmspot
  keebs 0
  sudo rntpd
  /usr/lib/kdeconnectd &
  if [[ -f /etc/X11/xorg.conf ]]; then 
    dunst -config ~/.config/dunst/dunstrc -font "Monoid 6" &
    couch
    mstart
  else
    dunst -config ~/.config/dunst/dunstrc &
    sleep 3
    desk
    sstart
  fi
elif [[ $HOST == "gamagoori" ]]; then
  /usr/lib/libexec/kdeconnectd &
  dwmblocks &
  backg &
  mstart 
fi
