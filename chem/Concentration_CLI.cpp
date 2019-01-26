/*
 * Concentration_CLI.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#include "Concentration_CLI.h"
#include <string.h>

// -------------------
#include "Concentration_CLI_External_Commands.cpp"
// -------------------
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

Concentration_CLI::Concentration_CLI(ConcentrationVolume &cvol) {
	concvol  = &cvol;
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
	printf("BaseCommands..\n");
	base_cmdlist.dump();
	printf("Concentration Commands..\n");
	dump_cmdlist.dump();

}
//---------------------------------
void Concentration_CLI::test() {
	PRINT(" .. START .. \n");
	PRINT("==============\n");
	PRINT(" .. pre dump =>\n"); dump();
	PRINT("==============\n");

	mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = base_cmdlist.add();
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
	PRINT(" .. run '%s' =>\n", arg0); r = run(&base_cmdlist, 1, argl); PRINT(".. (%s)=(%d)\n", arg0, r);
	PRINT(" .. run '%s' =>\n", arg0); r = run(&base_cmdlist, 2, argl); PRINT(".. (%s)=(%d)\n", arg0, r);

	//-----
	PRINT("==============\n");
	PRINT(" .. final dump ..\n"); dump();
	PRINT("==============\n");
	PRINT(" .. END ..\n");
}
//---------------------------------
int	Concentration_CLI::run2(char *line){
	if (line==NULL) return -100;

	char	*word, *argv[MAX_ARGS];
	int c = 0;
	word = strtok (line," \n");
	if (word!=NULL) {
		for (int i=0; i<MAX_ARGS; i++) {
			c++;
			argv[i] = word;
			word = strtok (NULL," \n");
			if (word==NULL) break;
		}
	}
	// check split results
	if (c<1) {
		//printf("line read error\n");
		return -10;
	}

	return run(&base_cmdlist, c, argv);
}
//---------------------------------
/*
int	Concentration_CLI::run2(int argc, char **argv){
	if ((argc<1) || (argv==NULL)) return -100;

	//mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = cmdlist.add();

	// search for argv[0]
	CLI_Command  *cmd = NULL;
	mylist<CLI_Command>::mylist_item<CLI_Command>  *next_item = base_cmdlist.gethead();
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
	LOG("[%s].[%d]\n", argv[0], r);
	return r;
}
//---------------------------------
int	Concentration_CLI::addcmd2(int 	(*op)(Concentration_CLI*, int, char**), char *name){
	if ((op==NULL)||(name==NULL)) return -1;

	mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = base_cmdlist.add();
	if (cmd==NULL) return -10;
	if (cmd-> item ==NULL) return -11;

	cmd-> item-> operation = op;
	sprintf(cmd-> item-> name, "%s", name);
	return 0;
}



*/

//---------------------------------//---------------------------------//---------------------------------
int	Concentration_CLI::addcmd(mylist<CLI_Command> *cmd_list, int 	(*op)(Concentration_CLI*, int, char**), char *name){
	if ((op==NULL)||(name==NULL)||(cmd_list==NULL)) return -1;

	mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = cmd_list-> add();
	if (cmd==NULL) return -10;
	if (cmd-> item ==NULL) return -11;

	cmd-> item-> operation = op;
	sprintf(cmd-> item-> name, "%s", name);
	return 0;
}
//---------------------------------
//---------------------------------
int	Concentration_CLI::run(mylist<CLI_Command> *cmd_list, char *line) {
	if ((cmd_list==NULL) || (line==NULL)) return -100;

	char	*word, *argv[MAX_ARGS];
	int c = 0;
	word = strtok (line," \n");
	if (word!=NULL) {
		for (int i=0; i<MAX_ARGS; i++) {
			c++;
			argv[i] = word;
			word = strtok (NULL," \n");
			if (word==NULL) break;
		}
	}
	// check split results
	if (c<1) {
		//printf("line read error\n");
		return -10;
	}

	return run(cmd_list, c, argv);
}
//---------------------------------
int	Concentration_CLI::run(mylist<CLI_Command> *cmd_list, int argc, char **argv){
	if ((cmd_list==NULL) || (argc<1) || (argv==NULL)) return -100;

	//mylist<CLI_Command>::mylist_item<CLI_Command>  *cmd = cmdlist.add();

	// search for argv[0]
	CLI_Command  *cmd = NULL;
	mylist<CLI_Command>::mylist_item<CLI_Command>  *next_item = cmd_list-> gethead();
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
	LOG("[%s].[%d]\n", argv[0], r);
	return r;
}
//---------------------------------

//---------------------------------//---------------------------------
//#define CLI_ADD_CMD(PFX) sprintf(name, #PFX); r = addcmd(cli_#PFX, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r)
//---------------------------------//---------------------------------
void Concentration_CLI::load_commands() {
	// int	load_commands(Concentration_CLI *cli, int argc, char **argv){
	cli_load_commands(this, 0, NULL);
	return;
/*
	int r;
	char name[32];
	cmdlist.clear();
	//sprintf(name, "list"); r = addcmd(cli_list, (char*) name);
	sprintf(name, "quit"); 				r = addcmd(cli_quit, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 				r = addcmd(cli_help, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "ping"); 				r = addcmd(cli_ping, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 				r = addcmd(cli_dump, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 				r = addcmd(cli_dump, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "dumpmoles"); 		r = addcmd(cli_dumpmoles, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "concvol_test"); 		r = addcmd(cli_concvol_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);


	// dump cmds
	sprintf(name, "test"); 		r = addcmd(cli_concvol_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
*/

}

