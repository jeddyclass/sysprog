#!/bin/sh

counter=1

while [ "$counter" -le 20 ]
do
  echo "[$counter], Here we counts..."
  counter=$((counter + 1))
done

exit 0



