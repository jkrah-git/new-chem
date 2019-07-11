//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------
//---------------------------//---------------------------
int	cli_cell(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	//-------
	if (argc>0)	return 	cli-> run(&cli-> cell_cmdlist, argc,  &argv[0]);
	// else
	cli-> cell_cmdlist.dump();
	return 0;
}
//--------------//---------------------------
int	cli_cell_dump(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB
	//printf("(AmbientCell[0x%zX])->" , (long unsigned int) cli->selected_ambcell);
	cli->selected_ambcell->dump();
	NEED_CELL
	//cli->selected_ambcell-> cell->dump();
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_cell_dumpvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB
	//printf("(AmbientCell[0x%zX])->" , (long unsigned int) cli->selected_ambcell);
	cli->selected_ambcell->dump();
	NEED_CELL
	cli->selected_ambcell-> cell->vol.list();
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_cell_add(Concentration_CLI *cli, int argc, char **argv){
	// add a cell to a ambcell ..
	NEED_CLI NEED_WORLD NEED_AMB

	if (cli->selected_ambcell->cell !=NULL) { printf("Cell already present\n"); return -20; }

	cli->selected_ambcell->cell = new Cell;
	if (cli->selected_ambcell->cell==NULL) {
		printf("amb-cell Failed to add cell\n"); return -10;
	}
	// ** Important ** (set upstream molelist)
	cli->selected_ambcell->cell->vol.set_molelist(&cli->world->mole_list);
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_cell_temp(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB NEED_CELL
	if (argc>0) {
		float f;
		if (sscanf(argv[0], "%f", &f) <1) { printf("bad data\n"); return -20; }
		cli->selected_ambcell->cell->status.temperature.set(f, 0);
	}

	printf("cell.temp = [%.3f]\n", cli->selected_ambcell->cell->status.temperature.get());
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_cell_selvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB NEED_CELL

	cli-> local_vm.vol = &cli->selected_ambcell->cell-> vol;
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_cell_unselvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli-> local_vm.vol = NULL; // &cli-> local_vol;
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
int	load_cli_cell(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//-------
	int r;
	char name[32];
	//--------------
	// 'ENZ' (reg) commands
	cli-> cell_cmdlist.clear();
	sprintf(name, "cell");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_cell, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "add");	 	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_add, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");	 	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_dump, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dumpvol");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_dumpvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "selvol");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_selvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "unselvol");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_unselvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "temp");	 	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_temp, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
