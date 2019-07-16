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
	cli->selected_ambcell->dump(); NL
//	if (cli->selected_ambcell-> cell!=NULL)
//		cli->selected_ambcell-> cell->dump();
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_cell_dumpvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB
	//printf("(AmbientCell[0x%zX])->" , (long unsigned int) cli->selected_ambcell);
	cli->selected_ambcell->dump(); NL
	if (cli->selected_ambcell-> cell!=NULL)
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
	cli->selected_ambcell->cell-> ambcell = cli->selected_ambcell;

	// ** Important ** (set upstream molelist)
	cli->selected_ambcell->cell->vol.set_molelist(&cli->world->mole_list);
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_cell_energy(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB NEED_CELL
	if (argc>0) {
		float f;
		if (sscanf(argv[0], "%f", &f) <1) { printf("bad data\n"); return -20; }
		cli->selected_ambcell->cell->status.energy.set(f, 0);
	}
	printf("cell.energy = [%.3f]\n", cli->selected_ambcell->cell->status.energy.get());
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_cell_health(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_AMB NEED_CELL
	if (argc>0) {
		float f;
		if (sscanf(argv[0], "%f", &f) <1) { printf("bad data\n"); return -20; }
		cli->selected_ambcell->cell->status.health.set(f, 0);
	}
	printf("cell.health = [%.3f]\n", cli->selected_ambcell->cell->status.health.get());
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
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
	_cli_world_print_selection(cli, argc, argv);
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
//--------------//---------------------------
int	cli_cell_applyconc(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_AMB NEED_CELL NEED_WORLD

	mylist<Concentration>::mylist_item<Concentration>  *item = NULL;

	float t = 1.0;
	if (argc<1) {
		item = vm-> concentration_stack.gettail();
		if (item ==NULL) {	printf("conc stack is empty\n");	return -30; }
	} else {
		int off;
		if (sscanf(argv[0], "%d", &off) <0) {	printf("bad offset [%s].\n", argv[0]);	return -20; }
		item = vm-> concentration_stack.offset(off);	if (item ==NULL) {	printf("conc load[%d] failed\n", off);	return -31; }
		if ((argc>1) && (sscanf(argv[1], "%f", &t) <0)) { printf("bad time [%s].\n", argv[1]); return -20; }
	}


	if (item-> item ==NULL) {	printf("null item->item\n");	return -31; }
	printf("run_time = [%.3f]\n", t);
	//item-> item->dump();
	return cli->selected_ambcell-> cell-> apply_concentration(&cli->world->chem_engine, vm->vol, item-> item, &cli->selected_ambcell-> cell->status, t);
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
// 	void Cell::commit(void){ energy.commit(); health.commit(); temperature.commit();  };
int	cli_cell_commit(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_AMB NEED_CELL
	if (argc==0) {
		cli->selected_ambcell-> cell->status.commit();
		//cli->selected_ambcell-> cell->vol.commit();
		printf("cell commit..\n");
		return 0;
		//CellStatusType eff = cli->selected_ambcell-> cell->status.efficiency();
	}
	return -49;
}
//--------------//---------------------------
//--------------//---------------------------
// int	Cell:get_reactions(ChemEngine *eng, AmbientCell *ambcell);
int	cli_cell_get(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_WORLD NEED_AMB NEED_CELL
	if (argc==0) {
		int r = cli->selected_ambcell-> cell-> get_reactions(&cli->world->chem_engine);
		printf(" cell->get_reactions = [%d]\n", r);
		return r;
	}
	return -49;
}
//--------------//---------------------------
// int	Cell:run_reactions(ChemEngine *eng, AmbientCell *ambcell, ChemTime run_time);
int	cli_cell_run(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_WORLD NEED_AMB NEED_CELL
	float t = 1.0f;

	if ((argc>0) && (sscanf(argv[0], "%f", &t)<1)) { printf("Bad Data\n"); return -20; }

	//int r = cli->selected_ambcell-> cell->run_reactions(&cli->world->chem_engine, cli->selected_ambcell, t);
//	int	run_cell(ChemEngine *eng, ConcentrationVolume *vol, AmbientCell *ambcell, ChemTime run_time);


	int r = cli->selected_ambcell-> cell->run_cell(&cli->world->chem_engine, t);

	printf(" cell->run_reactions[%f] = [%d]\n", t, r);

	return r;
}
//--------------//---------------------------
// int	Cell:run_cell(ChemEngine *eng, AmbientCell *ambcell, ChemTime run_time);
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
	sprintf(name, "energy");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_energy, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "health");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_health, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "temp");	 	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_temp, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "applyconc");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_applyconc, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_commit, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get");		r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_get, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run");		r = cli-> addcmd(&cli-> cell_cmdlist, 	cli_cell_run, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
