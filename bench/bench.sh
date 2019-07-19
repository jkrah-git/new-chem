#!/bin/bash

abort()
{	
	echo "40: aborted $*"
	exit 1
}

DATA_DIR="data/bench/"
[ -d "$DATA_DIR" ] || abort "no DATA_DIR [$DATA_DIR]"

BENCH_DIR="bench"
OUTPUT_DIR="$BENCH_DIR/outputs"
[ -d "$OUTPUT_DIR" ] || abort "no OUTPUT_DIR [$OUTPUT_DIR]"

##
mk_test()
{	
	FILE="$DATA_DIR/grid_$1_$2.chem"
	echo "making  FILE[$FILE] 'grid $1 $2'"
	$BENCH_DIR/grid.sh $1 $2 > $FILE
}

run_test()
{
	FILE="bench/grid_$1_$2"
	OUTPUT="$OUTPUT_DIR/grid_output.$1_$2.txt"
	RESULT="$OUTPUT_DIR/grid_results_$1_$2.`date +%H%M%S.%d%m%y`.txt"
	echo "runnng  FILE[$FILE] > OUTPUT[$OUTPUT]"
	../cli/chem.proj "f $FILE" > $OUTPUT
	grep -B1  'CPU' $OUTPUT > $RESULT
	echo "results saved [$RESULT]"
	
}

for I in 1 5 10 20; do
	mk_test $I
	run_test $I
done

