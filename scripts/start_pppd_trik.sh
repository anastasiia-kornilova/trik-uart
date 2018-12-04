#!/bin/sh

device="/dev/ttyS1"

echo "Starting pppd..."

mknod /dev/ppp c 108 0
stty -F $device raw
stty -F $device -a
pppd $device 115200 10.0.5.2:10.0.5.1 noauth local debug dump defaultroute nocrtscts persist maxfail 0 holdoff 1
