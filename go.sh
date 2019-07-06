#!/bin/bash
cd `dirname $0` || exit 1
[ -z "$1" ] || DISPLAY=$1
[ -z "$1" ] && DISPLAY=desktop:1

export DISPLAY
../cli/chem.proj 'f default'
