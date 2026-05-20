#!/bin/sh

set -e
. ./config.sh

for MODULE in $MODULES; do
    (cd $MODULE && $MAKE clean)
done
