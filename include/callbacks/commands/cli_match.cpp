#include "../command_callbacks.h"
//=======================
//=======================
//===  match commands  ===
//=======================
//=======================
//#include "../../include/gfx/gfx.h"
//---------------------------------//---------------------------------
int	cli_match(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		vm->matchpos.dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> match_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_help(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	cli-> match_cmdlist_dump();
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_m1(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	//if (vm-> mole ==NULL) {	printf("need to select mole..\n");	return -2;	}
	//cli-> core-> matchpos.rotation = 6;
	vm-> matchpos.setM1(vm-> mole);
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_m2(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	//if (vm-> mole ==NULL) {	printf("need to select mole..\n");	return -2;	}
	//cli-> core-> matchpos.rotation = 6;
	vm-> matchpos.setM2(vm-> mole);
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_enz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	ChemEnzyme *enz = cli->selected_enz;
	if (enz==NULL) {	printf("need to select enz..\n");	return -2;	}

	//cli-> core-> matchpos.rotation = 6;
	PRINT("================\n");
	vm-> matchpos.setM2(enz->get_mole());
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_start(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//cli->core->matchpos.rotation = 5;
	//cli->core->matchpos.test_item = NULL;

	if (argc<1) {
		return vm->matchpos.start();
	}


	/*
	int rot;
	if ( sscanf(argv[0], "%d", &rot) <0) {
		printf("bad rot[%s].\n", argv[0]);
		return -20;
	}
	cli-> core-> matchpos.rotation = rot;
	//cli-> core-> matchpos.current_pos.dim[PEPPOS_ROT] = rot;
	cli-> core-> matchpos.rotatemole();
	*/

	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_rot(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

/*
	if (argc>0) {
		int rot = 0;
		if ( sscanf(argv[0], "%d", &rot) <0) {
			printf("bad rot[%s].\n", argv[0]);
			return -20;
		}
		vm-> matchpos.rotation = rot;
	}
*/
	vm-> matchpos.rotatemole();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_next(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r = vm-> matchpos.match_item();
	printf("=>[%d]<= -4=(END) -3=(NOMATCH) -2=(MISS) -1=(COLLISION) 0=(NEXT) 1=(MATCH) \n",r);
	return r;

}
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int	cli_match_n(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	int r = vm-> matchpos.match_mole();
	printf("=>[%d]<= [-1=(NOMATCH), 0=(END), 1=(MATCH)]\n", r);
	return r;

}
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int	cli_match_render(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm-> matchpos.render();
	return 0;


}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------

//=======================
//---------------------------------//---------------------------------
//=======================//=======================//=======================
//---------------------------------//---------------------------------
int	cli_load_match(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

	int r;
	char name[32];

	// 'STACK' commands
	sprintf(name, "n"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_match_n, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "match"); r = cli-> addcmd(&cli-> base_cmdlist, 	cli_match, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	cli-> match_cmdlist.clear();
	sprintf(name, "help"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_help, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m1"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_m1, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m2"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_m2, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enz"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_enz, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "start"); r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_start, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "next"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_next, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "n"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_n, (char*) name);			LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "rot"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_rot, (char*) name);			LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "render"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_render, (char*) name);			LOG("match_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
