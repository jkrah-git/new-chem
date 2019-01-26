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
#undef DEBUG
//#define DEBUG
#include "debug.h"

/*  == cmds ==
 *  list (available nodes)
 *  dump conc, mole
 *  select conc, mole
 *
 */

#define MAX_ARGS 16
class Concentration_CLI;
//=================================================


//---------------------------------//---------------------------------
class Concentration_CLI {
public:
	ConcentrationVolume 		*concvol;
	Concentration				*conc;
	Molecule					*mole;
	mylist<CLI_Command>			base_cmdlist;
	mylist<CLI_Command>			dump_cmdlist;
	mylist<CLI_Command>			load_cmdlist;


	Concentration_CLI(ConcentrationVolume &cvol);
	virtual ~Concentration_CLI();
	void	load_commands();
	void 	dump();
	void 	test();

	int		addcmd(mylist<CLI_Command> *cmd_list, int 	(*op)(Concentration_CLI*, int, char**), char *name);
	int		run(mylist<CLI_Command> *cmd_list, int argc, char **argv);
	int		run(mylist<CLI_Command> *cmd_list, char *line);
	Concentration	*search_conc(char *name);
};
//---------------------------------
// int		cli_quit(Concentration_CLI *cli, int argc, char **argv);
//---------------------------------


#endif /* CONCENTRATION_CLI_H_ */
