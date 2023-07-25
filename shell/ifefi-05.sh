#!/bin/sh

echo "Is it morning? Please answer 'yes' or 'no'"
read period_of_day

case "$period_of_day" in
    yes | y | Yes | YES ) echo "Good Morning";;
    n*  | N* )                echo "Good Afternoon";;   
    * )                           echo "Sorry, '$period_of_day' not recognized";;
esac

exit 0



