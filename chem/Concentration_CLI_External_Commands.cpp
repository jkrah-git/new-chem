/*
 * Concentration_CLI_External_Commands.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */


//---------------------------------//---------------------------------
//int		cli_list(Concentration_CLI *cli, int argc, char **argv){	PRINT("cli_list..\n");	return 0;	}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_quit(Concentration_CLI *cli, int argc, char **argv){	exit(0);	}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_ping(Concentration_CLI *cli, int argc, char **argv){
	PRINT("cli_help : -- PING --\n");
	PRINT("cli_help : argc[%d]", argc);

	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	return argc;
}
//---------------------------------//---------------------------------
int	cli_help(Concentration_CLI *cli, int argc, char **argv){	PRINT("cli_dump..\n");	DUMP(cli);	return 0; }
//---------------------------------//---------------------------------

//---------------------------------//---------------------------------
int		cli_dumpmoles(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;
	cli-> concvol->dumpmoles();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_concvol_test(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;
	cli-> concvol->test();
	return 0;
}//---------------------------------
//---------------------------------//---------------------------------
int	cli_dump(Concentration_CLI *cli, int argc, char **argv){

	if (cli==NULL) return -100;

	if (argc==0) {
		DUMP(cli-> concvol);
		return 0;
	}

	//-------
	PRINT("cli_dump: ----------\n");
	PRINT("cli_dump: -- DUMP --\n");
	PRINT("cli_dump: argc[%d]", argc);

	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	PRINT("cli_dump: ----------\n");

	return 	cli-> run(&cli-> dump_cmdlist, argc-1,  &argv[1]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_test(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;

	PRINT("dump_test: ----------\n");
	PRINT("dump_test: -- DUMP --\n");
	PRINT("dump_test: argc[%d]", argc);

	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	PRINT("dump_test: ----------\n");
	cli-> run(&cli-> dump_cmdlist, argc-1, &argv[1]);

	return 0;
}
//---------------------------------

//---------------------------------//---------------------------------
int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

	int r;
	char name[32];
	cli-> base_cmdlist.clear();
	cli-> dump_cmdlist.clear();

	//sprintf(name, "list"); r = addcmd(cli_list, (char*) name);
	sprintf(name, "quit"); 				r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 				r = cli-> addcmd(&cli-> base_cmdlist, 	cli_help, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "ping"); 				r = cli-> addcmd(&cli-> base_cmdlist, 	cli_ping, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 				r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "dumpmoles"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dumpmoles, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "concvol_test"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_concvol_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);

	// dump cmds
	sprintf(name, "test"); 				r =  cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);

	return 0;
}
