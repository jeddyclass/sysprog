#!/bin/bash

fruits=("apple" "banana" "orange" "grape" "watermelon")

echo "List of fruits:"

# Using for loop to iterate through the elements of the 'fruits' array
for fruit in "${fruits[@]}"; do
  echo "$fruit"
done

echo "Loop finished!"


