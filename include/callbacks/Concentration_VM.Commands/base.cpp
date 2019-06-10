

#include "chem/Concentration_VM.h"

//=======================
//===  BASE commands  ===
//=======================
//---------------------------------//---------------------------------
int		vm_ping(Concentration_VM *vm, int argc, char **argv){	printf("vm_ping!!\n"); exit(0);	}
//---------------------------------//---------------------------------

//-------------------
int	vm_load_cmd_base(VM_Command_Set *vmcmd){
	if (vmcmd==NULL) return -1;

	int r;
	char 	name[VM_COMMAND_MAX_NAME];
	char 	opcode[VM_COMMAND_MAX_OPCODE];

	// 'BASE' commands

	PRINT("\n");
	vmcmd-> base_cmdlist.dump();
	vmcmd-> base_cmdlist.clear();
	PRINT("\n");
	sprintf(name, "ping");
	sprintf(opcode, "p");

	r = vmcmd-> addcmd(&vmcmd-> base_cmdlist, vm_ping, (char *)name, (char *)opcode);
	//PRINT("base_cmdlist[%s] = [%d]\n", name, r);

	return r;
}
//-------------------
