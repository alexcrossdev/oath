#!/bin/sh

set -e

cd test

for FILE in *; do
    echo Testing $FILE...

    ../oath/oath $FILE

    # TODO: Testing logic here, is would just check that the exit code is 0

    echo $FILE passed!
done
