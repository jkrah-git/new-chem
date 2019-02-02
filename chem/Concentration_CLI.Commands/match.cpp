//=======================
//=======================
//===  match commands  ===
//=======================
//=======================

//---------------------------------//---------------------------------
int	cli_match(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> core->matchpos.dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> match_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_help(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
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
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (cli-> core-> mole ==NULL) {	printf("need to select mole..\n");	return -2;	}
	cli-> core-> matchpos.rotation = 6;
	cli-> core-> matchpos.setM1(cli-> core-> mole);
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_m2(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (cli-> core-> mole ==NULL) {	printf("need to select mole..\n");	return -2;	}
	cli-> core-> matchpos.rotation = 6;
	cli-> core-> matchpos.setM2(cli-> core-> mole);
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_start(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	//cli->core->matchpos.rotation = 5;
	//cli->core->matchpos.test_item = NULL;

	if (argc<1) {
		return cli->core->matchpos.start();
	}




	int rot;
	if ( sscanf(argv[0], "%d", &rot) <0) {
		printf("bad rot[%s].\n", argv[0]);
		return -20;
	}

	cli-> core-> matchpos.rotation = rot;
	cli-> core-> matchpos.rotatemole();
	return 0;

}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_rot(Concentration_CLI *cli, int argc, char **argv){

	int rot = 0;

	if (argc>0) {
		if ( sscanf(argv[0], "%d", &rot) <0) {
			printf("bad rot[%s].\n", argv[0]);
			return -20;
		}
	}
	cli-> core-> matchpos.rotation = rot;
	cli-> core-> matchpos.rotatemole();
	cli-> core-> matchpos.dump();
	return rot;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_match_next(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	//return cli->core->matchpos.nextmatch();
	int r = cli->core->matchpos.nextmatch();
	if (r==-1) r=0;
	//printf("nextmatch = [%d]\n", r);
	return r;

}
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int	cli_match_n(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	int r = cli->core->matchpos.nextmatch();
	printf(".. nextmatch = [%d]\n", r);
	if (r==-1) r=0;

	cli-> core-> matchpos.dump();
	cli-> core->matchpos.render();
	return r;

}
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int	cli_match_render(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	cli-> core->matchpos.render();
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
	sprintf(name, "n"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_match_n, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	cli-> match_cmdlist.clear();
	sprintf(name, "match"); r = cli-> addcmd(&cli-> base_cmdlist, 	cli_match, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_help, (char*) name);		PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m1"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_m1, (char*) name);		PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m2"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_m2, (char*) name);		PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "start"); r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_start, (char*) name);		PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "next"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_next, (char*) name);		PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "n"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_n, (char*) name);			PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "rot"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_rot, (char*) name);			PRINT("match_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "render"); 	r = cli-> addcmd(&cli-> match_cmdlist, 	cli_match_render, (char*) name);			PRINT("match_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
