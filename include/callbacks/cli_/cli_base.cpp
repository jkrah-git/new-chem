#include "../command_callbacks.h"

//=======================
//===  BASE commands  ===
//=======================
#include <string.h>
//---------------------------------//---------------------------------
int		cli_quit(Concentration_CLI *cli, int argc, char **argv){	exit(0);	}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_loop(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	if (argc<2) { printf("usage: loop NUM commands..\n");	 return -1;	 }
	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop[%d/%d]:[", c+1, count);
		for (int i=0; i< argc-1; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-1,  &argv[1]);
		printf("[%d]\n", r);
		if (r>=0) n++;
	}
	return n;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_loopz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<2) { printf("usage: loop NUM commands..\n");	 return -1;	 }
	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop.z[%d/%d]:[", c+1, count);
		for (int i=0; i< argc-1; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-1,  &argv[1]);
		printf("[%d]\n", r);
		if (r!=0) return n;
		n++;
	}

	return n;
}
//---------------------------------//---------------------------------
int		cli_loopnz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<2) { printf("usage: loop NUM commands..\n");	 return -1;	 }
	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop.nz[%d/%d]:[", c+1, count);
		for (int i=0; i< argc-1; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-1,  &argv[1]);
		printf("[%d]\n", r);
		if (r==0) return n;
		n++;
	}

	return n;
}
//---------------------------------//---------------------------------
int		cli_looplz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<2) { printf("usage: loop NUM commands..\n");	 return -1;	 }
	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop.lz[%d/%d]:[", c+1, count);
		for (int i=0; i< argc-1; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-1,  &argv[1]);
		printf("[%d]\n", r);
		if (r>=0) return n;
		n++;
	}

	return n;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int		cli_loopnlz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<2) { printf("usage: loop NUM commands..\n");	 return -1;	 }
	int count;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop.nlz[%d/%d]:[", c+1, count);
		for (int i=0; i< argc-1; i++) {	if (i==0) printf("%s", argv[i+1]); else printf(" %s", argv[i+1]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-1,  &argv[1]);
		printf("[%d]\n", r);
		if (r<0) return n;
		n++;
	}

	return n;
}
//---------------------------------//---------------------------------
int		cli_loopeq(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<3) { printf("usage: loopeq COUNT eqVAL commands..\n");	 return -1;	 }
	int count, val;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	if ( sscanf(argv[1], "%d", &val) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop[%d/%d].eq[%d]:[", c+1, count, val);
		for (int i=0; i< argc-2; i++) {	if (i==0) printf("%s", argv[i+2]); else printf(" %s", argv[i+2]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-2,  &argv[2]);
		printf("[%d]\n", r);
		if (r!=val) return n;
		n++;
	}

	return n;
}
//---------------------------------//---------------------------------
int		cli_loopneq(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<3) { printf("usage: loopneq COUNT eqVAL commands..\n");	 return -1;	 }
	int count, val;
	if ( sscanf(argv[0], "%d", &count) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	if ( sscanf(argv[1], "%d", &val) <0) {
		printf("bad count [%s].\n", argv[0]);
		return -20;
	}
	// else..
	int n=0;
	for (int c=0; c<count; c++) {
		printf("loop[%d/%d].neq[%d]:[", c+1, count, val);
		for (int i=0; i< argc-2; i++) {	if (i==0) printf("%s", argv[i+2]); else printf(" %s", argv[i+2]);	}	printf("]=");
		int r = cli-> run(&cli-> base_cmdlist, argc-2,  &argv[2]);
		printf("[%d]\n", r);
		if (r==val) return n;
		n++;
	}

	return n;
}


//---------------------------------//---------------------------------
int		cli_multi(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	PRINT("cli_dump..\n");	DUMP(cli);	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_basehelp(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
//int	cli_load_commands(Concentration_CLI *cli, int argc, char **argv){
//=======================
//=======================
//===  LOAD commands  ===
//=======================
//=======================
/***************************************
//---------------------------------//---------------------------------
int	cli_load(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if (vm-> concvol==NULL) { printf("NULL vol\n"); return -11; }
	//-------

	if (argc!=1) {		PRINT("usage:  conc 0x1234567\n");		return 0;	}

	long unsigned int ptr;
	ptr = strtoul (argv[0], NULL, 0);
	printf("load conc [0x%zX] ..\n", ptr);

	//mylist<Concentration>::mylist_item<Concentration> *item = vm-> concvol->conc_list.search( (Concentration*) ptr);
	mylist<Concentration>::mylist_item<Concentration> *conc_item = vm-> concvol-> search_conc( (Concentration*) ptr);
	if (conc_item==NULL) return -11;
	if (conc_item-> item == NULL) return -12;

	vm-> conc = conc_item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
// Molecule[0x17C4670]
int	cli_load_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if (vm-> concvol==NULL) { printf("NULL vol\n"); return -11; }
	//-------

	if (argc!=1) {		PRINT("usage:  load mole 0x1234567\n");		return 0;	}

	long unsigned int ptr;
	 ptr = strtoul (argv[0], NULL, 0);
	 printf("load conc [0x%zX] ..\n", ptr);

 	//mylist<Molecule>::mylist_item<Molecule> *item = vm-> concvol->mole_list.search( (Molecule*) ptr);
 	mylist<Molecule>::mylist_item<Molecule> *conc_item = vm-> concvol->search_mole( (Molecule*) ptr);
	if (conc_item==NULL) return -10;
	if (conc_item-> item == NULL) return -11;
	vm-> mole = conc_item-> item;

	return 0;
}
//---------------------------------//---------------------------------
// Concentration[0x1C6F740]
int	cli_load_pep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	if (argc!=1) {		PRINT("usage:  load pep 0x1234567\n");		return 0;	}
	if (vm-> mole ==NULL) {		PRINT("err:  need to load mole first\n");		return 0;	}

	long unsigned int ptr;
	 ptr = strtoul (argv[0], NULL, 0);
	 printf("load pep [0x%zX] ..\n", ptr);

	mylist<Peptide>::mylist_item<Peptide> *item;
	item = vm-> mole-> pep_list.search( (Peptide*) ptr);

	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	vm-> pep = item-> item;

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
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm-> conc = NULL;
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_clear_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm-> mole = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_clear_pep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm-> pep = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_clear_all(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm-> conc = NULL;
	vm-> mole = NULL;
	vm-> pep = NULL;
	return 0;
}
***************************************/
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_dump_stacks(Concentration_CLI *cli, int argc, char **argv);
int	cli_dump_regs(Concentration_CLI *cli, int argc, char **argv);
int	cli_dump_pep(Concentration_CLI *cli, int argc, char **argv);
int	cli_dump_mole(Concentration_CLI *cli, int argc, char **argv);
int	cli_dump_conc(Concentration_CLI *cli, int argc, char **argv);
int	cli_dump_vol(Concentration_CLI *cli, int argc, char **argv);
int	cli_pep_clear(Concentration_CLI *cli, int argc, char **argv);
int	cli_mole_clear(Concentration_CLI *cli, int argc, char **argv);
int	cli_conc_clear(Concentration_CLI *cli, int argc, char **argv);


//---------------------------------//---------------------------------
int	cli_load_base(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];
	// 'BASE' commands
	cli-> base_cmdlist.clear();
	LOG("\n");
	sprintf(name, "quit"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "q"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_quit, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "?"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_basehelp, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_help, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ping"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_ping, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loop"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loop, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loopz"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loopz, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loopnz"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loopnz, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "looplz"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_looplz, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loopnlz"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loopnlz, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loopeq"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loopeq, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "loopneq"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_loopneq, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, ";"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_multi, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "file"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_file, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "f"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_file, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "s"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_stacks, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "r"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_regs, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "p"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_pep, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "m"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_mole, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "c"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_conc, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "v"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_dump_vol, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "~p"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_pep_clear, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "~m"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_mole_clear, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "~c"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_conc_clear, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);

/*
	// 'LOAD' commands
	cli-> load_cmdlist.clear();
	sprintf(name, "load"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_load, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_conc, (char*) name);		LOG("load_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_mole, (char*) name);		LOG("load_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> load_cmdlist, 	cli_load_pep, (char*) name);		LOG("load_cmdlist[%s] = [%d]\n", name, r);

	// 'CLEAR' commands
	cli-> clear_cmdlist.clear();
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_clear, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "conc"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_conc, (char*) name);		LOG("clear_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_mole, (char*) name);		LOG("clear_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pep"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_pep, (char*) name);		LOG("clear_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "all"); 		r = cli-> addcmd(&cli-> clear_cmdlist, 	cli_clear_all, (char*) name);		LOG("clear_cmdlist[%s] = [%d]\n", name, r);
*/

	return 0;
}
//---------------------------------//---------------------------------
