#!/bin/bash

# Get id of touchpad and the id of the field corresponding to
id=`xinput list | grep "Touchpad" | cut -d'=' -f2 | cut -d'[' -f1`

# Set the property to false  禁用触摸板
xinput --set-prop $id 'Device Enabled' 0

#启用
#xinput --set-prop $id 'Device Enabled' 1
