#!/bin/sh 

device="/dev/ttyUSB0"

sudo stty -F $device raw
sudo pppd $device 115200 10.0.5.1:10.0.5.2 connect 'chat -v -f winserver.chat'  proxyarp local noauth debug nodetach dump nocrtscts passive persist maxfail 0 holdoff 1
