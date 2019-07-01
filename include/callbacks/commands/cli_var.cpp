#include "../command_callbacks.h"

/*
 * vars.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: jkrah
 */
//=======================
//=======================
//===  STACK commands  ===
//=======================
//=======================

//---------------------------------//---------------------------------
int	cli_stack(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> stack_cmdlist_dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> stack_cmdlist, argc,  &argv[0]);
}
#include <string.h>
//---------------------------------//---------------------------------
int	cli_stack_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		vm-> dumpstacks();	 printf(".. use [pep|mole|conc to filter dump.\n");
	} else {
		if (strcmp(argv[0], "pep") ==0)  {	printf("peptide_stack ==> ");	 vm->  peptide_stack.dump();	 }
		if (strcmp(argv[0], "mole") ==0) {	printf("molecule_stack ==> ");	 vm-> molecule_stack.dump();	 }
		if (strcmp(argv[0], "conc") ==0) {	printf("concentration_stack ==> ");	 vm-> concentration_stack.dump();	 }
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_stack_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
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
			if (vm-> pep != NULL) {
				if ( vm-> peptide_stack.search(vm-> pep) != NULL ) {
					vm-> pep = NULL;
				}
			}
			//--
			vm-> peptide_stack.clear();
		}
		// -------------------------
		if ((strcmp(argv[0], "mole") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("molecule_stack ==> clear\n");
			// check if selected
			if (vm-> mole != NULL) {
				if ( vm-> molecule_stack.search(vm-> mole) != NULL ) {
					vm-> mole = NULL;
				}
			}
			//--
			vm-> molecule_stack.clear();
		}
		// -------------------------
		if ((strcmp(argv[0], "conc") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("concentration_stack ==> clear\n");
			// check if selected
			if (vm-> conc != NULL) {
				if ( vm-> concentration_stack.search(vm-> conc) != NULL ) {
					vm-> conc = NULL;
				}
			}
			//--
			vm-> concentration_stack.clear();
		}
	}

	return 0;
}

//=======================
//=======================
//===  PEP commands  ===
//=======================
//=======================
//---------------------------------//---------------------------------
int	cli_pep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// LOG(": argc[%d]", argc);
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	//-------
	mylist<Peptide>::mylist_item<Peptide>  *new_item;
	if (argc==0) {
		new_item = vm-> peptide_stack.add();
		if (new_item ==NULL) return -10;
		if (new_item-> item ==NULL) return -11;

		if (vm-> pep==NULL) {
			vm-> pep = new_item-> item;
		} else {
			*new_item-> item = *vm-> pep;
		}

	} else {
		for (int i=0; i<argc; i++) {
			new_item = vm-> peptide_stack.add();
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Peptide>::mylist_item<Peptide>  *tail = vm-> peptide_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	//*cli-> core-> pep = *tail-> item;
	if (vm-> pep == tail-> item) {
		vm-> pep = NULL;
	}
	vm-> peptide_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_ld(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Peptide>::mylist_item<Peptide>  *item = NULL;

	if (argc<1) {
		item = vm-> peptide_stack.gettail();
	} else {
		int off;
		if ( sscanf(argv[0], "%d", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		//printf("..load [%d]\n", off);
		item = vm-> peptide_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	vm-> pep = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_hex(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
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
	if (vm-> pep !=NULL) {
		vm-> pep-> set(sig);
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_pep_pos(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<2) {
		printf("usage: pep posX posY\n");
		return -123;
	}

	int posx;
	if ( sscanf(argv[0], "%d", &posx) <0) {
		printf("bad pos-x[%s].\n", argv[0]);
		return -20;
	}

	int posy;
	if ( sscanf(argv[1], "%d", &posy) <0) {
		printf("bad pos-y[%s].\n", argv[1]);
		return -21;
	}


	if (vm-> pep !=NULL) {
	//	cli-> core-> pep-> pos.dim[0] = posx;
	//	cli-> core-> pep-> pos.dim[1] = posy;
	//	PepPosVecType	*pos = cli-> core-> pep-> getpos();
		vm-> pep-> setpos(posx, posy, 0);
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
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Molecule>::mylist_item<Molecule>  *new_item = NULL;
	new_item = vm-> molecule_stack.add();
	if (new_item ==NULL) return -10;
	if (new_item-> item ==NULL) return -11;
	vm-> mole = new_item-> item;
	return 0;
}

/******
	if (vm-> mole==NULL) {
		vm-> mole = new_item-> item;
	} else {
		*new_item-> item = *vm-> mole;
	}
	return 0;
}
******/
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_pop(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------



	mylist<Molecule>::mylist_item<Molecule>  *tail = vm-> molecule_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	//*cli-> core-> pep = *tail-> item;
	if (vm-> mole == tail-> item) {
		vm-> mole = NULL;
	}
	vm-> molecule_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_ld(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	mylist<Molecule>::mylist_item<Molecule>  *item = NULL;

	if (argc<1) {
		item = vm-> molecule_stack.gettail();
	} else {

		if (strcmp(argv[0], "help" ) == 0) {
			printf("[ m1|m2|rot|+n|-1]\n");
			return 0;
		}

		if (strcmp(argv[0], "m1" ) == 0) {	vm-> mole = vm->matchpos.getM1(); return 0; }
		if (strcmp(argv[0], "m2" ) == 0) {	vm-> mole = vm->matchpos.getM2(); return 0; }
		if (strcmp(argv[0], "rot" ) == 0) {	vm-> mole = vm->matchpos.get_rotmole();	return 0;	}

		int off;
		if ( sscanf(argv[0], "%d", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		printf("..load [%d]\n", off);
		item = vm-> molecule_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	vm-> mole = item-> item;

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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> mole==NULL)  return -10;

	int r = -100;
	int c=0;
	mylist<Peptide>::mylist_item<Peptide>  *item = vm-> peptide_stack.gethead();
	while ((item!=NULL) && (item-> item!=NULL)) {
		r = vm-> mole->addpep(item-> item-> get());
		if (r<0) { LOG("addpep = [%d]\n", r); }
		else { c++; }
		// ---
		item = item-> next;
	}



	if (argc<1) {
	}
	return c;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_addpep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> mole==NULL)  return -10;

	//PRINT("argc=[%d].", argc); for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}	NL
	int r=0;
	//int n=0;
	int hex;
	for (int i=0; i<argc; i++){
		if ( sscanf(argv[i], "0x%x", &hex) <0) {
			printf("bad sig #[%d]=[%s].\n", i, argv[i]);
			return -20;
		}
		r = vm-> mole->addpep(hex);
		LOG("addpep = [%d] = [%d]\n", hex, r);
	}
	return argc;


}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_deltail(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> mole==NULL)  return -10;
	int r=0;

	if (vm-> mole->pep_list.gettail()!=NULL) {
		vm-> mole->pep_list.del(vm-> mole->pep_list.gettail());
	}



	return r;

}
//---------------------------------//---------------------------------

//---------------------------------//---------------------------------
int	cli_mole_frompep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> mole==NULL)  return -10;

	vm-> mole->clear();
	mylist<Peptide>::mylist_item<Peptide>  *item = vm-> peptide_stack.gethead();
	while ((item!=NULL) && (item-> item!=NULL)) {
		mylist<Peptide>::mylist_item<Peptide> *new_item = vm-> mole-> pep_list.add();
		if (new_item==NULL)
			return -20;

		*new_item-> item = *item-> item;
		// ---
		item = item-> next;
	}
	return 0;
}
//---------------------------------//---------------------------------
int	cli_mole_topep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> mole==NULL)  return -10;

	//cli-> core-> mole->clear();
	mylist<Peptide>::mylist_item<Peptide>  *item = vm-> mole-> pep_list.gethead();
	while ((item!=NULL) && (item-> item!=NULL)) {
		mylist<Peptide>::mylist_item<Peptide> *new_item = vm-> peptide_stack.add();
		if (new_item==NULL)
			return -20;

		*new_item-> item = *item-> item;
		// ---
		item = item-> next;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_tovar(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> mole==NULL)  return -10;

	if (argc<1) {
		printf("usage: mole tovar VARNAME\n");
		return -11;
	}

//	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], argv[1]);
	char 	name[20];
	sprintf(name, "0x%zX", (long unsigned int) vm-> mole);
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

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
 	item = vm->molecule_stack.search( (Molecule*) ptr);
 	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	vm-> mole = item-> item;

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
	// LOG(": argc[%d]", argc);
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	mylist<Concentration>::mylist_item<Concentration>  *new_item = NULL;

	// ../chem/Concentration.h:33: note: candidates are: Concentration::Concentration(Molecule*)
	new_item = vm->concentration_stack.add();
	if (new_item ==NULL) return -10;
	if (new_item-> item ==NULL) return -11;

	// if nothing selected - (select new) (and leave entry blank)
	if (vm-> conc==NULL) {	   // (or use current mole)
		if (vm-> mole != NULL) {
			new_item-> item->setmole(vm-> mole);
		}
		vm-> conc = new_item-> item;	// select
	} else { // copy in selected to new
		*new_item-> item = *vm-> conc;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_pop(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	mylist<Concentration>::mylist_item<Concentration>  *tail = vm-> concentration_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	//*cli-> core-> pep = *tail-> item;
	if (vm-> conc == tail-> item) {
		vm-> conc = NULL;
	}
	vm-> concentration_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_ld(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	mylist<Concentration>::mylist_item<Concentration>  *item = NULL;

	if (argc<1) {
		item = vm-> concentration_stack.gettail();
	} else {
		int off;
		if ( sscanf(argv[0], "%d", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		//printf("..load [%d]\n", off);
		item = vm-> concentration_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	vm-> conc = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	if (vm-> mole == NULL) {
		printf("Need to select mole!\n");
		return -1;
	}

	if (vm-> conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	vm-> conc->setmole(vm-> mole);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_adj(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> conc == NULL) {
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

		if (adj <0) {	vm-> conc-> take(adj);	}
		if (adj >0) {	vm-> conc-> put(adj);	}

		return 0;
	}

	if (argc==2) {
		//ConcLevelType adj;
		float val, delta;

		if (sscanf(argv[0], "%f" , &val) <1) { printf("err: cant read val..\n"); return -3; }
		if (sscanf(argv[1], "%f" , &delta) <1) { printf("err: cant read delta..\n"); return -3; }
		printf("set=[%f][%f]\n", val, delta);
		vm-> conc-> set(val, delta);
		return 0;
	}

	printf("usage: conc '+-adj' | 'val' 'delta'\n");
	return -10;


}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_commit(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	vm-> conc-> commit();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_tovol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> concvol ==NULL) return -2;
	if (vm-> conc == NULL) {
		printf("Need to select conc!\n");
		return -3;
	}


	ConcLevelType r = 0;
	Molecule	*m = vm-> conc-> getmole();

	if (m==NULL) {
		printf("Conc needs Molecule..\n");
		return -3;
	}

	ConcLevelType val = vm-> conc-> get();
	ConcLevelType delta = vm-> conc-> getdelta();
	// if val!=0 then put/take - else just set delta
	if (val > 0) {
		vm-> concvol->put(m, val);
		printf("add[%f]=[%f]\n", val, r);
	}
	if (val < 0) {
		vm-> concvol->take(m, -val);
		printf("take[%f]=[%f]\n", -val, r);
	}
	if (val == 0) {
		vm-> concvol->set(m, val, delta);
		printf("set[%f][%f]=[%f]\n", val, delta, r);
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_fromvol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> concvol ==NULL) return -2;
	if (vm-> mole == NULL) {
		printf("Need to select mole first!\n");
		return -3;
	}

	////Concentration	*molesearch(Molecule	*m);
	vm-> conc = vm-> concvol->molesearch(vm-> mole);
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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm-> concvol ==NULL) return -2;
	if (vm-> conc == NULL) {
		printf("Need to select conc first!\n");
		return -3;
	}

	if (argc<1) {
		printf("usage: conc tovar VARNAME\n");
		return -11;
	}

//	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], argv[1]);
	char 	name[20];
	sprintf(name, "0x%zX", (long unsigned int) vm-> conc);

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
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
 	item = vm->concentration_stack.search( (Concentration*) ptr);
 	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	vm-> conc = item-> item;


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
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
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
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	cli-> var_cmdlist_dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_get(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<2) {
		printf("usage: var set name value\n");
		return -1;
	}
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	char buf[KEYVAL_MAX_VAL];
	buf[0] = '\0';
	int c=0;
	for (int i=1; i<argc; i++) {
		if ((strlen(buf) + strlen(argv[i]+1) < KEYVAL_MAX_VAL)) {

			//printf("arg[%d][%s] -> buf[%d][%s]\n", i, argv[i], c, buf);
			if (i>1) buf[c++] = ' ';
			strcpy(&buf[c], argv[i]);
			c += strlen(argv[i]);
			//buf[c+1] = '\0';
		}
	}
	printf("'%s'='%s'\n", argv[0], buf);

	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], buf);
	if (item==NULL) {
		printf("failed to set var[%s]\n", buf);
		return -2;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
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
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc!=1) {
		printf("usage: var clear name\n");
		return -1;
	}
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.search(argv[0]);
	if (item!=NULL) {
		cli->var_list.keyvalues.del(item);
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_run(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	 if (argc<1) {
		 printf("usage: var run vName..\n");
		 return -1;
	 }

	char *str = cli->var_list.get(argv[0]);
	if (str==NULL) {
		printf("Error reading args\n");
		return -10;
	}
	printf("[%s]\n", str);
	//-----------------------------
	//return 0;
	char payload[KEYVAL_MAX_VAL];
	strncpy(payload, str, KEYVAL_MAX_VAL);

	int r = cli-> runline(&cli-> base_cmdlist, payload);
	if (r!=0) printf("Run = [%d]\n", r);

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
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];

	// 'STACK' commands
	cli-> stack_cmdlist.clear();
	sprintf(name, "stack"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_stack, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_dump, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_clear, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "comp"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_comp, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);

	// 'PEP' commands
	cli-> pep_cmdlist.clear();
	sprintf(name, "pep");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_pep, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_push, (char*) name);		LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_pop, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_ld, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "hex"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_hex, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pos"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_pos, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);

	// 'MOLE' (reg) commands
	cli-> mole_cmdlist.clear();
	sprintf(name, "mole");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_mole, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "clear"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_clear_mole, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_push, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_pop, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_ld, (char*) name);			LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "build"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_build, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "addpep"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_addpep, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "deltail"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_deltail, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);

	sprintf(name, "frompep"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_frompep, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "topep"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_topep, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovar"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_tovar, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvar"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_fromvar, (char*) name);	LOG("mole_cmdlist[%s] = [%d]\n", name, r);

	// 'CONC' (reg) commands
	cli-> conc_cmdlist.clear();
	sprintf(name, "conc");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_conc, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_push, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_pop, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_ld, (char*) name);			LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "mole");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_mole, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "adj");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_adj, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_commit, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovol");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_tovol, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvol");	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_fromvol, (char*) name);	LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovar"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_tovar, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvar"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_fromvar, (char*) name);	LOG("conc_cmdlist[%s] = [%d]\n", name, r);

	// 'VAR' commands
	cli-> var_cmdlist.clear();
	sprintf(name, "var");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_var, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_help, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_get, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "set"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_set, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_clear, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "del"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_del, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_run, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	//----------
	sprintf(name, "run"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_var_run, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
