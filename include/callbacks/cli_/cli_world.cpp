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
	NEED_CLI	cli-> world.dump();	return 0;
}
//---------------------------//---------------------------
//--------------//---------------------------
int	cli_world_add(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	if (argc<2) { printf("usage: world add <x> <y>\n"); return -1; }
	int x,y;
	if ((sscanf(argv[0], "%x", &x)<1)||
		(sscanf(argv[1], "%x", &y)<1)) { printf("data err\n"); return -20; }
	CellPos p;
	p.dim[0] = x;
	p.dim[1] = y;

	//printf("pos=[0x%x, 0x%x]\n", x, y);
	//p.dump();
	//AmbientCell *World::add_cell(CellPos *_pos){
	AmbientCell *amb = 	cli->world.add_cell(&p);
	if (amb==NULL) { printf("world.add_cell[%d,%d] failed..\n", x, y); return -30; }
	amb->dump();
	return 0;

}
//---------------------------//---------------------------
//---------------------------------//---------------------------------
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
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
