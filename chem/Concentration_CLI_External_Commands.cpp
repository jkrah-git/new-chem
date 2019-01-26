/*
 * Concentration_CLI_External_Commands.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */


//---------------------------------//---------------------------------
//int		cli_list(Concentration_CLI *cli, int argc, char **argv){	PRINT("cli_list..\n");	return 0;	}
//---------------------------------//---------------------------------
//=======================
//===  BASE commands  ===
//=======================
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
int		cli_concvol_test(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;
	cli-> concvol->test();
	return 0;
}
//---------------------------------//---------------------------------


//---------------------------------//---------------------------------
//int	cli_dump(Concentration_CLI *cli, int argc, char **argv){
//=======================
//===  DUMP commands  ===
//=======================
//---------------------------------//---------------------------------
int	cli_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	// ----
	if (argc==0) {	DUMP(cli-> concvol); return 0;	}

	//-------
	LOG("cli_dump: ----------\n");
	LOG("cli_dump: -- DUMP --\n");
	LOG("cli_dump: argc[%d]", argc);

#ifdef DEBUG
	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	PRINT("cli_dump: ----------\n");
#endif
	return 	cli-> run(&cli-> dump_cmdlist, argc,  &argv[0]);
}
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
	//cli-> run(&cli-> dump_cmdlist, argc-1, &argv[1]);

	return 0;
}
//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_moles(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;
	cli-> concvol->dumpmoles();
	return 0;
}
//---------------------------------//---------------------------------
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//===  LOAD commands  ===
//=======================
//---------------------------------//---------------------------------
int	cli_load(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	// ----
	if (argc==0) {	return -200;	}

	//-------
	LOG("cli_load: ----------\n");
	LOG("cli_load: -- LOAD --\n");
	LOG("cli_load: argc[%d]", argc);

#ifdef DEBUG
	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	PRINT("cli_load: ----------\n");
#endif
	return 	cli-> run(&cli-> load_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_load_test(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;

	PRINT("load_test: ----------\n");
	PRINT("load_test: -- LOAD --\n");
	PRINT("load_test: argc[%d]", argc);

	for (int i=0; i< argc; i++) {
		printf(", argv[%d]=[%s]", i, argv[i]);
	}
	printf("\n");
	PRINT("load_test: ----------\n");
	//cli-> run(&cli-> load_cmdlist, argc-1, &argv[1]);
	return 0;
}
//---------------------------------//---------------------------------
// Concentration[0x1C6F740]
int	cli_load_conc(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;

	if (argc!=1) {	PRINT("usage:  conc 0x1234567\n");		return 0;	}

	//PRINT("load conc[%s]..\n", argv[0]);
	long unsigned int ptr;
	 ptr = strtoul (argv[0], NULL, 0);
	 printf("load conc [0x%zX] ..\n", ptr);

	mylist<Concentration>::mylist_item<Concentration> *item = cli->concvol->conc_list.search( (Concentration*) ptr);
	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->conc = item-> item;

	return 0;
}

//=======================//=======================//=======================
//=======================//=======================
//=======================
//===  END ALL commands  ===
//=======================
//=======================//=======================
//=======================//=======================//=======================

// ---- load all commands (last step)
//---------------------------------//---------------------------------
int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

	int r;
	char name[32];
	cli-> base_cmdlist.clear();
	cli-> dump_cmdlist.clear();
	cli-> load_cmdlist.clear();

	//sprintf(name, "list"); r = addcmd(cli_list, (char*) name);
	sprintf(name, "quit"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_help, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "ping"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_ping, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	//sprintf(name, "dumpmoles"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dumpmoles, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	sprintf(name, "concvol_test"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_concvol_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);

	// dump cmds
	sprintf(name, "dump"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	  sprintf(name, "test");		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	  sprintf(name, "moles"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_moles, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);

	sprintf(name, "load"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_load, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	  sprintf(name, "test"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_test, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);
	  sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_conc, (char*) name);	PRINT("addcmd[%s] = [%d]\n", name, r);



	return 0;
}
//---------------------------------//---------------------------------
