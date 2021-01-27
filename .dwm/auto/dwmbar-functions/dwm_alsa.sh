#!/bin/sh

# A dwm_bar function to show the master volume of ALSA
# Joe Standring <git@joestandring.com>
# GNU GPLv3

# Dependencies: alsa-utils

dwm_alsa () {
    VOL=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
	VOLstatus=$(amixer get Master | tail -n1 | cut -d[ -f4 | cut -d] -f1)
    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        if [ "$VOLstatus" == "off" ]; then
            printf "ﳌ %s%%" "$VOL"
        elif [ "$VOL" -ge 0 ] && [ "$VOL" -le 25 ]; then
            printf " %s%%" "$VOL"
        elif [ "$VOL" -gt 25 ] && [ "$VOL" -le 50 ]; then
            printf " %s%%" "$VOL"
        elif [ "$VOL" -gt 50 ] && [ "$VOL" -le 85 ]; then
            printf "墳 %s%%" "$VOL"
        else
            printf " %s%%" "$VOL"
        fi
    else
        if [ "$VOL" -eq 0 ]; then
            printf "MUTE"
        elif [ "$VOL" -gt 0 ] && [ "$VOL" -le 33 ]; then
            printf "VOL %s%%" "$VOL"
        elif [ "$VOL" -gt 33 ] && [ "$VOL" -le 66 ]; then
            printf "VOL %s%%" "$VOL"
        else
            printf "VOL %s%%" "$VOL"
        fi
    fi
    printf "%s\n" "$SEP2"
}

