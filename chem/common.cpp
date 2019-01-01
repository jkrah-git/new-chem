/*
 * common.cpp
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */
#include "common.h"
#include <stdio.h>
// -------------------------------------

// -------------------------------------
void printb(char val) {
	char str[16];
	sprintb(str, val);
	printf("%s", str);
}

//-----------------
void sprintb(char *str, char val) {
	sprintb(str, val, '.');
}

//-----------------
void sprintb(char *str, char val, char zero){

	char mask = 1;
	for (int i=0; i<8; i++) {
		if (val & mask)		str[7-i] = '1';
		else				str[7-i] = zero;
		mask *=2;
	}
	str[8] = '\0';
}
// -------------------------------------
