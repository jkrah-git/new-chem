/*
 * VM_Command.cpp
 *
 *  Created on: May 27, 2019
 *      Author: jkrah
 */
#include "VM_Command.h"
//#include "callbacks/Concentration_VM.Commands/base.cpp"
#include <stdio.h>
#include <string.h>

/*
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
  */

//----------------//----------------
VM_Command::VM_Command() {
	callback = NULL;
	operation = NULL;
	for (int i=0; i<VM_COMMAND_MAX_NAME; i++)
		name[i] = '\0';

}

//VM_Command::~VM_Command() {}
//---------------------------------
void VM_Command::dump(){
	printf("VM_Command::[0x%zX] name[%s] operation[0x%zX] callback[0x%zX]",
			(long unsigned int) this, name,
			(long unsigned int) operation,
			(long unsigned int) callback);
}
//---------------------------------//---------------------------------
// local test cmd
int		vm_cmd_test(Concentration_VM *vm, int argc, char **argv){
	printf("$$::vm_cmd_test::[%d]", argc);
	for (int i=0; i<argc; i++) {
		printf(", arg[%d][%s]", i, argv[i]);
	}
	printf("\n");

	return argc;
}
//---------------------------------
void VM_Command::test(){
	sprintf(name, "testcmd");
	operation = vm_cmd_test;

	char arg1[16], arg2[16];
	sprintf(arg1,"arg1");
	sprintf(arg2,"arg2");
	char *argl[2];
	argl[0] = arg1;
	argl[1] = arg2;

	int r;
	r = operation(NULL, 1, argl);	printf("result(1) = [%d]\n", r);
	r = operation(NULL, 2, argl);	printf("result(2) = [%d]\n", r);
	printf("final dump..\n");
	dump();
}
//---------------------------------
/*
//-----------------------------------
class VM_Command_Set {
public:
	mylist<VM_Command>		base_cmdlist;

	void addcmd(mylist<VM_Command> *cmd_list, int 	(*op)(Concentration_VM*, int, char**), char *name, char opcode)
	void load_commands();
	// -------
	VM_Command_Set();
	~VM_Command_Set(){}
};
//-----------------------------------

 */
VM_Command_Set::VM_Command_Set() {};
//---------------------------------
void VM_Command_Set::load_commands(){
	//cli_load_commands(this, 0, NULL);
	//vm_load_cmd_base(this);
}


int VM_Command_Set::addcmd(mylist<VM_Command> *cmd_list,int 	(*op)(Concentration_VM*, int, char**), char *name, char *opcode)
{
	if ((cmd_list==NULL)||(op==NULL)||(name==NULL)||(opcode==NULL)) return -1;

	mylist<VM_Command>::mylist_item<VM_Command> *cmd = cmd_list-> add();
	if (cmd==NULL) return -10;
	if (cmd-> item ==NULL) return -11;

	cmd-> item-> operation = op;
	sprintf(cmd-> item-> name, "%s", name);
	strncpy(cmd-> item-> name, name, VM_COMMAND_MAX_NAME);
	strncpy(cmd-> item-> opcode, opcode, VM_COMMAND_MAX_OPCODE);
	return 0;
}
//---------------------------------
//---------------------------------
//---------------------------------
