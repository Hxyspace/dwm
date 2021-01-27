#!/bin/bash

#bg
/home/yuan/.dwm/auto/changeBg.sh &

#status
/home/yuan/.dwm/auto/dwm-status.sh &

#picom
picom -b

#fcitx
fcitx &

#delay launch
/home/yuan/.dwm/auto/autostart_wait.sh &
