#!/bin/bash

killall trayer
if [ $? != 0 ]; then
    trayer --edge right --widthtype request --SetDockType false --transparent true --distancefrom left --distance 7 --tint 0x0000ff00 &
fi
