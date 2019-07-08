/*
 * cli_dump.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */
//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------
//---------------------------------//---------------------------------
int	cli_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------


	//cli-> dump();
	cli-> run(&cli-> dump_cmdlist, argc,  &argv[0]);
	return 0;
}
//---------------------------------//---------------------------------
int		cli_dump_help(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	cli-> dump_cmdlist_dump();
	return 0;
}
///---------------------------------//---------------------------------
int		cli_dump_world(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI	DUMP(cli-> world)		return 0;
}
//---------------------------------//---------------------------------
int		cli_dump_cli(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI	cli-> dump();	return 0;
}
//---------------------------------//---------------------------------
int		cli_dump_core(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM	vm-> dump();	return 0;
}
//---------------------------------//---------------------------------
int		cli_dump_stacks(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM	vm-> dumpstacks();	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_dump_moles(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if (vm-> concvol==NULL) { printf("NULL vol\n"); return -11; }

	//-------
	vm-> concvol->dumpmoles();
	//cli-> get_selected_vm()-> concvol->dumpmoles();
	return 0;
}
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int	cli_dump_regs(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm-> dumpregs();
//	cli-> get_selected_vm()-> dumpregs();
	return 0;
}
//---------------------------------//---------------------------------
int		cli_dump_vol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if (vm-> concvol==NULL) { printf("NULL vol\n"); return -11; }
	//-------

//	if (cli-> get_selected_vm()-> concvol != NULL) {
//		cli-> get_selected_vm()-> concvol-> dump();
	if (vm-> concvol != NULL) {	vm-> concvol-> dump();	return 0;	}
	else	return -1;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_conc(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//DUMP(cli-> get_selected_vm()-> conc)
	DUMP(vm-> conc)
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//DUMP(cli-> get_selected_vm()-> mole)
	DUMP(vm-> mole)
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_pep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	DUMP(vm-> pep) NL
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------


//---------------------------------//---------------------------------
int	load_cli_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];
	//--------------
	// 'DUMP' commands
	cli-> dump_cmdlist.clear();
	sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_help, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "cli"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_cli, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "world"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_world, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "core"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_core, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "stacks"); 	r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_stacks, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "stack"); 	r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_stack_dump, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "moles"); 	r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_moles, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "regs"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_regs, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "vol"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_vol, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_conc, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_mole, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_pep, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------

