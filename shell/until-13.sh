#!/bin/bash

counter=1

until [ "$counter" -gt 20 ]; do
  echo "Current count: $counter"
  ((counter++))
done

echo "Loop finished!"


