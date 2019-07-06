/*
 * cli_mole.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */

//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------------//---------------------------------
int	cli_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
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

	//if (strcmp(argv[0], "dump")==0) {	DUMP(vm->mole)	return 0;	}

	return 	cli-> run(&cli-> mole_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
int	cli_mole_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm->mole = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_mole_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	DUMP(vm->mole)
	return 0;
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
Molecule *_cli_mole_fromargs(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return NULL;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return NULL;
	//-------
	mylist<Molecule>::mylist_item<Molecule>  *item = NULL;
	if (argc<1) {
		item = vm-> molecule_stack.gettail();
	} else {

		if (strcmp(argv[0], "help" ) == 0) {
			printf("[ null|m1|m2|rot|enz|+-[0xn]\n");
			return 0;
		}

		if (strcmp(argv[0], "m1" ) == 0) {	return vm->matchpos.getM1(); }
		if (strcmp(argv[0], "m2" ) == 0) {	return vm->matchpos.getM2(); }
		if (strcmp(argv[0], "rot" ) == 0) {	return vm->matchpos.get_rotmole();	}
		if (strcmp(argv[0], "-0" ) == 0) {	item = vm-> molecule_stack.gettail();	}
		if (strcmp(argv[0], "enz" ) == 0) {
			//PRINT("=========\n"); DUMP(cli->selected_enz) NL PRINT("=========\n");
			if (cli->selected_enz==NULL) { return NULL; }
			else { return cli->selected_enz->get_mole(); }
		}

		if (item==NULL) {
			int off;
			if ( sscanf(argv[0], "%x", &off) <0) {
				printf("bad offset [%s].\n", argv[0]);
				return NULL;
			}
			//printf("..load [%d]\n", off);
			item = vm-> molecule_stack.offset(off);
		}
	}

	// ----------- save
	if ((item !=NULL) && (item-> item !=NULL)) return item-> item;
	return NULL;
}
//---------------------------------//---------------------------------
int	cli_mole_ld(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if ((argc>0)&&(strcmp(argv[0],"null")==0)) {
		vm-> mole = NULL;
		return 0;
	}
	//-------
	Molecule	*m = _cli_mole_fromargs(cli, argc, argv);
	if (m==NULL) return -1;
	vm-> mole = m;
	return 0;
}
	/****************************
	mylist<Molecule>::mylist_item<Molecule>  *item = NULL;

	if (argc<1) {
		item = vm-> molecule_stack.gettail();
	} else {

		if (strcmp(argv[0], "help" ) == 0) {
			printf("[ m1|m2|rot|+-[0xn]\n");
			return 0;
		}

		if (strcmp(argv[0], "m1" ) == 0) {	vm-> mole = vm->matchpos.getM1(); return 0; }
		if (strcmp(argv[0], "m2" ) == 0) {	vm-> mole = vm->matchpos.getM2(); return 0; }
		if (strcmp(argv[0], "rot" ) == 0) {	vm-> mole = vm->matchpos.get_rotmole();	return 0;	}

		int off;
		if ( sscanf(argv[0], "%x", &off) <0) {
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
	return 0;
}
	***********************/
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
		if ( sscanf(argv[i], "0x%X", &hex) <0) {
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
int	cli_mole_getenz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//ChemEnzyme *enz = NULL;
	if (vm->mole != NULL) cli->selected_enz = cli-> chem_engine-> search_enz(vm->mole);

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_mole_export(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//ChemEnzyme *enz = NULL;
	if (vm->mole != NULL) {
		printf("mole addpep");
		mylist<Peptide>::mylist_item<Peptide>  *pep_item = vm->mole->pep_list.gethead();
		while ((pep_item!=NULL)&&(pep_item->item !=NULL)) {
			printf(" 0x%x", pep_item-> item->sig);
			pep_item = pep_item-> next;
		}
		printf("\n");
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------



//---------------------------------//---------------------------------
int	load_cli_mole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];

	// 'MOLE' (reg) commands
	cli-> mole_cmdlist.clear();
	sprintf(name, "mole");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_mole, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_clear, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_dump, (char*) name);		LOG("mole_cmdlist[%s] = [%d]\n", name, r);
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
	sprintf(name, "getenz"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_getenz, (char*) name);	LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "export"); 	r = cli-> addcmd(&cli-> mole_cmdlist, 	cli_mole_export, (char*) name);	LOG("mole_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
//---------------------------------//---------------------------------
