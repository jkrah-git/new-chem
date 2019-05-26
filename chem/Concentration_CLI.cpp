/*
 * Concentration_CLI.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#include "Concentration_CLI.h"
#include <string.h>

// -------------------
//#include "Concentration_CLI_External_Commands.cpp"

#include "Concentration_CLI.Commands/base.cpp"
#include "Concentration_CLI.Commands/vars.cpp"
#include "Concentration_CLI.Commands/match.cpp"

// -------------------
//---------------------------------//---------------------------------
/*
//---------------------------------//---------------------------------
class Concentration_CLI {
public:
	Concentration_VM			*core;
	char						last_line[MAX_LINELEN];
	int							last_result;

	mylist<CLI_Command>			base_cmdlist;
	mylist<CLI_Command>			dump_cmdlist;
	mylist<CLI_Command>			load_cmdlist;
	mylist<CLI_Command>			clear_cmdlist;
	mylist<CLI_Command>			stack_cmdlist;
	mylist<CLI_Command>			pep_cmdlist;
	mylist<CLI_Command>			mole_cmdlist;
	mylist<CLI_Command>			conc_cmdlist;
	mylist<CLI_Command>			var_cmdlist;
	mylist<CLI_Command>			match_cmdlist;

	KeyValList					var_list;


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
	void	clear_cmdlist_dump(void) { printf ("'clear' Commands => ");	clear_cmdlist.dump(); }
	void	stack_cmdlist_dump(void) { printf ("'stack' Commands => "); stack_cmdlist.dump(); }
	void	pep_cmdlist_dump(void) { printf ("'pep' Commands => ");  	pep_cmdlist.dump(); }
	void	mole_cmdlist_dump(void) { printf ("'mole' Commands => ");  mole_cmdlist.dump(); }
	void	conc_cmdlist_dump(void) { printf ("'conc' Commands => ");  	conc_cmdlist.dump(); }
	void	var_cmdlist_dump(void) { printf ("'var' Commands => ");  	var_cmdlist.dump(); }
	void	match_cmdlist_dump(void) { printf ("'match' Commands=> "); 	match_cmdlist.dump(); }

	void	var_list_dump(void) { printf ("'Variables' => ");  			var_list.dump(); }

};
//---------------------------------
//---------------------------------
*/


char  **Concentration_CLI::get_possible_args(mylist<CLI_Command> *menu){

//	PRINT("start.possible_args[0x%zX]\n", (long unsigned int)  args);
	if (args!=NULL) {
		int c=0;
		while (args[c] != NULL)
			free(args[c++]);
		free(args);
		args = NULL;
	}

//	PRINT("free.possible_args[0x%zX]\n", (long unsigned int)  args);

	if (menu!=NULL) {
		// add one for NULL ptr at end of list..
		int c = menu->count()+1;
//		PRINT("c(count+1)=[%d]\n", c);

		args = (char **) malloc(sizeof(char*)*c);
//		PRINT("malloc=[0x%zX]\n",  (long unsigned int)  args);
		if (args==NULL) return NULL;


		int i=0;
		mylist<CLI_Command>::mylist_item<CLI_Command>  *item = menu-> gethead();
		while ((item!=NULL)&&(item-> item !=NULL)) {
			args[i] = strdup(item->item->name);
//			PRINT("arg[%d]=[%s]\n", i, args[i]);
			//
			item = item-> next;
			i++;
		}

		// terminate word array
		args[i] = NULL;
	//	PRINT("final_null[0x%zX]=[%d]\n", (long unsigned int)  args, i);
	}


	if (args!=NULL) {
		int c=0;
		while (args[c] != NULL) {
		//	printf("possible_args[%d]=[%s]\n", c, args[c]);
			c++;
		}
	}

	//possible_args = args;
	return args;
}
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
	//printf("last_result = [%d] : last_line = [%s]\n", last_result, last_line);
}
//---------------------------------

Concentration_CLI::Concentration_CLI(ConcentrationVolume &cvol, Concentration_VM &vm) {
	//memset(last_line, '\0', MAX_LINELEN);
	args = NULL;
	//possible_args[0] = NULL;
	last_result = 0;
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

	//PRINT("\n");
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

	// make a local copy
	char buf[MAX_LINELEN];
	strncpy(buf, line, MAX_LINELEN);


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
		//printf(lastline, "");
		return -10;
	}

	int r = run(cmd_list, c, argv);
	//if (strcmp(argv[0], ".") !=0) strncpy(last_line, line, MAX_LINELEN);

	return r;
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

	last_result = 0;
	if (cmd==NULL) {
		printf("[%s].Command Not Found\n", argv[0]);
		last_result =  -110;
	} else
		if (cmd-> operation==NULL) {
			printf("[%s].Command.operation NULL\n", argv[0]);
			last_result =  -111;
	}

	if (last_result>=0)  {
		last_result = cmd-> operation(this, argc-1, &argv[1]);
		LOG("[%s].[%d]\n", argv[0], last_result);
	}
	return last_result;
}
//---------------------------------
//---------------------------------//---------------------------------
void Concentration_CLI::load_commands() {
	//cli_load_commands(this, 0, NULL);
	cli_load_base(this, 0, NULL);
	cli_load_vars(this, 0, NULL);
	cli_load_match(this, 0, NULL);
}

//---------------------------------//---------------------------------
/*
Concentration	*Concentration_CLI::search_conc(char *name) {
	Concentration *result  = NULL;
	return result;
}
*/
