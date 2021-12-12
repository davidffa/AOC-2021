#!/bin/sh

if [ -z "$1" ]; then
  echo "Usage: $0 <DAY>"
  exit 1
fi

set -xe

CC=cc
CFLAGS="-Wall -Wextra -Wshadow -pedantic -std=c11"

cd $1 && $CC $CFLAGS -o $1 main.c && ./$1 && cd ..