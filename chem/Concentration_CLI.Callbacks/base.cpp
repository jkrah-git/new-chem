

//=======================
//===  BASE commands  ===
//=======================
//---------------------------------//---------------------------------
int		cli_quit(Concentration_CLI *cli, int argc, char **argv){	exit(0);	}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_echo(Concentration_CLI *cli, int argc, char **argv){
	return 0;
	/*
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> lastline!=NULL) {
		printf("%s", cli-> lastline);
		return 0;
	}
	return -1;
	*/
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_testrot(Concentration_CLI *cli, int argc, char **argv){
	Molecule m;
	m.testrot();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_loop(Concentration_CLI *cli, int argc, char **argv){
	//PRINT("cli_help : -- LOOP --\n");
	//-------
	 PRINT(": argc[%d]", argc);
	 for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	//-------
	 if (argc<2) {
		 printf("usage: loop NUM commands..\n");
		 return -1;
	 }


	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..

//	char oldline[MAX_LINELEN];
//	strncpy(oldline, cli-> last_line, MAX_LINELEN);

	int c=0;
	argc--;
	while (c++<count){
		printf("loop[%d/%d]:[", c, count);
		for (int i=0; i< argc; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]\n");
		int r = cli-> run(&cli-> base_cmdlist, argc,  &argv[1]);
		if (r!=0) printf("Run = [%d]\n", r);
	}

//	strncpy(cli-> last_line, oldline, MAX_LINELEN);


	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_loopz(Concentration_CLI *cli, int argc, char **argv){
	//PRINT("cli_help : -- LOOP --\n");
	//-------
	 PRINT(": argc[%d]", argc);
	 for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	//-------
	 if (argc<2) {
		 printf("usage: loop NUM commands..\n");
		 return -1;
	 }

	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..




	int r = -1;
	int c=0;
	argc--;
	while (c++<count){
		printf("loop[%d/%d]:[", c, count);
		for (int i=0; i< argc; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]\n");
		r = cli-> run(&cli-> base_cmdlist, argc,  &argv[1]);
		if (r!=0) { printf("Break = [%d]\n", r); break; }
	}

	return r;
}
//---------------------------------//---------------------------------
int		cli_multi(Concentration_CLI *cli, int argc, char **argv){
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	 printf("\n");
	//-------

	// start at arrgv[0]
	int start = 0;
	int end = 0;
	int c=0;
	while ((start <argc)&&(end <argc)) {
		//printf("chk[%d]:[%d]->[%d] -> argv[%s]\n", c, start, end, argv[end]);

		if (strcmp(argv[end], ";")==0) {
			c++;
			printf("CMD[%d] ([%d]->[%d]) = ", c, start, end);
			//printf("CMD[%d]=", c);
			if (start==end) printf("[%s]", argv[start]);
			else { for (int u=start; u<end; u++) { printf("[%s]", argv[u]);	}		}
			printf("=>");

			int r = cli-> run(&cli-> base_cmdlist, (end-start),  &argv[start]);
			if (r<0) printf("Run = [%d]\n", r);

			start = end+1;
		}
		end++;
	}
	// terminate
	end = argc;
	// finish processing as if there were a final ';'
	if (start < argc) {
		c++;
		printf("CMD[%d] ([%d]->[%d]) = ", c, start, end);
		//printf("CMD[%d]=", c);
		if (start==end) printf("[%s]", argv[start]);
		for (int u=start; u<end; u++) {
			printf("[%s]", argv[u]);
		}
		printf("=>");

		int r = cli-> run(&cli-> base_cmdlist, (end-start),  &argv[start]);
		if (r<0) printf("Run = [%d]\n", r);

	}
	return c;

}

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
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//PRINT("cli_file : -- FILE --\n");
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

    char name[32];
    char filename[48];
    if (argc<1) { sprintf(name, "test"); }
    else { sprintf(name, "%s", argv[0]); }
    sprintf(filename, "data/%s.chem", name);
    //PRINT("Open[%s]..(%s)\n", name, filename);
    if (strlen(name)<1)
    	return -2;

    //----------------------
    {
        FILE *fp;
        char str[MAXCHAR];
		fp = fopen(filename, "r");
		if (fp == NULL){
			PRINT("Could not open file [%s] !!\n",filename);
			return -10;
		}

		//----------------------
		while (fgets(str, MAXCHAR, fp) != NULL) {
			if ((strlen(str)>1) && (str[0] != '\n')){
				printf("%s", str);
				int r = cli-> runline(&cli-> base_cmdlist, str);
				if (r!=0) printf("Run = [%d]\n", r);
			}

		}
		fclose(fp);
    }

    return 0;
}
//---------------------------------//---------------------------------
int	cli_help(Concentration_CLI *cli, int argc, char **argv){
	PRINT("cli_dump..\n");	DUMP(cli);	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_basehelp(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//cli->base_cmdlist.dump();
	cli-> base_cmdlist_dump();
	//PRINT("cli_dump..\n");	DUMP(cli);
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

	if (argc<1) {

	//	if (cli->core-> concvol != NULL) {
	//		cli->core-> concvol-> dump();
	//		return 0;
	//	} //else
	//	return -1;
		cli-> dump();
		//cli-> dump_cmdlist_dump();
		return 0;
	}
	// else
	return 	cli-> run(&cli-> dump_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
int		cli_dump_help(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> dump_cmdlist_dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int		cli_dump_cli(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------//---------------------------------//---------------------------------
int		cli_dump_core(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> core-> dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_dump_stacks(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> core-> dumpstacks();
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
	if (cli->core-> concvol != NULL) {
		cli->core-> concvol-> dump();
		return 0;
	} else
		return -1;
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
		//cli-> core-> pep = NULL;
		//cli-> core-> mole = NULL;
		//cli-> core-> conc = NULL;
		printf("usage: clear pep|mnle|conc|all\n");
		return -1;
	}
	return 	cli-> run(&cli-> clear_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_clear_conc(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> conc = NULL;
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> mole = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_clear_pep(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> pep = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_clear_all(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli->core-> conc = NULL;
	cli->core-> mole = NULL;
	cli->core-> pep = NULL;
	return 0;
}



//---------------------------------//---------------------------------
//---------------------------------//---------------------------------

int	cli_load_base(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

	int r;
	char name[32];
	// 'BASE' commands
	PRINT("\n");
	cli-> base_cmdlist.dump();

	cli-> base_cmdlist.clear();
	PRINT("\n");
	sprintf(name, "quit"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "q"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "#"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_echo, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "testrot"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_testrot, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "?"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_basehelp, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_help, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ping"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_ping, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loop"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loop, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loopz"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loopz, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, ";"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_multi, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "file"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_file, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "f"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_file, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "s"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_stacks, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "r"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_regs, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "v"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_vol, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "p"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_pep, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_mole, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "c"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_conc, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "~p"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_clear_pep, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "~m"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_clear_mole, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "~c"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_clear_conc, (char*) name);		PRINT("base_cmdlist[%s] = [%d]\n", name, r);

	// 'DUMP' commands
	cli-> dump_cmdlist.clear();
	sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_help, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "cli"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_cli, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "core"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_core, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "stacks"); 	r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_stacks, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "stack"); 	r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_stack_dump, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "moles"); 	r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_moles, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "regs"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_regs, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "vol"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_vol, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_conc, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_mole, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> dump_cmdlist, 	cli_dump_pep, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);

	// 'LOAD' commands
	cli-> load_cmdlist.clear();
	sprintf(name, "load"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_load, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_conc, (char*) name);		PRINT("load_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_mole, (char*) name);		PRINT("load_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_pep, (char*) name);		PRINT("load_cmdlist[%s] = [%d]\n", name, r);

	// 'CLEAR' commands
	cli-> clear_cmdlist.clear();
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_clear, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_conc, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_mole, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_pep, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "all"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_all, (char*) name);		PRINT("clear_cmdlist[%s] = [%d]\n", name, r);


	return 0;
}
//---------------------------------//---------------------------------
