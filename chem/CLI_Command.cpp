/*
 * CLI_Command.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */
#include <stdio.h>
#include "CLI_Command.h"
//-----
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
/*
 //----------------
class Concentration_CLI;

class CLI_Command {
public:

	int 	(*operation)(Concentration_CLI*, int*, char**);
	char 	name[COMMAND_MAX_NAME];
	//-----
	CLI_Command();
	virtual ~CLI_Command();
	void dump();
	void test();

};
//----------------
 */
//----------------//----------------
CLI_Command::CLI_Command() {
	operation = NULL;
	for (int i=0; i<COMMAND_MAX_NAME; i++)
		name[i] = '\0';

}

//CLI_Command::~CLI_Command() {}
//---------------------------------
void CLI_Command::dump(){
	printf("CLI_Command::[0x%zX] name[%s] operation[0x%zX]",	(long unsigned int) this, name, (long unsigned int) operation);
}
//---------------------------------//---------------------------------
// local test cmd
int		cli_cmd_test(Concentration_CLI *cli, int argc, char **argv){
	printf("$$::cli_cmd_test::[%d]", argc);
	for (int i=0; i<argc; i++) {
		printf(", arg[%d][%s]", i, argv[i]);
	}
	printf("\n");

	return argc;
}


//---------------------------------
void CLI_Command::test(){
	sprintf(name, "testcmd");
	operation = cli_cmd_test;

	char arg1[16], arg2[16];
	sprintf(arg1,"arg1");
	sprintf(arg2,"arg2");
	char *argl[2];
	argl[0] = arg1;
	argl[1] = arg2;

	int r;
	r = operation(NULL, 1, argl);	PRINT("result(1) = [%d]\n", r);
	r = operation(NULL, 2, argl);	PRINT("result(2) = [%d]\n", r);
	PRINT("final dump..\n");
	dump();
}



//---------------------------------
