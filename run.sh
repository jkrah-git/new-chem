#!/bin/bash

FILE=`dirname $0`/out.txt
ls $FILE >/dev/null || exit 1

##
run()
{
	echo "..writing to [$FILE]"
	Debug/new-chem > $FILE
}
####
grepout()
{
	if [ -z "$1" ]; then 
		cat $FILE
	else
		if [ -z "$2" ]; then
			egrep $1 $FILE 
		else
			egrep $1 $FILE |  grep $2
		fi
	fi
}
####
# ------------------------------ 
memtest()
{
for ID in `grepout malloc | awk -F\[ '{ print $NF }' | sed -e 's/\].*//g'`; do
	
	let M=`grepout 'malloc' $ID | wc -l`
	let F=`grepout 'free' $ID | wc -l`

	echo -n "memtest: ID=$ID : RES="
	if [ $M -eq $F ]; then
		echo "OK : M[$M]=F[$F]"
	else
		echo "!WARN! : M[$M] != F[$F]"
	
		grepout 'malloc|free' $ID
		echo "------------------------"
	fi
done
}

# ------------------------------ 
summary()
{
	grep -v ^:: $FILE
}
# ------------------------------ 
detail()
{
	egrep -v 'malloc|free' $FILE
}
# ------------------------------------------------- 
test_func()
{
	if [ -z "$1" ]; then
		for F in $FUNCLIST;  do
			echo $F
		done
	else
		for F in $FUNCLIST;  do
			echo $F
		done | grep -w $1
	fi
}
# ===============================================================
## --  MAIN 

	#FUNCLIST="run summary detail memtest"
	FUNCLIST="run memtest detail summary"

	if [ "$1" = "list" ]; then
		test_func
		exit 0
	fi

	RUNFUNCS="$*"
	if [ -z "$RUNFUNCS" ]; then
		RUNFUNCS=$FUNCLIST
		echo "Running ALL tasks [$ALLFUNCS]"
	else
		echo "Running  subtasks [$RUNFUNCS]"
	fi

	#summary
	#memtest
	for F in $RUNFUNCS; do
		if [ -n "`test_func $F`"  ]; then
			echo "----------[ $F ] -------------"
			$F
			echo "----------------------------------"
		else
			echo "### INVALID func[$F]"
		fi
	done
