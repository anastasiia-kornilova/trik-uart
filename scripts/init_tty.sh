#!/bin/sh 

device="/dev/ttyS1"
baudrate=115200
echo_en="echo -en"

login() {
  getty -L $device $baudrate -n -l /home/root/trik/autologin
}

start_pppd() {
  mknod /dev/ppp c 108 0
  pppd $device $baudrate 10.0.5.2:10.0.5.1 connect 'chat -v -f /etc/ppp/winclient.chat' noauth local debug dump defaultroute nocrtscts persist maxfail 0 holdoff 1
}

stty -F $device $baudrate raw
exec <$device >$device 2>&1
$echo_en "Type r to run console\n\r"
read -t 5 -n 1 ch
if [ "$ch" == "r" ]; then
  $echo_en "Running console...\n\r"
  login
else 
  $echo_en "Running pppd...\n\r"
  start_pppd
fi
