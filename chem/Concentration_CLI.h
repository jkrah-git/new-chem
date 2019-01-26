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


class Concentration_CLI;
//=================================================


//---------------------------------//---------------------------------
class Concentration_CLI {
private:
	ConcentrationVolume 								*concvol;
	mylist<Concentration>::mylist_item<Concentration>	*conc;
	Molecule											*mole;

	mylist<CLI_Command>									cmdlist;

public:
	Concentration_CLI();
	virtual ~Concentration_CLI();
	void	load_commands();
	void 	dump();
	void 	test();
	int		addcmd(int 	(*operation)(Concentration_CLI*, int, char**), char *name);
	int		run(int argc, char **argv);
};


//---------------------------------
//Result	opcode_debug(Concentration_Engine *eng,		Concentration_Unit *exe_unit); 	// debug = T
int		cli_help(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump(Concentration_CLI *cli, int argc, char **argv);
//---------------------------------


#endif /* CONCENTRATION_CLI_H_ */
