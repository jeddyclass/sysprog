#!/bin/bash

# Loop 100 times
for ((i=1; i<=30; i++))
do
    mm=$(./test6) 
    echo "$mm  ... $i"
done

    echo "-------------------"
