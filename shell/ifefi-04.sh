#!/bin/sh

echo "Is it morning? Please answer 'morning' or 'afternoon'"
read period_of_day

if [ "$period_of_day" = "morning" ]; then
  echo "Good morning"
elif [ "$period_of_day" = "afternoon" ]; then
  echo "Good afternoon"
else
  echo "Sorry, '$period_of_day' not recognized. Enter 'morning' or 'afternoon'"
  exit 1
fi

exit 0

