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

//int	cli_vm(Concentration_CLI *cli, int argc, char **argv);
Molecule *_cli_mole_fromargs(Concentration_CLI *cli, int argc, char **argv);
//int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv);

//---------------

// todo
#define NEED_CLI if (cli==NULL) return -1;
#define NEED_VM if (cli->core ==NULL) return -1;



//--------------- //---------------
#endif /* COMMAND_CALLBACKS_H_ */






