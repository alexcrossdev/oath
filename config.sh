#!/bin/sh

MODULES="ast parser scanner codegen oath"

export MAKE=${MAKE:-make}

export CC="gcc"
export AS="as"
export FLEX="flex"
export BISON="bison"
export AR="ar"
