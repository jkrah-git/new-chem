/*
 * Display_Command.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: jkrah
 */

#include "Display_Command.h"
#include <stdio.h>

Display_Command::Display_Command() {
	callback = NULL;
	operation = NULL;
	for (int i=0; i<DISPLAY_COMMAND_MAX_NAME; i++)
		name[i] = '\0';
}

Display_Command::~Display_Command() {}
//--------------------------------
void Display_Command::dump(){
	printf("Display_Command::[0x%zX] name[%s] operation[0x%zX]",	(long unsigned int) this, name, (long unsigned int) operation);
}
