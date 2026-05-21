#!/bin/sh

set -e

. ./config.sh

for MODULE in $MODULES; do
    echo Building $MODULE...
    (cd $MODULE && $MAKE all)
done
