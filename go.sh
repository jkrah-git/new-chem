#!/bin/bash
cd `dirname $0` || exit 1
export DISPLAY=desktop:1
../cli/chem.proj 'f default'
