#!/bin/sh

global_text="global variable"

foo() {
    local local_text="local variable"

    echo "Function foo is executing"
    echo "$local_text"
}

echo "Script starting"
echo "$global_text"

foo

echo "Script ended"
echo "$global_text"

exit 0

