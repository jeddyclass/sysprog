#!/bin/bash

# Loop 100 times
for ((i=1; i<=30; i++))
do
    mm=$(./test5) 
    echo "$mm  ... $i"
done

    echo "-------------------"
