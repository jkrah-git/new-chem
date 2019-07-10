//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------
//---------------------------//---------------------------
int	cli_world(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	//-------
	if (argc>0)	return 	cli-> run(&cli-> world_cmdlist, argc,  &argv[0]);
	// else
	cli-> world_cmdlist.dump();
	return 0;
}
//--------------//---------------------------
int	cli_world_dump(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	cli->world->ambcell_list.dump();
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
	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_world_ld(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD

	mylist<AmbientCell>::mylist_item<AmbientCell>  *item = NULL;
	if (argc<1) {
		item = cli->world->ambcell_list.gettail();
	} else {
		int s;
		//-------------------
		if (argc==1) {
			if (strcmp(argv[0], "null" ) == 0) { cli->selected_ambcell = NULL; return 0; }
			if (sscanf(argv[0], "%x", &s) <0) { printf("Bad Data\n"); return -20; }
			// else
			item = cli->world->ambcell_list.offset(s);
		}  // end argc==1
		//-------------------
		if (argc==2) {
			CellPos pos;
			if ((sscanf(argv[0], "%x", &pos.dim[CELLPOS_X]) <0)||
				(sscanf(argv[1], "%x", &pos.dim[CELLPOS_Y]) <0))	{ printf("Bad Data\n"); return -20; }
			// AmbientCell *World::get_ambcell(CellPos *_pos){
			//pos.dump();
			AmbientCell *ambcell = cli->world->get_ambcell(&pos);
			if (ambcell==NULL) return -10;
			else { cli->selected_ambcell = ambcell; return 0; }
		}// end argc==2
		//-------------------
	}

	if (item==NULL) return -10;
	if (item->item ==NULL) return -11;
	cli->selected_ambcell = item->item;
	return 0;
}
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
	sprintf(name, "add");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_add, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_ld, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "addvol");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_addvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "selvol");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_selvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "unselvol");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_unselvol, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "temp");	 	r = cli-> addcmd(&cli-> world_cmdlist, 	cli_world_temp, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
