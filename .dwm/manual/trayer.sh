#!/bin/bash

killall trayer
if [ $? != 0 ]; then
	trayer --edge top --widthtype request --height 18 --transparent 30 --tint 5555555 &
fi
