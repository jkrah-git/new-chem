/*
 * VM_Command.h
 *
 *  Created on: May 27, 2019
 *      Author: jkrah
 */

#ifndef VM_COMMAND_H_
#define VM_COMMAND_H_

#define VM_COMMAND_MAX_NAME 	32
#define VM_COMMAND_MAX_OPCODE 	8

class Concentration_VM;
#include "Concentration.h"

//-----------------------------------
class VM_Command {
public:
	int 	(*operation)(Concentration_VM*, int, char**);
	void	(*callback)(int);
	char 	name[VM_COMMAND_MAX_NAME];
	char 	opcode[VM_COMMAND_MAX_OPCODE];
	//-----
	VM_Command();
	virtual ~VM_Command(){};
	void dump();
	void test();
};
//-----------------------------------
// TODO 99: think about porting / overlap CLI commands / VM commands
//-----------------------------------
class VM_Command_Set {
public:
	mylist<VM_Command>		base_cmdlist;
	int addcmd(mylist<VM_Command> *cmd_list,int 	(*op)(Concentration_VM*, int, char**), char *name, char *opcode);
	void load_commands();
	// -------
	VM_Command_Set();
	~VM_Command_Set(){}
};
//-----------------------------------



//================================================
#endif /* VM_COMMAND_H_ */
