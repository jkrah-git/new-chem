/*
 * Concentration_CLI.h
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#ifndef CONCENTRATION_CLI_H_
#define CONCENTRATION_CLI_H_

#include "Concentration.h"
#include "CLI_Command.h"
#include "Concentration_VM.h"
#include "display/ChemDisplay.h"

#undef DEBUG
//#define DEBUG
#include "../include/debug.h"

/*  == cmds ==
 *  list (available nodes)
 *  dump conc, mole
 *  select conc, mole
 *
 */

#define MAX_ARGS 16
#define MAX_LINELEN 128
class Concentration_CLI;
//=================================================


//---------------------------------//---------------------------------
CLI_Command  *search_cmd_list(mylist<CLI_Command> *cmd_list, const char *name);
//-------------------------------------------
class Concentration_CLI {
private:
public:
	Concentration_VM			*core;
	int							last_result;
// TODO Superclass / list of lists
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
	char 						**args;

	//---------------
	ChemDisplay 				display;



	//void 	(*run_callback)(char *msg);
	int		(*callback)(Concentration_CLI*, int, char**);


	Concentration_CLI(ConcentrationVolume &cvol, Concentration_VM &vm);
	virtual ~Concentration_CLI();
	void	load_commands();
	void 	dump();
	void 	test();

	int		addcmd(mylist<CLI_Command> *cmd_list, int 	(*op)(Concentration_CLI*, int, char**), char *name);
	int		argstr(char *dest, int max, int argc, char **argv);
	int		runline(mylist<CLI_Command> *cmd_list, char *line);

	int		run(mylist<CLI_Command> *cmd_list, int argc, char **argv);

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
	char 	**get_possible_args(mylist<CLI_Command> *menu);

};
//---------------------------------

#endif /* CONCENTRATION_CLI_H_ */
