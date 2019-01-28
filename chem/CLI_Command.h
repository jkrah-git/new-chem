/*
 * CLI_Command.h
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#ifndef CLI_COMMAND_H_
#define CLI_COMMAND_H_
//================================================
#include "KeyValPair.h"

#define COMMAND_MAX_NAME 	32
//-----------------------------
class Concentration_CLI;

class CLI_Command {
public:

	int 	(*operation)(Concentration_CLI*, int, char**);
	char 	name[COMMAND_MAX_NAME];
	//-----
	CLI_Command();
	virtual ~CLI_Command(){};
	void dump();
	void test();
};
//================================================
//----------------
/*class CLI_Variable {
public:
	char	name[COMMAND_MAX_VAR];
	char
	//----
	CLI_Variable(){ memset(name, '\0', COMMAND_MAX_VARLEN); ptr = NULL; };
	~CLI_Variable(){}
	void dump() { printf("var: '%s' = [0x%zX]\n", name, ptr); }
};*/


//================================================
#endif /* CLI_COMMAND_H_ */
