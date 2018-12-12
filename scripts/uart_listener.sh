#!/bin/bash
set -eou pipefail

# This is done to not missing tabs and spaces in scripts
export IFS=" "

file="example.js"
saving=0
scripts_path="/home/root/trik/scripts"

stop_getty() {
  # replace comment in /etc/inittab
  init q
}

start_getty_and_exit() {
  /bin/start_getty 115200 ttyS1
  exit 0
}

prepare_saving() {
  saving=1
  if [ -e "$scripts_path/$file" ]; then
    rm $file
  fi
  touch "$scripts_path/$file"
}

finish_saving() {
  saving=0
}

while read -r line < /dev/ttyS1; do
  if [ $saving == 0 ]; then
    echo $saving
    line_array=( $line )
    case "${line_array[0]:-}" in 
      save)
        file=${line_array[1]}
        prepare_saving
        ;;
      saveend)
        finish_saving
        ;;
      getty)
        start_getty
        ;;
    esac
  else 
    echo $line >> "$scripts_path/$file" 
  fi
done

