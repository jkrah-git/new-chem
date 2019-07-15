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
	//printf("------  ambcell_list ----\n");
	//cli->world->ambcell_list.dump();
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
	if (cli->selected_vm==NULL) { printf("<NULL vm>\n");	}
	else {
		if (cli-> selected_vm-> vol==NULL)  { printf("<NULL>\n");	}
		else {
			if (cli-> selected_vm-> vol == cli->selected_ambcell->ambvol) {
				printf("AmbientCell[0x%zX].vol\n", (PTR) cli-> selected_ambcell);	}
			if ((cli->selected_ambcell-> cell!=NULL) && (cli-> selected_vm-> vol == &cli->selected_ambcell->cell-> vol)) {
				printf("selected_ambcell.cell[0x%zX].vol\n", (PTR) cli->selected_ambcell->cell);
			}
		}
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

	//--------------------
//	_cli_world_print_selection(cli);
//	if (cli->selected_ambcell==NULL){ printf("selected_ambcell is NULL\n");	}
//	else 							{ printf("selected_ambcell = "); cli->selected_ambcell->pos.dump(); NL	}

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

	//printf("pos=[0x%x, 0x%x]\n", x, y);
	//p.dump();
	//AmbientCell *World::add_cell(CellPos *_pos){
	AmbientCell *amb = 	cli->world-> add_ambcell(&p);
	if (amb==NULL) { printf("world-> add_cell[%d,%d] failed..\n", x, y); return -30; }
	//amb->dump(); NL;

	cli->selected_ambcell = amb;
	//-----------
	//if (cli->selected_ambcell==NULL) {	printf("selected_ambcell is NULL\n");	}
	//else {	printf("selected_ambcell = "); cli->selected_ambcell->pos.dump(); NL }
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
		ambcell = cli->world->get_ambcell(&pos);
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
/*******************
	if (item==NULL) return -10;
	if (item->item ==NULL) return -11;
	cli->selected_ambcell = item->item;
	return 0;
}
*******************/
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_world_temp(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM
	if (cli->selected_ambcell==NULL) { printf("Need to select ambcell\n"); return -10; }
	if (argc>0) {
		float f;
		if (sscanf(argv[0], "%f", &f) <1) { printf("bad data\n"); return -20; }
//		if (f<0) {
		//printf("remove[%.3f] = [%.3f]\n", );
//		}
//		if (f>0) { printf("add[%.3f] = [%.3f]\n", cli->selected_ambcell->temperature.add(f)); }
//		}
		cli->selected_ambcell-> temperature.set(f, 0);
	}

	printf("ambcell.temp = [%.3f]\n", cli->selected_ambcell-> temperature.get());
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_world_addvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM
	if (cli->selected_ambcell==NULL) { printf("Need to select ambcell\n"); return -10; }
	if (cli->selected_ambcell->ambvol!=NULL) { printf("ambcell already has amb-vol\n"); return -10; }
	cli->selected_ambcell->ambvol = new ConcentrationVolume;//(ConcentrationVolume*) malloc(sizeof(ConcentrationVolume));
	if (cli->selected_ambcell->ambvol==NULL) { printf("amb-cell Failed to add amb-vol\n"); return -10; }
	//	cli.local_vol.set_molelist(&world.mole_list);
	cli->selected_ambcell->ambvol->set_molelist(&cli->world->mole_list);
	return 0;
}
//---------------------------//---------------------------//---------------------------------//---------------------------------
//--------------//---------------------------
int	cli_world_selvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM
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
// TODO:
/*
 * 	int	get_reactions(ChemEngine *eng);
	int	run_reactions(ChemEngine *eng, ChemTime run_time);
	int	run_cell(ChemEngine *eng, ChemTime run_time){ return run_cell(eng, &vol, run_time); };
	int	run_cell(ChemEngine *eng, ConcentrationVolume *vol, ChemTime run_time);
 */

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
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
