/*
 * CLI_Command.h
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#ifndef CLI_COMMAND_H_
#define CLI_COMMAND_H_
//================================================
#define COMMAND_MAX_NAME 	32

//----------------
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
//----------------

//================================================
#endif /* CLI_COMMAND_H_ */
