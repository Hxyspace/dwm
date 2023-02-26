#!/bin/bash
#xrandr --output HDMI1 --off
#feh --no-fehbg --bg-fill --randomize '/home/yuan/picture/background/'
SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)
sleep 2
#$SHELL_FOLDER/display-double.sh
$SHELL_FOLDER/display-simple.sh
