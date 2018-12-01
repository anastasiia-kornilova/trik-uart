#!/bin/bash
set -eou pipefail

saving=0

# This is done to not missing tabs and spaces in scripts
export IFS=
file="example.js"

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
  rm $file
  touch $file
}

finish_saving() {
  saving=0
}

while read -r line < /dev/ttyS1; do 
  echo $line
  line_array=( $line )
  case "${line_array[0]}" in 
    save)
      prepare_saving
      ;;
    saveend)
      finish_saving
      ;;
    getty)
      start_getty
      ;;
    *)
      if [ $saving == 1 ]; then
         echo -e "$line" >> $file
      fi
      ;;
  esac
done

