/*
 * cli_conc.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */

//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------------//---------------------------------
int	cli_conc(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> conc_cmdlist_dump();
		return 0;
	} // else

	if (strcmp(argv[0], "dump")==0) {	DUMP(vm->conc)	return 0;	}
	if (strcmp(argv[0], "clear")==0) { vm->conc = NULL; return 0;  }
	if (strcmp(argv[0], "search")==0) {
		if (vm->mole ==NULL) { printf("NULL mole\n"); return -20; }
		if (vm->vol ==NULL) { printf("NULL vol\n"); return -21; }

		Concentration *c = vm->vol->molesearch(vm->mole);

		if (c ==NULL) {
			printf("no conc found\n");
			return -1;
		}
		vm->conc =c;
		return 0;
	}


	return 	cli-> run(&cli-> conc_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm->conc = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_conc_push(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if ((vm->conc == NULL) && (vm-> mole == NULL)) {
		printf("need to select conc or mole first\n"); return -11;
	}
	//-------

	mylist<Concentration>::mylist_item<Concentration>  *new_conc_item = vm->concentration_stack.add();
	if (new_conc_item ==NULL) return -20;
	if (new_conc_item-> item ==NULL) return -21;

	if (vm-> conc!=NULL){
		//new_conc_item-> item->setmole(vm-> conc->getmole());

		*new_conc_item-> item = *vm->conc;

	} else  {
		new_conc_item-> item->setmole(vm-> mole);
	}

	vm->conc =new_conc_item-> item;
	return 0;
}
	/*
	// if nothing selected - (select new) (and leave entry blank)
	if (vm-> conc==NULL) {	   // (or use current mole)
		if (vm-> mole != NULL) {
			new_conc_item-> item->setmole(vm-> mole);
		}
		vm-> conc = new_conc_item-> item;	// select
	} else { // copy in selected to new
		*new_conc_item-> item = *vm-> conc;
	}
	return 0;
}
	*/
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
	if (vm-> vol ==NULL) return -2;
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
		vm-> vol->put(m, val);
		printf("add[%f]=[%f]\n", val, r);
	}
	if (val < 0) {
		vm-> vol->take(m, -val);
		printf("take[%f]=[%f]\n", -val, r);
	}
	if (val == 0) {
		vm-> vol->set(m, val, delta);
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
	if (vm-> vol ==NULL) return -2;
	if (vm-> mole == NULL) {
		printf("Need to select mole first!\n");
		return -3;
	}

	////Concentration	*molesearch(Molecule	*m);
	vm-> conc = vm-> vol->molesearch(vm-> mole);
	/*

	ConcLevelType r = 0;
	Molecule	*m = cli-> core-> mole;

	if (m==NULL) {
		printf("Conc needs Molecule..\n");
		return -3;
	}

	ConcLevelType val = cli-> core-> conc-> get();
	ConcLevelType delta = cli-> core-> conc-> getdelta();
	cli-> core-> vol->set(m, val,delta);
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
	if (vm-> vol ==NULL) return -2;
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
 	//item = cli->core-> vol->mole_list.search( (Molecule*) ptr);
 	item = vm->concentration_stack.search( (Concentration*) ptr);
 	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	vm-> conc = item-> item;


	return 0;
}
//---------------------------------//---------------------------------


//---------------------------------//---------------------------------
int	load_cli_conc(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];


	// 'CONC' (reg) commands
	cli-> conc_cmdlist.clear();
	sprintf(name, "conc");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_conc, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_clear, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
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

	return 0;
}
//---------------------------------//---------------------------------
