#!/bin/sh

set -e
. ./config.sh

for MODULE in $MODULES; do
    echo Cleaning $MODULE...
    (cd $MODULE && $MAKE clean)
done
