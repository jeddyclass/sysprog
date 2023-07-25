#!/bin/sh

check_name() {
  echo "Is your name $* ?"
  while true
  do
    echo -n "Enter yes or no: "
    read answer
    case "$answer" in
      y | yes ) return 0;;
      n | no )  return 1;;
      * )       echo "Answer yes or no"
    esac
  done
}

echo "Original parameters are $*"

if check_name "$1"
then
  echo "Hi $1, nice to meet you."
else
  echo "Never mind, good day."
fi

exit 0


