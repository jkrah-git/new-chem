/*
 * command_callbacks.h
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#ifndef COMMAND_CALLBACKS_H_
#define COMMAND_CALLBACKS_H_

#include "chem/Concentration_CLI.h"
//--------------- //--------------- //---------------
int	cli_load_base(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_dump(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_pep(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_mole(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_conc(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_var(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_match(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_vm(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_stack(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_eng(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_vol(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_enz(Concentration_CLI *cli, int argc, char **argv);
int	load_cli_world(Concentration_CLI *cli, int argc, char **argv);

//int	cli_vm(Concentration_CLI *cli, int argc, char **argv);
Molecule *_cli_mole_fromargs(Concentration_CLI *cli, int argc, char **argv);
//int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv);


//---------------------------------------------------------------------
// ================================================================================================================
#define NEED_CLI 	if (cli==NULL) 			{ printf("NULL cli\n"); return -1; }
//#define NEED_VM  	if (cli-> core ==NULL) 	{ printf("NULL cli-> core\n"); return -2; }
#define NEED_VM 	Concentration_VM 	*vm = cli-> get_selected_vm();	if (vm==NULL) { printf("NULL vm\n"); return -2; }
#define NEED_VOL 	if (vm-> concvol==NULL) 	{ printf("NULL vol\n"); return -3; }
#define NEED_ENG 	if (cli-> chem_engine==NULL) { printf("NULL eng\n"); return -4; }



//--------------- //---------------
#endif /* COMMAND_CALLBACKS_H_ */






