//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
#include "common.h"
//---------------------------
//---------------------------//---------------------------
int	cli_world(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	//-------
	if (argc>0)	{
		int r = cli-> run(&cli-> world_cmdlist, argc,  &argv[0]);
		_cli_world_print_selection(cli, argc, argv);
		return r;
	}
	// else
	cli-> world_cmdlist.dump();
	_cli_world_print_selection(cli, argc, argv);
	return 0;
}
//--------------//---------------------------
int	cli_world_dump(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	cli->world->dump();
	return 0;
}
//---------------------------//---------------------------
int _cli_world_print_selection(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	printf(".............\n");
	printf("[selected_ambcell][0x%zX] = ", (PTR) cli-> selected_ambcell);
	if (cli->selected_ambcell==NULL){ printf("<NULL>\n");	}
	else 							{ cli->selected_ambcell->pos.dump(); NL	}

	printf("[vm.vol] = ");
	if (cli->local_vm.vol==NULL)  { printf("<NULL>\n");	}
	else {
		if (cli->local_vm.vol == cli->selected_ambcell->ambvol) {
			printf("AmbientCell[0x%zX].vol\n", (PTR) cli-> selected_ambcell);	}
		else if ((cli->selected_ambcell-> cell!=NULL) && (cli->local_vm.vol == &cli->selected_ambcell->cell-> vol)) {
			printf("selected_ambcell.cell[0x%zX].vol\n", (PTR) cli->selected_ambcell->cell);
		}
		else printf("vol[0x%zX]\n", (PTR) cli->local_vm.vol);
	}
	return 0;
}
//--------------//---------------------------
int	cli_world_list(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if ((argc<1) || (strcmp(argv[0], "ambcell")==0)){ cli->world->ambcell_list.dump(); }

	int r = 0;
	//----------------------------
	if ((argc==1)&&(strcmp(argv[0], "vol")==0)){

		mylist<AmbientCell>::mylist_item<AmbientCell> *amb_item = cli->world->ambcell_list.gethead();
		while(amb_item!=NULL) {
			if (amb_item->item!=NULL) {
				printf("=============== Pos[%d, %d] ===============\n",
						amb_item->item ->pos.dim[CELLPOS_X],amb_item->item ->pos.dim[CELLPOS_Y]);

				amb_item->item -> dump(); printf("------------- Vol's\n");
				if (amb_item->item-> ambvol != NULL) {
					r = amb_item->item-> ambvol->get_conc_list()->  count();
					printf("... ambcell.ambvol(%d conc's) :", r);
					amb_item->item-> ambvol-> list();
				}

				if (amb_item->item->cell!=NULL)	{
					r = amb_item->item->cell->vol.get_conc_list()-> count();
					printf("... cell.vol (%d conc's) :", r);
					amb_item->item->cell->vol.list();
				}

			} // end item->item
			//------------
			amb_item = amb_item-> next;
		} // end while
		printf("===========================================\n");
	}
	//----------------------------
	//----------------------------
	if ((argc==1)&&(strcmp(argv[0], "heap")==0)){ cli->world->mole_list.dump(); return cli->world->mole_list.count(); }


	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_world_add(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if (argc<2) { printf("usage: world add <x> <y>\n"); return -1; }
	int x,y;
	if ((sscanf(argv[0], "%d", &x)<1)||
		(sscanf(argv[1], "%d", &y)<1)) { printf("data err\n"); return -20; }
	CellPos p;
	p.dim[0] = x;
	p.dim[1] = y;

	AmbientCell *amb = 	cli->world-> add_ambcell(&p);
	if (amb==NULL) { printf("world-> add_cell[%d,%d] failed..\n", x, y); return -30; }

	cli->selected_ambcell = amb;
	//-----------
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_world_ld(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD

	AmbientCell *ambcell = NULL;
	mylist<AmbientCell>::mylist_item<AmbientCell>  *item = NULL;
	if (argc<1) {
		item = cli->world->ambcell_list.gettail();
	}
	int s;
	//-------------------
	if (argc==1) {
		if (strcmp(argv[0], "null" ) == 0) {
			cli->selected_ambcell = NULL;
		} else {
			if (sscanf(argv[0], "%x", &s) <0) { printf("Bad Data\n"); return -20; }
			item = cli->world->ambcell_list.offset(s);
		}
	}  // end argc==1
	//-------------------
	if (argc==2) {
		CellPos pos;
		if ((sscanf(argv[0], "%x", &pos.dim[CELLPOS_X]) <0)||
			(sscanf(argv[1], "%x", &pos.dim[CELLPOS_Y]) <0))	{ printf("Bad Data\n"); return -20; }

		item = cli->world->get_ambcell(&pos);
	}// end argc==2
	//-------------------
	if (item !=NULL) {
		ambcell = item->item;
	}
	if (ambcell!=NULL) {
		cli->selected_ambcell = ambcell;
	}
	printf("selected :");
	if (ambcell==NULL) { printf("<NULL>\n"); }
	else {	ambcell->pos.dump(); NL	}


	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_world_temp(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if (cli->selected_ambcell==NULL) { printf("Need to select ambcell\n"); return -10; }
	if (argc>0) {
		float f;
		if (sscanf(argv[0], "%f", &f) <1) { printf("bad data\n"); return -20; }
		cli->selected_ambcell-> temperature.set(f, 0);
	}
	printf("ambcell.temp = [%.3f]\n", cli->selected_ambcell-> temperature.get());
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_world_addvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if (cli->selected_ambcell==NULL) { printf("Need to select ambcell\n"); return -10; }
	if (cli->selected_ambcell->ambvol!=NULL) { printf("ambcell already has amb-vol\n"); return -10; }

	cli->selected_ambcell->ambvol = new ConcentrationVolume;//(ConcentrationVolume*) malloc(sizeof(ConcentrationVolume));
	if (cli->selected_ambcell->ambvol==NULL) { printf("amb-cell Failed to add amb-vol\n"); return -10; }
	//	!! nb: world_molelist
	cli->selected_ambcell->ambvol->set_molelist(&cli->world->mole_list);
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_world_selvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if (cli->selected_ambcell==NULL) { printf("Need to select ambcell\n"); return -10; }
	if (cli->selected_ambcell->ambvol==NULL) { printf("ambcell has no ambvol\n"); return -10; }
	cli-> local_vm.vol = cli->selected_ambcell->ambvol;
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_world_unselvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli-> local_vm.vol = NULL; // &cli-> local_vol;
	return 0;
}
//--------------//---------------------------
// 	int	get_reactions(ChemEngine *eng);
//--------------//---------------------------
int	cli_world_get(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	int r = cli->world->get_reactions();
	printf("world get_reactions = [%d]\n", r);
	return r;
}
//--------------//---------------------------
//	int	World::run_reactions(ChemTime run_time){
//--------------//---------------------------
//--------------//---------------------------
int	cli_world_run(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	NEED_CLI NEED_WORLD
	float f = 1.0;
	if ((argc>0) && ( sscanf(argv[0], "%f" , &f) <0)) { printf("bad data..\n"); return -30; }

	int r = cli->world->run_reactions(f);
	printf("world run_reactions = [%d]\n", r);
	return r;
}
//--------------//---------------------------
//	int	World::finish_reactions(ChemEngine *eng){ //, ChemTime run_time){
//--------------//---------------------------
int	cli_world_commit(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	NEED_CLI NEED_WORLD
	int r = cli->world->finish_reactions();
	printf("world finish_reactions = [%d]\n", r);
	return r;
}

//int	World::run_world(ChemEngine *eng, ChemTime run_time){
// --------------------------
#include <time.h>
#include <unistd.h>
#include <stdio.h>
//--------------//---------------------------
int	cli_world_tick(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	float f = 1.0;
	int repeat = 1;
//	if ((argc>0) && ( sscanf(argv[0], "%f" , &f) <0)) { printf("bad data..\n"); return -30; }
	if (argc>0) { READF(f,0); }
	if (argc>1) { READI(repeat,1); }


	if (repeat==1) {
		int r = cli->world->run_world(f);
		printf("world tick = [%d]\n", r);
		return r;
	}

	//-------
	clock_t 	start_ticks = clock();
	time_t 		start_time;
	time(&start_time);
	int n = 0;

	//-------
	for (int i=0; i<repeat; i++) {
		if (cli->world->run_world(f) >=0) n++;
	}
	//-------
	clock_t end_ticks = clock();
	time_t end_time;
	time(&end_time);
	//-------

	long elapsed_ticks = ((long) (end_ticks - start_ticks)/1000);
	//printf("start_t[%ld], end_t[%ld] , elapsed_t[%ld]\n", start_t, end_t, elapsed_t);
	printf("world.run_world (x%d) took ..\n", repeat);
	printf("%.3f (sec) Real Time and %ld (msec) CPU Time\n", difftime(end_time, start_time), elapsed_ticks);

	return n;

}
//--------------//---------------------------
//---------------------------//---------------------------//---------------------------------//---------------------------------
int	load_cli_world(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//-------
	int r;
	char name[32];
	//--------------
	// 'ENZ' (reg) commands
	cli-> world_cmdlist.clear();
	sprintf(name, "world");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_world, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_dump, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "list");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_list, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "add");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_add, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld");		r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_ld, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "addvol");	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_addvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "selvol");	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_selvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "unselvol");	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_unselvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "temp");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_temp, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_get, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_run, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_commit, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tick");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_tick, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
