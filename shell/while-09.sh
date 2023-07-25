#!/bin/sh

check_password() {
  echo "Enter password"
  read attempt

  while [ "$attempt" != "qwer1234" ]; do
    echo "Sorry, try again"
    read attempt
  done
}

check_password

exit 0

