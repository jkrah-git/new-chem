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

//---------------
// cli_base.cpp
//---------------
int	cli_load_base(Concentration_CLI *cli, int argc, char **argv);
int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv);

//---------------
// cli_var,cpp
//---------------
int	cli_load_vars(Concentration_CLI *cli, int argc, char **argv);

//---------------
//cli_match.cpp
//---------------
int	cli_load_match(Concentration_CLI *cli, int argc, char **argv);

//---------------
//cli_vm.cpp
//---------------
int	cli_load_vm(Concentration_CLI *cli, int argc, char **argv);
int	cli_vm(Concentration_CLI *cli, int argc, char **argv);

int	cli_eng_load(Concentration_CLI *cli, int argc, char **argv);

//--------------- //--------------- //---------------
/*
// cli_dump.cpp
int     cli_dump(Concentration_CLI *cli, int argc, char **argv);
int     cli_dump_help(Concentration_CLI *cli, int argc, char **argv);
int     cli_dump_cli(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump_core(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump_stacks(Concentration_CLI *cli, int argc, char **argv);
int     cli_dump_moles(Concentration_CLI *cli, int argc, char **argv);
int     cli_dump_regs(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump_vol(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump_conc(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump_mole(Concentration_CLI *cli, int argc, char **argv);
int		cli_dump_pep(Concentration_CLI *cli, int argc, char **argv);
*/








#endif /* COMMAND_CALLBACKS_H_ */



