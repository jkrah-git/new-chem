/*
 * cli_pep.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */

//---------------------------------
#include "../command_callbacks.h"
//---------------------------------

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
int	cli_pep_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm->pep = NULL;
	return 0;
}
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


//---------------------------------//---------------------------------
int	load_cli_pep(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];


	// 'PEP' commands
	cli-> pep_cmdlist.clear();
	sprintf(name, "pep");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_pep, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_clear, (char*) name);		LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "push"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_push, (char*) name);		LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pop"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_pop, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_ld, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "hex"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_hex, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "pos"); 		r = cli-> addcmd(&cli-> pep_cmdlist, 	cli_pep_pos, (char*) name);			LOG("pep_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
//---------------------------------//---------------------------------
