#!/bin/bash
#在屏幕上显示按键
result=$(ps ax|grep -v grep|grep screenkey)
if [ "$result" == "" ]; then
  eval "screenkey --bg-color white --font-color black --font SauceCodePro --opacity 0.9 -t 2 &"
else
  eval "killall screenkey"
fi
