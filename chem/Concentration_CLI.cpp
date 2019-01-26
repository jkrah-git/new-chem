/*
 * Concentration_CLI.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#include "Concentration_CLI.h"
#include <string.h>
//=====================
//---------------------------------//---------------------------------
/*
class Concentration_CLI {
private:
	ConcentrationVolume 								*concvol;
	mylist<Concentration>::mylist_item<Concentration>	*conc;
	Molecule											*mole;

	mylist<Concentration_Command>						cmdlist;

public:
	Concentration_CLI();
	virtual ~Concentration_CLI();
	void	load_commands();
	void 	dump();
	void 	test();
};
*/
//---------------------------------

Concentration_CLI::Concentration_CLI() {
	concvol  = NULL;
	conc = NULL;
	mole = NULL;

}
//---------------------------------
Concentration_CLI::~Concentration_CLI() {}
//---------------------------------
void Concentration_CLI::dump() {

	printf("Concentration_CLI[0x%zX]:: concvol[0x%zX],conc[0x%zX],mole[0x%zX]\n",
			(long unsigned int) this,
			(long unsigned int) concvol,
			(long unsigned int) conc,
			(long unsigned int) mole );
	printf("Concentration_CLI[0x%zX]::", (long unsigned int) this);
	cmdlist.dump();
}
//---------------------------------
void Concentration_CLI::test() {
	PRINT(" .. START .. \n");
	PRINT("==============\n");
	PRINT(" .. pre dump =>\n"); dump();
	PRINT("==============\n");

	mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = cmdlist.add();
	PRINT("==============\n");
	PRINT(" .. new cmd =>"); DUMP(cmd);
	if ((cmd!=NULL) && (cmd-> item !=NULL)) {
		PRINT("==============\n");
		PRINT(" .. cmd.test() =>\n");
		cmd-> item -> test();
	}
	PRINT("==============\n");
	PRINT(" .. load_commands =>\n"); //dump();
	load_commands();
	PRINT("==============\n");

	int r;
	char	arg0[16], arg1[16], *argl[5];
	argl[0] = arg0;
	argl[1] = arg1;
	sprintf(arg0, "help");
	sprintf(arg1, "arg1");
	PRINT(" .. run '%s' =>\n", arg0); r = run(1, argl); PRINT(".. (%s)=(%d)\n", arg0, r);
	PRINT(" .. run '%s' =>\n", arg0); r = run(2, argl); PRINT(".. (%s)=(%d)\n", arg0, r);


	//-----
	PRINT("==============\n");
	PRINT(" .. final dump ..\n"); dump();
	PRINT("==============\n");
	PRINT(" .. END ..\n");
}
//---------------------------------
//---------------------------------
int	Concentration_CLI::run(int argc, char **argv){
	if ((argc<1) || (argv==NULL)) return -100;

	//mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = cmdlist.add();

	// search for argv[0]
	CLI_Command  *cmd = NULL;
	mylist<CLI_Command>::mylist_item<CLI_Command>  *next_item = cmdlist.gethead();
	while ((next_item!=NULL) && (next_item-> item != NULL)) {
		int r = strcmp(argv[0], next_item-> item->name);
		if (r==0) {
			cmd = next_item-> item;
			break;
		}
		// ---
		next_item = next_item->next;
	}
	if (cmd==NULL) {
		printf("[%s].Command Not Found\n", argv[0]);
		return -101;
	}
	if (cmd-> operation==NULL) {
		printf("[%s].Command.operation NULL\n", argv[0]);
		return -102;
	}

	int r = cmd-> operation(this, argc-1, &argv[1]);
	printf("[%s].[%d]\n", argv[0], r);
	return r;
}
//---------------------------------
//-------------
int	Concentration_CLI::addcmd(int 	(*op)(Concentration_CLI*, int, char**), char *name){
	if ((op==NULL)||(name==NULL)) return -1;

	mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = cmdlist.add();
	if (cmd==NULL) return -10;
	if (cmd-> item ==NULL) return -11;

	cmd-> item-> operation = op;
	sprintf(cmd-> item-> name, "%s", name);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
void Concentration_CLI::load_commands() {
	int r;
	char name[32];
	cmdlist.clear();
	//sprintf(name, "list"); r = addcmd(cli_list, (char*) name);
	sprintf(name, "help"); r = addcmd(cli_help, (char*) name);	PRINT("addcmd = [%d]\n", r);
	sprintf(name, "dump"); r = addcmd(cli_dump, (char*) name);	PRINT("addcmd = [%d]\n", r);


}
//---------------------------------//---------------------------------
//int		cli_list(Concentration_CLI *cli, int argc, char **argv){	PRINT("cli_list..\n");	return 0;	}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_help(Concentration_CLI *cli, int argc, char **argv){
	PRINT("cli_help : -- HELP --\n");
	PRINT("cli_help : argc[%d]", argc);

	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	return argc;
}
//---------------------------------//---------------------------------
int		cli_dump(Concentration_CLI *cli, int argc, char **argv){
	PRINT("cli_dump..\n");
	DUMP(cli);
	return 0;
}
//---------------------------------//---------------------------------

//---------------------------------





