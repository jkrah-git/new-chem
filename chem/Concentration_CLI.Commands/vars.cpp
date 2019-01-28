/*
 * vars.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: jkrah
 */


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
		printf("usage: stack clear pep|mole|conc|all to select.\n");
	} else {
		// -------------------------
		if ((strcmp(argv[0], "pep") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("peptide_stack ==> clear\n");
			// check if selected
			if (cli-> core-> pep != NULL) {
				if ( cli->core-> peptide_stack.search(cli-> core-> pep) != NULL ) {
					cli-> core-> pep = NULL;
				}
			}
			//--
			cli->core-> peptide_stack.clear();
		}
		// -------------------------
		if ((strcmp(argv[0], "mole") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("molecule_stack ==> clear\n");
			// check if selected
			if (cli-> core-> mole != NULL) {
				if ( cli->core-> molecule_stack.search(cli-> core-> mole) != NULL ) {
					cli-> core-> mole = NULL;
				}
			}
			//--
			cli->core-> molecule_stack.clear();
		}
		// -------------------------
		if ((strcmp(argv[0], "conc") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("concentration_stack ==> clear\n");
			// check if selected
			if (cli-> core-> conc != NULL) {
				if ( cli->core-> concentration_stack.search(cli-> core-> conc) != NULL ) {
					cli-> core-> conc = NULL;
				}
			}
			//--
			cli->core-> concentration_stack.clear();
		}
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_stack_comp(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		printf("usage: stack comp mole|conc to select.\n");
	} else {
		//if (strcmp(argv[0], "pep") ==0)  {	printf("peptide_stack ==> clear\n");	 	cli->core-> peptide_stack.clear();	 }
		if (strcmp(argv[0], "mole") ==0) {
			//printf("molecule_stack ==> clear\n");
			//cli->core-> molecule_stack.clear();
			if (cli-> core-> mole ==NULL) {
				printf("No molecule selected\n");
				return -2;
			}

			int c = 0;
			mylist<Peptide>::mylist_item<Peptide>  *item = cli-> core-> peptide_stack.gethead();
			while ((item!=NULL) && (item-> item!=NULL)) {
				cli-> core-> mole->addpep(item-> item-> get());
				// ---
				item = item-> next;
				c++;
			}
			return c;

		}

		if (strcmp(argv[0], "conc") ==0) {
			printf("concentration_stack ==> clear\n");
			cli->core-> concentration_stack.clear();
		}
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
int	cli_mole_tovar(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> mole==NULL)  return -10;

	if (argc<1) {
		printf("usage: mole tovar VARNAME\n");
		return -11;
	}

//	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], argv[1]);
	char 	name[20];
	sprintf(name, "0x%zX", (long unsigned int) cli-> core-> mole);
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], name);
	if (item==NULL) {
		printf("failed to set var[%s]\n", argv[0]);
		return -12;
	}


	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_fromvar(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//if (cli-> core-> mole==NULL)  return -10;

	if (argc<1) {
		printf("usage: mole fromvar VARNAME\n");
		return -11;
	}

	char *val = cli->var_list.get(argv[0]);
	if (val==NULL) {
		printf("failed to get var[%s]\n", argv[0]);
		return -12;
	}


	long unsigned int ptr;
	ptr = strtoul (val, NULL, 0);
	printf("load mole [0x%zX] ..\n", ptr);

 	mylist<Molecule>::mylist_item<Molecule> *item;
 	//item = cli->core-> concvol->mole_list.search( (Molecule*) ptr);
 	item = cli->core->molecule_stack.search( (Molecule*) ptr);
 	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->core-> mole = item-> item;

 	// todo marker fromvar

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
int	cli_conc_push(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	mylist<Concentration>::mylist_item<Concentration>  *new_item = NULL;

	// ../chem/Concentration.h:33: note: candidates are: Concentration::Concentration(Molecule*)
	new_item = cli-> core->concentration_stack.add();
	if (new_item ==NULL) return -10;
	if (new_item-> item ==NULL) return -11;

	// if nothing selected - (select new) (and leave entry blank)
	if (cli-> core-> conc==NULL) {	   // (or use current mole)
		if (cli-> core-> mole != NULL) {
			new_item-> item->setmole(cli-> core-> mole);
		}
		cli-> core-> conc = new_item-> item;	// select
	} else { // copy in selected to new
		*new_item-> item = *cli-> core-> conc;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_pop(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Concentration>::mylist_item<Concentration>  *tail = cli-> core-> concentration_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	//*cli-> core-> pep = *tail-> item;
	if (cli-> core-> conc == tail-> item) {
		cli-> core-> conc = NULL;
	}
	cli-> core-> concentration_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_ld(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	mylist<Concentration>::mylist_item<Concentration>  *item = NULL;

	if (argc<1) {
		item = cli-> core-> concentration_stack.gettail();
	} else {
		int off;
		if ( sscanf(argv[0], "%d", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		//printf("..load [%d]\n", off);
		item = cli-> core-> concentration_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	cli-> core-> conc = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_mole(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;

	if (cli-> core-> mole == NULL) {
		printf("Need to select mole!\n");
		return -1;
	}

	if (cli-> core-> conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	cli-> core-> conc->setmole(cli-> core-> mole);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_adj(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	//if (argc!=1) {		printf("usage: conc adj '+-amount'\n");		return -1;	}


	if (argc==1) {
		//ConcLevelType adj;
		float adj;
		if (sscanf(argv[0], "%f" , &adj) <1) {
			printf("err: cant read amount..\n");
			return -2;
		}
		printf("adj=[%f]\n", adj);

		if (adj <0) {	cli-> core-> conc-> take(adj);	}
		if (adj >0) {	cli-> core-> conc-> put(adj);	}

		return 0;
	}

	if (argc==2) {
		//ConcLevelType adj;
		float val, delta;

		if (sscanf(argv[0], "%f" , &val) <1) { printf("err: cant read val..\n"); return -3; }
		if (sscanf(argv[1], "%f" , &delta) <1) { printf("err: cant read delta..\n"); return -3; }
		printf("set=[%f][%f]\n", val, delta);
		cli-> core-> conc-> set(val, delta);
		return 0;
	}

	printf("usage: conc '+-adj' | 'val' 'delta'\n");
	return -10;


}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_commit(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	cli-> core-> conc-> commit();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_tovol(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> concvol ==NULL) return -2;
	if (cli-> core-> conc == NULL) {
		printf("Need to select conc!\n");
		return -3;
	}


	ConcLevelType r = 0;
	Molecule	*m = cli-> core-> conc-> getmole();

	if (m==NULL) {
		printf("Conc needs Molecule..\n");
		return -3;
	}

	ConcLevelType val = cli-> core-> conc-> get();
	ConcLevelType delta = cli-> core-> conc-> getdelta();
	// if val!=0 then put/take - else just set delta
	if (val > 0) {
		cli-> core-> concvol->put(m, val);
		printf("add[%f]=[%f]\n", val, r);
	}
	if (val < 0) {
		cli-> core-> concvol->take(m, -val);
		printf("take[%f]=[%f]\n", -val, r);
	}
	if (val == 0) {
		cli-> core-> concvol->set(m, val, delta);
		printf("set[%f][%f]=[%f]\n", val, delta, r);
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_fromvol(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> concvol ==NULL) return -2;
	if (cli-> core-> mole == NULL) {
		printf("Need to select mole first!\n");
		return -3;
	}

	////Concentration	*molesearch(Molecule	*m);
	cli-> core-> conc = cli-> core-> concvol->molesearch(cli-> core-> mole);
	/*

	ConcLevelType r = 0;
	Molecule	*m = cli-> core-> mole;

	if (m==NULL) {
		printf("Conc needs Molecule..\n");
		return -3;
	}

	ConcLevelType val = cli-> core-> conc-> get();
	ConcLevelType delta = cli-> core-> conc-> getdelta();
	cli-> core-> concvol->set(m, val,delta);
	printf("set[%f][%f]=[%f]\n", val,delta, r);
	*/
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_tovar(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (cli-> core-> concvol ==NULL) return -2;
	if (cli-> core-> conc == NULL) {
		printf("Need to select conc first!\n");
		return -3;
	}

	if (argc<1) {
		printf("usage: conc tovar VARNAME\n");
		return -11;
	}

//	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], argv[1]);
	char 	name[20];
	sprintf(name, "0x%zX", (long unsigned int) cli-> core-> conc);

	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], name);
	if (item==NULL) {
		printf("failed to set var[%s]\n", argv[0]);
		return -12;
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_fromvar(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//if (cli-> core-> mole==NULL)  return -10;

	if (argc<1) {
		printf("usage: conc fromvar VARNAME\n");
		return -11;
	}

	char *val = cli->var_list.get(argv[0]);
	if (val==NULL) {
		printf("failed to get var[%s]\n", argv[0]);
		return -12;
	}


	long unsigned int ptr;
	ptr = strtoul (val, NULL, 0);
	printf("load conc [0x%zX] ..\n", ptr);

 	mylist<Concentration>::mylist_item<Concentration> *item;
 	//item = cli->core-> concvol->mole_list.search( (Molecule*) ptr);
 	item = cli->core->concentration_stack.search( (Concentration*) ptr);
 	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->core-> conc = item-> item;


	return 0;
}
//---------------------------------//---------------------------------

//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
//int	cli_dump(Concentration_CLI *cli, int argc, char **argv){
//=======================
//===  VAR commands  ===
//=======================
//---------------------------------//---------------------------------
int	cli_var(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	if (argc<1) {
		cli->var_list_dump();
		return 0;
	}
	// else
	return 	cli-> run(&cli-> var_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
int	cli_var_help(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	cli-> var_cmdlist_dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_get(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (argc<1) {
		printf("usage: var get name\n");
		return -1;
	}
	char *val = cli->var_list.get(argv[0]);

	if (val==NULL) {
		printf("Failed to get var[%s]\n", argv[0]);
		return -10;
	}

	printf("'%s'='%s'\n", argv[0], val);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_set(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (argc<2) {
		printf("usage: var set name value\n");
		return -1;
	}
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], argv[1]);
	if (item==NULL) {
		printf("failed to set var[%s]\n", argv[0]);
		return -2;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_clear(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (argc!=1) {
		printf("usage: var clear name\n");
		return -1;
	}
	char S[1] = { '\0' };
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], S);
	if ((item==NULL)||(item-> item==NULL)) {
		printf("failed to set var[%s]\n", argv[0]);
		return -2;
	} else {
		memset(item-> item-> val, '\0', KEYVAL_MAX_VAL);
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_del(Concentration_CLI *cli, int argc, char **argv){
	if ((cli==NULL) || (cli-> core ==NULL)) return -1;
	if (argc!=1) {
		printf("usage: var clear name\n");
		return -1;
	}
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.search(argv[0]);
	if (item!=NULL) {
		cli->var_list.keyvalues.del(item, true);
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------

//=======================
//---------------------------------//---------------------------------
//=======================//=======================//=======================
//---------------------------------//---------------------------------
int	cli_load_vars(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

	int r;
	char name[32];

	// 'STACK' commands
	cli-> stack_cmdlist.clear();
	sprintf(name, "stack"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_stack, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_dump, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_clear, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "comp"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_comp, (char*) name);		PRINT("dump_cmdlist[%s] = [%d]\n", name, r);

	// 'PEP' commands
	cli-> pep_cmdlist.clear();
	sprintf(name, "pep");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_pep, (char*) name);				PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_push, (char*) name);		PRINT("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_pop, (char*) name);			PRINT("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_ld, (char*) name);			PRINT("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "hex"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_hex, (char*) name);			PRINT("pep_cmdlist[%s] = [%d]\n", name, r);

	// 'MOLE' commands
	cli-> mole_cmdlist.clear();
	sprintf(name, "mole");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_mole, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_push, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_pop, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_ld, (char*) name);			PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "build"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_build, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovar"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_tovar, (char*) name);		PRINT("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvar"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_fromvar, (char*) name);	PRINT("mole_cmdlist[%s] = [%d]\n", name, r);

	// 'CONC' commands
	cli-> conc_cmdlist.clear();
	sprintf(name, "conc");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_conc, (char*) name);			PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_push, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_pop, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_ld, (char*) name);			PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_mole, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "adj");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_adj, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_commit, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovol");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_tovol, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvol");	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_fromvol, (char*) name);	PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovar"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_tovar, (char*) name);		PRINT("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvar"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_fromvar, (char*) name);	PRINT("conc_cmdlist[%s] = [%d]\n", name, r);

	// 'VAR' commands
	cli-> var_cmdlist.clear();
	sprintf(name, "var");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_var, (char*) name);				PRINT("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_help, (char*) name);		PRINT("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_get, (char*) name);		PRINT("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "set"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_set, (char*) name);		PRINT("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_clear, (char*) name);		PRINT("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "del"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_del, (char*) name);		PRINT("var_cmdlist[%s] = [%d]\n", name, r);
	//----------
	return 0;
}
