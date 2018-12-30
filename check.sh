#!/bin/bash

for ID in `grep malloc out.txt  | awk -F\[ '{ print $NF }' | sed -e 's/\].*//g'`; do
	echo "$ID .."
	grep $ID  out.txt | egrep 'malloc|free'
done

