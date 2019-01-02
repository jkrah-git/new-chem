#!/bin/bash

# molecule.testrot: [0xff 0xf3]( , ) =1
# molecule.testrot: [0xff 0xf4]( , ) =0
# molecule.testrot: [0xff 0xf5]( , ) =0
# molecule.testrot: [0xff 0xf6]( , ) =1
# molecule.testrot: [0xff 0xf7]( , ) =1

A="$1"
B="$2"
R="$3"

[ -z "$A" ] && A="*"
[ -z "$B" ] && B="*"
[ -z "$R" ] && R="*"

FILE=getrot.txt
####
rungrep()
{
	
	cat $FILE |  grep "($A," | grep ",$B)" | grep "=$R$" 
}
(
	echo "#### " cat $FILE |  grep "($A," | grep ",$B)" | grep "=$R$" 
	rungrep
	echo "#### found [`rungrep | wc -l`] lines"
) 

