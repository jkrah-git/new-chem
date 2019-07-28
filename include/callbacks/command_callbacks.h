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
int	load_cli_cell(Concentration_CLI *cli, int argc, char **argv);

//int	cli_vm(Concentration_CLI *cli, int argc, char **argv);
Molecule *_cli_mole_fromargs(Concentration_CLI *cli, int argc, char **argv);
//int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv);
int _cli_world_print_selection(Concentration_CLI *cli, int argc, char **argv);

//---------------------------------------------------------------------
// ================================================================================================================
#include "common.h"
#define NEED_CLI 	if (cli==NULL) 							{ printf("NULL cli\n"); 					return -1; }
#define NEED_WORLD	if (cli->world==NULL) 					{ printf("NULL world\n"); 					return -2; }
#define NEED_MOLE 	if (cli->local_vm.mole==NULL) 			{ printf("Need to select mole first\n"); 	return -3; }
#define NEED_CONC 	if (cli->local_vm.conc==NULL) 			{ printf("Need to select conc first\n"); 	return -4; }
#define NEED_VOL 	if (cli->local_vm.vol==NULL) 			{ printf("Need to select vol first\n"); 	return -5; }
#define NEED_AMB	if (cli->selected_ambcell ==NULL) 		{ printf("Need to select ambcell first\n"); return -6; }
#define NEED_CELL 	if (cli->selected_ambcell-> cell==NULL) { printf("Need to select cell first\n"); 	return -7; }
#define NEED_ENZ 	if (cli->selected_enz==NULL) 			{ printf("Need to select enzyme first\n"); 	return -8; }


//#define READI(i,c) { if ( sscanf(argv[c], "%d", &i) <0) {	printf("arg [%d] error: expected 'int' but got [%s].\n", c, argv[c]);	return -20;	} else { printf("read [%d]\n". i); } }
#define READI(i,c) if ( sscanf(argv[c], "%d", &i) <1) {	printf("error: arg [%d] expected 'int' but got '%s'.\n", c, argv[c]);	return -20;	}
#define READF(f,c) if ( sscanf(argv[c], "%f", &f) <1) {	printf("error: arg [%d] expected 'float' but got '%s'.\n", c, argv[c]);	return -20;	}

//--------------- //---------------
#endif /* COMMAND_CALLBACKS_H_ */






