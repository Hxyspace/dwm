#!/bin/bash
#多屏幕设置 并设置壁纸(副屏为竖屏)
#xrandr --auto --output eDP1 --pos 0x0 --primary --output HDMI1 --right-of eDP1 --rotate right
xrandr --output HDMI1 --auto --scale 0.75 --right-of eDP1 --rotate right
dir='/home/yuan/picture/background/'
picture=$dir$(ls $dir | sort --random-sort | head -1)
feh --no-fehbg --bg-fill $picture '/home/yuan/picture/bg_ver/rightbg.jpg'
