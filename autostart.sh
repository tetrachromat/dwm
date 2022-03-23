#!/usr/bin/env zsh
#

# only execute for ryuko
if [[ $HOST == "ryuko" ]]; then
  dwmblocks &
  fixbl &
  #rmspot
  keebs 0
  /usr/lib/kdeconnectd &
  /usr/bin/pipewire &
  /usr/bin/pipewire-pulse &
  /usr/bin/wireplumber &
  
  if [[ -f /etc/X11/xorg.conf.d/20-gpus.conf ]]; then 
    dunst -config ~/.config/dunst/dunstrc &
    noisetorch -i
    sleep 3
    desk
    sstart
  else
    dunst -config ~/.config/dunst/dunstrc -font "Monoid 6" &
		lrs
    mstart
  fi

  sudo rntpd

elif [[ $HOST == "gamagoori" ]]; then
  /usr/lib/libexec/kdeconnectd &
  /usr/bin/pipewire &
  /usr/bin/pipewire-pulse &
  /usr/bin/pipewire-media-session &
  dwmblocks &
  backg &
  mstart 
elif [[ $HOST == "barazo" ]]; then
  # TODO: fix this
  dwmblocks &
  backg &
  startup 
fi
