#include "../command_callbacks.h"
//===  match commands  ===
//---------------------------------//---------------------------------
int	cli_match(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	if (argc<1) {
		cli->local_vm.matchpos.dump();
		return 0;
	}
	return 	cli-> run(&cli-> match_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
int	cli_match_dump(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli->local_vm.matchpos.dump();
	return 0;
}
//---------------------------------//---------------------------------
int	cli_match_m1(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli->local_vm. matchpos.setM1(cli->local_vm. mole);
	return 0;

}
//---------------------------------//---------------------------------
int	cli_match_m2(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli->local_vm. matchpos.setM2(cli->local_vm. mole);
	return 0;

}
//---------------------------------//---------------------------------
int	cli_match_enz(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_ENZ
	cli->local_vm. matchpos.setM2(cli->selected_enz->get_mole());
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_start(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	return cli->local_vm.matchpos.start();
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_rot(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	while (cli->local_vm. matchpos.nextpos() !=4) { ; }
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_next(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	int r = cli->local_vm. matchpos.match_item();
	//printf("=>[%d]<= -4=(END) -3=(NOMATCH) -2=(MISS) -1=(COLLISION) 0=(NEXT) 1=(MATCH) \n",r);
	printf("match [%d] = [",r );
	switch (r) {
	case -4: printf("END"); break;
	case -3: printf("NOMATCH"); break;
	case -2: printf("MISS"); break;
	case -1: printf("COLLISION"); break;
	case 0: printf("NEXT"); break;
	case 1: printf("MATCH"); break;
	}
	printf("]\n");
	return r;

}
//--------------------------------- //---------------------------------
int	cli_match_n(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	int r = cli->local_vm. matchpos.match_mole();
	printf("match [%d] = [",r );
	// // match_mole() returns -2=(save_err)  -1=(NOMATCH), 0=(END), 1=(MATCH)
	switch (r) {
	case -2: printf("SAVE ERR"); break;
	case -1: printf("NO MATCH"); break;
	case 0: printf("END"); break;
	case 1: printf("MATCH"); break;
	}

	printf("]\n");
	return r;

}
//--------------------------------- //---------------------------------
//--------------------------------- //---------------------------------
int	cli_match_clear(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli->local_vm. matchpos.clear();
	return 0;

}
//--------------------------------- //---------------------------------
int	load_cli_match(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	int r;
	char name[32];

	// 'MATCH' commands
	sprintf(name, "n"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_match_n, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "match"); r = cli-> addcmd(&cli-> base_cmdlist, 	cli_match, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	cli-> match_cmdlist.clear();
	sprintf(name, "m1"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_m1, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m2"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_m2, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enz"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_enz, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "start"); r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_start, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "next"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_next, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "n"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_n, (char*) name);			LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "rot"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_rot, (char*) name);		LOG("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_clear, (char*) name);	LOG("match_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
