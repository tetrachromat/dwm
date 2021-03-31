#!/usr/bin/env zsh

# only execute for ryuko
if [[ $HOST == "ryuko" ]]; then
  dwmblocks &
  fixbl &
  #rmspot
  keebs 0
  /usr/lib/kdeconnectd &
  if [[ -f /etc/X11/xorg.conf ]]; then 
    dunst -config ~/.config/dunst/dunstrc -font "Monoid 6" &
    couch
    mstart
  else
    dunst -config ~/.config/dunst/dunstrc &
    noisetorch -i
    sleep 3
    desk
    sstart
  fi
  sudo rntpd
elif [[ $HOST == "gamagoori" ]]; then
  /usr/lib/libexec/kdeconnectd &
  dwmblocks &
  backg &
  mstart 
fi
