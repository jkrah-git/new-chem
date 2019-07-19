#!/bin/bash
abort()
{
	echo "$0: aborted: $*"
	exit 1
}

cd `dirname $0` || exit 1

NAME="$0 $* (`date`("
WORLD_BASE=default.chem

#####################
# start with smallest default 3x3
NUM_X=1
NUM_Y=1
[ -z "$1" ] || NUM_X="$1"
[ -z "$2" ] || NUM_Y="$2"

# ---------- start
cat << EOstart
#### Start: $NAME
# WORLD_BASE=$WORLD_BASE
EOstart
[ -f "$WORLD_BASE" ] && grep -v ^#  $WORLD_BASE



# ---------- loop
echo "#### Loop"
for X in `seq 0 $NUM_X`; do
	for Y in `seq 0 $NUM_Y`; do
		# ------------------
cat <<EOloop
world add $X $Y
f cellsetup
EOloop
		# ------------------
	done
done

# ---------- end
cat <<EOend
#### End
world commit
world list vol
#### End: $NAME

# fill cahche
world tick .00001 1
# x1000
world tick .00001 1000
# x10000
world tick .00001 10000
quit
EOend

