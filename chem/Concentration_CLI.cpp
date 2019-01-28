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
//---------------------------------//---------------------------------
class Concentration_CLI {
public:
	Concentration_VM			*core;
	char						lastline[MAX_LINELEN];

	mylist<CLI_Command>			base_cmdlist;
	mylist<CLI_Command>			dump_cmdlist;
	mylist<CLI_Command>			load_cmdlist;
	mylist<CLI_Command>			clear_cmdlist;
	mylist<CLI_Command>			stack_cmdlist;
	mylist<CLI_Command>			pep_cmdlist;
	mylist<CLI_Command>			mole_cmdlist;
	mylist<CLI_Command>			conc_cmdlist;

	mylist<CLI_Variable>		vars_list;


	Concentration_CLI(ConcentrationVolume &cvol, Concentration_VM &vm);
	virtual ~Concentration_CLI();
	void	load_commands();
	void 	dump();
	void 	test();

	int		addcmd(mylist<CLI_Command> *cmd_list, int 	(*op)(Concentration_CLI*, int, char**), char *name);
	int		run(mylist<CLI_Command> *cmd_list, int argc, char **argv);
	int		run(mylist<CLI_Command> *cmd_list, char *line);
	//Concentration	*search_conc(char *name);

	void	base_cmdlist_dump(void) { printf ("Basic Commands => ");  	base_cmdlist.dump(); }
	void	dump_cmdlist_dump(void) { printf ("'dump' Commands => ");  	dump_cmdlist.dump(); }
	void	load_cmdlist_dump(void) { printf ("'load' Commands => ");  	load_cmdlist.dump(); }
	void	stack_cmdlist_dump(void) { printf ("'stack' Commands => "); stack_cmdlist.dump(); }
	void	pep_cmdlist_dump(void) { printf ("'pep' Commands => ");  	pep_cmdlist.dump(); }
	void	mole_cmdlist_dump(void) { printf ("'mole' Commands => ");  mole_cmdlist.dump(); }
	void	conc_cmdlist_dump(void) { printf ("'conc' Commands => ");  	conc_cmdlist.dump(); }
};
//---------------------------------
//---------------------------------
*/
//---------------------------------
void Concentration_CLI::dump() {

//	printf("Concentration_CLI[0x%zX]:: concvol[0x%zX],conc[0x%zX],mole[0x%zX]\n",
//			(long unsigned int) this,
//			(long unsigned int) concvol,
//			(long unsigned int) conc,
//			(long unsigned int) mole );
	printf("Concentration_CLI[0x%zX]\n", (long unsigned int) this);
	base_cmdlist_dump(); 	//printf("'Base' Commands..\n");	base_cmdlist.dump();
	dump_cmdlist_dump(); 	//printf("'dump' Commands..\n");	dump_cmdlist.dump();
	load_cmdlist_dump(); 	//printf("'load' Commands..\n");	load_cmdlist.dump();
	clear_cmdlist_dump(); 	//printf("'clear' Commands..\n");	clear_cmdlist.dump();
	stack_cmdlist_dump(); 	//printf("'stack' Commands..\n");	stack_cmdlist.dump();
	pep_cmdlist_dump(); 	//printf("'pep' Commands..\n");	pep_cmdlist.dump();
	mole_cmdlist_dump(); 	//printf("'mole' Commands..\n");	mole_cmdlist.dump();
	conc_cmdlist_dump(); 	//printf("'conc' Commands..\n");	conc_cmdlist.dump();
	var_cmdlist_dump(); 	//printf("'var' Commands..\n");		var_cmdlist.dump();

	var_list_dump(); 		//printf("Variables..\n");		vars_list.dump();
}
//---------------------------------

Concentration_CLI::Concentration_CLI(ConcentrationVolume &cvol, Concentration_VM &vm) {
	memset(lastline, '\0', MAX_LINELEN);
	core = &vm;
	if (core!=NULL)
		core-> concvol = &cvol;
}
//---------------------------------
Concentration_CLI::~Concentration_CLI() {}

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

	strncpy(&lastline[0], line, MAX_LINELEN);
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
		printf(lastline, "");
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
		return -110;
	}
	if (cmd-> operation==NULL) {
		printf("[%s].Command.operation NULL\n", argv[0]);
		return -111;
	}

	int r = cmd-> operation(this, argc-1, &argv[1]);
	LOG("[%s].[%d]\n", argv[0], r);
	return r;
}
//---------------------------------
//---------------------------------//---------------------------------
void Concentration_CLI::load_commands() { 	cli_load_commands(this, 0, NULL);	}

//---------------------------------//---------------------------------
/*
Concentration	*Concentration_CLI::search_conc(char *name) {
	Concentration *result  = NULL;
	return result;
}
*/
