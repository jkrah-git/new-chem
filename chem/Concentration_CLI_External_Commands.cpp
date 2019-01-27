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
	//-------
	 PRINT(": argc[%d]", argc);
	 for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	//-------

	return argc;
}
//---------------------------------//---------------------------------

#define MAXCHAR 1000
//---------------------------------//---------------------------------
int		cli_file(Concentration_CLI *cli, int argc, char **argv){
	PRINT("cli_file : -- FILE --\n");
	//-------
	 PRINT(": argc[%d]", argc);
	 for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	//-------

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "test.chem";

    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    //----------------------
    while (fgets(str, MAXCHAR, fp) != NULL) {
   	   	printf("%s", str);

		if (strlen(str)>0) {
			int r = cli-> run(&cli-> base_cmdlist, str);
			if (r!=0) printf("Run = [%d]\n", r);
		}

    }
    fclose(fp);

    return 0;
}
//---------------------------------//---------------------------------
int	cli_help(Concentration_CLI *cli, int argc, char **argv){
	PRINT("cli_dump..\n");	DUMP(cli);	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_concvol_test(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> concvol==NULL) return -2;

	cli-> core-> concvol->test();
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
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	if (argc<1) {	cli-> dump_cmdlist_dump();		return 0;	}
	return 	cli-> run(&cli-> dump_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_cli(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_core(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> core-> dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_dump_moles(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> concvol->dumpmoles();
	return 0;
}
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int	cli_dump_regs(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> dumpregs();
	return 0;
}
//---------------------------------//---------------------------------
int		cli_dump_vol(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> concvol-> dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_conc(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	DUMP(cli->core-> conc)
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_mole(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	DUMP(cli->core-> mole)
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_pep(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	DUMP(cli->core-> pep) NL
	return 0;
}
//---------------------------------//---------------------------------

//---------------------------------//---------------------------------
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//=======================
//===  LOAD commands  ===
//=======================
//=======================
//---------------------------------//---------------------------------
int	cli_load(Concentration_CLI *cli, int argc, char **argv){
	//if ((cli==NULL) || (cli-> concvol ==NULL)) return -1;
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	//-------
	 PRINT(": argc[%d]", argc);
	 for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	//-------
	if (argc<1) {	cli-> load_cmdlist_dump();	return 0;	}

	return 	cli-> run(&cli-> load_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
// Concentration[0x1C6F740]
int	cli_load_conc(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	if (argc!=1) {		PRINT("usage:  conc 0x1234567\n");		return 0;	}

	long unsigned int ptr;
	 ptr = strtoul (argv[0], NULL, 0);
	 printf("load conc [0x%zX] ..\n", ptr);

	mylist<Concentration>::mylist_item<Concentration> *item = cli->core-> concvol->conc_list.search( (Concentration*) ptr);
	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->core-> conc = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
// Molecule[0x17C4670]
int	cli_load_mole(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	if (argc!=1) {		PRINT("usage:  load mole 0x1234567\n");		return 0;	}

	long unsigned int ptr;
	 ptr = strtoul (argv[0], NULL, 0);
	 printf("load conc [0x%zX] ..\n", ptr);

 	mylist<Molecule>::mylist_item<Molecule> *item;
 	item = cli->core-> concvol->mole_list.search( (Molecule*) ptr);


	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->core-> mole = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
// Concentration[0x1C6F740]
int	cli_load_pep(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	if (argc!=1) {		PRINT("usage:  load pep 0x1234567\n");		return 0;	}
	if (cli->core-> mole ==NULL) {		PRINT("err:  need to load mole first\n");		return 0;	}

	long unsigned int ptr;
	 ptr = strtoul (argv[0], NULL, 0);
	 printf("load pep [0x%zX] ..\n", ptr);

	mylist<Peptide>::mylist_item<Peptide> *item;
	item = cli->core-> mole-> pep_list.search( (Peptide*) ptr);

	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->core-> pep = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//=======================
//===  CLEAR commands  ===
//=======================
//=======================
//---------------------------------//---------------------------------
int	cli_clear(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> core-> pep = NULL;
		cli-> core-> mole = NULL;
		cli-> core-> conc = NULL;
		return 0;
	}
	return 	cli-> run(&cli-> clear_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
// Concentration[0x1C6F740]
int	cli_clear_conc(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> conc = NULL;
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
// Molecule[0x17C4670]
int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> mole = NULL;
	return 0;
}
//---------------------------------//---------------------------------
// Concentration[0x1C6F740]
int	cli_clear_pep(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> pep = NULL;
	return 0;
}

//---------------------------------//---------------------------------
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//=======================
//===  STACK commands  ===
//=======================
//=======================


//---------------------------------//---------------------------------
int	cli_stack(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> stack_cmdlist_dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> stack_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
int	cli_stack_dump(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli->core-> dumpstacks();	 printf(".. use [pep|mole|conc to filter dump.\n");
	} else {
		if (strcmp(argv[0], "pep") ==0)  {	printf("peptide_stack ==> ");	 cli->core->  peptide_stack.dump();	 }
		if (strcmp(argv[0], "mole") ==0) {	printf("molecule_stack ==> ");	 cli->core-> molecule_stack.dump();	 }
		if (strcmp(argv[0], "conc") ==0) {	printf("concentration_stack ==> ");	 cli->core-> concentration_stack.dump();	 }
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_stack_clear(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		printf("usage: stack clear pep|mole|conc to select.\n");
	} else {
		if (strcmp(argv[0], "pep") ==0)  {	printf("peptide_stack ==> ");	 cli->core->  peptide_stack.clear();	 }
		if (strcmp(argv[0], "mole") ==0) {	printf("molecule_stack ==> ");	 cli->core-> molecule_stack.clear();	 }
		if (strcmp(argv[0], "conc") ==0) {	printf("concentration_stack ==> ");	 cli->core-> concentration_stack.clear();	 }
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
/*
int	cli_stack_push(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		 printf(".. use [pep|mole|conc to push item.\n");
		 return 0;
	} // else

	 if (strcmp(argv[0], "pep") ==0)  {	//cli-> core-> pushpep(cli-> core-> pep);	 }
		mylist<Peptide>::mylist_item<Peptide>  *new_pep = NULL;
		new_pep = cli-> core-> peptide_stack.add();
		if (new_pep ==NULL) return -1;
		if (cli-> core-> pep==NULL) {
			cli-> core-> pep = new_pep-> item;
		} else {
			*new_pep-> item = *cli-> core-> pep;
		}
		return 0;
		cli_pep_push(cli, argc, argv);
	 }

	 if (strcmp(argv[0], "mole") ==0) {	printf("molecule_stack ==> ");	 cli->core-> molecule_stack.dump();	 }
	 if (strcmp(argv[0], "conc") ==0) 	  {	printf("concentration_stack ==> ");	 cli->core-> concentration_stack.dump();	 }

	return 0;
}
*/
//---------------------------------//---------------------------------
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//=======================
//===  PEP commands  ===
//=======================
//=======================
//---------------------------------//---------------------------------
int	cli_pep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> pep_cmdlist_dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> pep_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_push(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	//-------
	mylist<Peptide>::mylist_item<Peptide>  *new_item;
	if (argc==0) {
		new_item = cli-> core-> peptide_stack.add();
		if (new_item ==NULL) return -10;
		if (new_item-> item ==NULL) return -11;

		if (cli-> core-> pep==NULL) {
			cli-> core-> pep = new_item-> item;
		} else {
			*new_item-> item = *cli-> core-> pep;
		}

	} else {
		for (int i=0; i<argc; i++) {
			new_item = cli-> core-> peptide_stack.add();
			if (new_item ==NULL) return -10;
			if (new_item-> item ==NULL) return -11;

			int hex;
			if ( sscanf(argv[i], "0x%x", &hex) <0) {
				printf("bad sig[%s].\n", argv[0]);
				return -20;
			}
			PepSig sig = hex;
			new_item-> item-> set(sig);
		}
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_pop(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Peptide>::mylist_item<Peptide>  *tail = cli-> core-> peptide_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	//*cli-> core-> pep = *tail-> item;
	if (cli-> core-> pep == tail-> item) {
		cli-> core-> pep = NULL;
	}
	cli-> core-> peptide_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_ld(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Peptide>::mylist_item<Peptide>  *item = NULL;

	if (argc<1) {
		item = cli-> core-> peptide_stack.gettail();
	} else {
		int off;
		if ( sscanf(argv[0], "%d", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		//printf("..load [%d]\n", off);
		item = cli-> core-> peptide_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	cli-> core-> pep = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_hex(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		printf("usage: pep hex 0x(sig)\n");
		return -123;
	}

	int hex;
	if ( sscanf(argv[0], "0x%x", &hex) <0) {
		printf("bad sig[%s].\n", argv[0]);
		return -20;
	}
	PepSig sig = hex;
	if (cli-> core-> pep !=NULL) {
		cli-> core-> pep-> set(sig);
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//=======================
//=======================
//===  MOLE commands  ===
//=======================
//=======================

//TODO - stack -  dump|push|pop|clear  pep|mole|conc
//---------------------------------//---------------------------------
int	cli_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> mole_cmdlist_dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> mole_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_push(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Molecule>::mylist_item<Molecule>  *new_item = NULL;
	new_item = cli-> core-> molecule_stack.add();
	if (new_item ==NULL) return -10;
	if (new_item-> item ==NULL) return -11;

	if (cli-> core-> mole==NULL) {
		cli-> core-> mole = new_item-> item;
	} else {
		*new_item-> item = *cli-> core-> mole;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_pop(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Molecule>::mylist_item<Molecule>  *tail = cli-> core-> molecule_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	//*cli-> core-> pep = *tail-> item;
	if (cli-> core-> mole == tail-> item) {
		cli-> core-> mole = NULL;
	}
	cli-> core-> molecule_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_ld(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	mylist<Molecule>::mylist_item<Molecule>  *item = NULL;

	if (argc<1) {
		item = cli-> core-> molecule_stack.gettail();
	} else {
		int off;
		if ( sscanf(argv[0], "%d", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		//printf("..load [%d]\n", off);
		item = cli-> core-> molecule_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	cli-> core-> mole = item-> item;

/// old
//	if (argc<1) {
//		cli-> mole_cmdlist_dump();
//		return 0;
//	} // else
//
//	return 	cli-> run(&cli-> mole_cmdlist, argc,  &argv[0]);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_build(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> mole==NULL)  return -10;

	mylist<Peptide>::mylist_item<Peptide>  *item = cli-> core-> peptide_stack.gethead();
	while ((item!=NULL) && (item-> item!=NULL)) {
		cli-> core-> mole->addpep(item-> item-> get());
		// ---
		item = item-> next;
	}



	if (argc<1) {
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//=======================
//===  CONC commands  ===
//=======================
//=======================


//---------------------------------//---------------------------------
int	cli_conc(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> conc_cmdlist_dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> conc_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------

//=======================
//---------------------------------//---------------------------------
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

	// base commands
	cli-> base_cmdlist.clear();
	sprintf(name, "quit"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_help, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ping"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_ping, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "file"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_file, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "core"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_core, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "concvol_test"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_concvol_test, (char*) name);	PRINT("base_cmdlist[%s] = [%d]\n", name, r);

	// 'dump' commands
	cli-> dump_cmdlist.clear();
	sprintf(name, "dump"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "cli"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_cli, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "core"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_core, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "moles"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_moles, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "stack"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_stack_dump, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "regs"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_regs, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "vol"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_vol, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_conc, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_mole, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_pep, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);

	// 'load' commands
	cli-> load_cmdlist.clear();
	sprintf(name, "load"); 			r = cli-> addcmd(&cli-> base_cmdlist, 	cli_load, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_conc, (char*) name);		PRINT("load_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_mole, (char*) name);		PRINT("load_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_pep, (char*) name);		PRINT("load_cmdlist[%s] = [%d]\n", name, r);

	// 'clear' commands
	cli-> clear_cmdlist.clear();
	sprintf(name, "clear"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_clear, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_conc, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_mole, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_pep, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);

	// 'stack' commands
	cli-> stack_cmdlist.clear();
	sprintf(name, "stack"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_stack, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_dump, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	  //sprintf(name, "push"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_push, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);

	// 'pep' commands
	cli-> pep_cmdlist.clear();
	sprintf(name, "pep");	 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_pep, (char*) name);				PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "push"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_push, (char*) name);		PRINT("pep_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_pop, (char*) name);			PRINT("pep_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "ld"); 			r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_ld, (char*) name);			PRINT("pep_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "hex"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_hex, (char*) name);			PRINT("pep_cmdlist[%s] = [%d]\n", name, r);

	// 'mole' commands
	cli-> mole_cmdlist.clear();
	sprintf(name, "mole");	 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_mole, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "push"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_push, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_pop, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	  sprintf(name, "ld"); 			r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_ld, (char*) name);			PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
    sprintf(name, "build"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_build, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);


	// 'conc' commands
	cli-> conc_cmdlist.clear();
	sprintf(name, "conc");	 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_conc, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	//  sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_dump, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
//---------------------------------//---------------------------------
