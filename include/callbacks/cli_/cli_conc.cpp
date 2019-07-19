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
	NEED_CLI
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> conc_cmdlist_dump();
		return 0;
	} // else

	if (strcmp(argv[0], "dump")==0) 	{DUMP(cli->local_vm.conc)	return 0;	}
	if (strcmp(argv[0], "clear")==0) 	{ cli->local_vm.conc = NULL; return 0;  }

	if (strcmp(argv[0], "search")==0) 	{
		NEED_MOLE NEED_VOL
	//	if (cli->local_vm.mole ==NULL) 	{ printf("NULL mole\n"); return -20; }
	//	if (cli->local_vm.vol ==NULL) 	{ printf("NULL vol\n"); return -21; }
		Concentration *c = cli->local_vm.vol->molesearch(cli->local_vm.mole);
		if (c ==NULL) {
			printf("No conc found with mole[0x%zX]\n", (PTR) cli->local_vm.mole);
			return -1;
		} else {
			printf("conc[0x%zX] selected\n", (PTR) c);
		}
		cli->local_vm.conc =c;
		return 0;
	}


	return 	cli-> run(&cli-> conc_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_clear(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	cli->local_vm.conc = NULL;
	return 0;
}
//---------------------------------//---------------------------------
int	cli_conc_push(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	if ((cli->local_vm.conc == NULL) && (cli->local_vm. mole == NULL)) {
		printf("need to select conc or mole first\n"); return -11;
	}
	//-------

	mylist<Concentration>::mylist_item<Concentration>  *new_conc_item = cli->local_vm.concentration_stack.add();
	if (new_conc_item ==NULL) return -20;
	if (new_conc_item-> item ==NULL) return -21;

	if (cli->local_vm. conc!=NULL){
		*new_conc_item-> item = *cli->local_vm.conc;

	} else  {
		new_conc_item-> item->setmole(cli->local_vm. mole);
	}

	cli->local_vm.conc =new_conc_item-> item;
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_pop(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	mylist<Concentration>::mylist_item<Concentration>  *tail = cli->local_vm. concentration_stack.gettail();
	if (tail ==NULL) return -10;
	if (tail-> item ==NULL) return -11;

	if (cli->local_vm. conc == tail-> item) {
		cli->local_vm. conc = NULL;
	}
	cli->local_vm. concentration_stack.del(tail);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_ld(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	mylist<Concentration>::mylist_item<Concentration>  *item = NULL;

	if (argc<1) {
		item = cli->local_vm. concentration_stack.gettail();
	} else {
		int off; READI(off, 0)
		//if ( sscanf(argv[0], "%d", &off) <0) {		printf("bad offset [%s].\n", argv[0]);		return -20;		}
		//printf("..load [%d]\n", off);
		item = cli->local_vm. concentration_stack.offset(off);
	}

	// ----------- save
	if (item ==NULL) return -10;
	if (item-> item ==NULL) return -11;
	cli->local_vm. conc = item-> item;

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_mole(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	if (cli->local_vm. mole == NULL) {
		printf("Need to select mole!\n");
		return -1;
	}

	if (cli->local_vm. conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	cli->local_vm. conc->setmole(cli->local_vm. mole);

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_set(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	if (cli->local_vm. conc == NULL) {
		printf("Need to select conc!\n");
		return -1;
	}

	if (argc==1) {
		float adj; READF(adj, 0)

		printf("add/remove=[%f]\n", adj);
		if (adj >0) {	cli->local_vm. conc->buf.add(adj);	}
		if (adj <0) {	cli->local_vm. conc->buf.remove(-adj);	}

		return 0;
	}

	if (argc==2) {
		float val; READF(val, 0)
		float delta; READF(delta, 1)

		printf("set=[%f][%f]\n", val, delta);
		cli->local_vm. conc-> set(val, delta);
		return 0;
	}

	printf("usage: conc '+/-adj' | 'val' 'delta'\n");
	return -10;


}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_commit(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

	if (cli->local_vm. conc == NULL) {	printf("Need to select conc!\n");	return -1;	}
	cli->local_vm. conc-> commit();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_tovol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VOL
	//-------
	if (cli->local_vm. vol ==NULL) return -2;
	if (cli->local_vm. conc == NULL) {
		printf("Need to select conc!\n");
		return -3;
	}


	ConcLevelType r = 0;
	Molecule	*m = cli->local_vm. conc-> getmole();

	if (m==NULL) {
		printf("Conc needs Molecule..\n");
		return -3;
	}

	ConcLevelType val = cli->local_vm. conc-> get();
	ConcLevelType delta = cli->local_vm. conc-> getdelta();
	// if val!=0 then put/take - else just set delta
	if (val > 0) {
		cli->local_vm. vol->put(m, val);
		printf("add[%f]=[%f]\n", val, r);
	}
	if (val < 0) {
		cli->local_vm. vol->take(m, -val);
		printf("take[%f]=[%f]\n", -val, r);
	}
	if (val == 0) {
		cli->local_vm. vol->set(m, val, delta);
		printf("set[%f][%f]=[%f]\n", val, delta, r);
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_fromvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	//-------
	// if (cli->local_vm. vol ==NULL) return -2;
	// if (cli->local_vm. mole == NULL) {	printf("Need to select mole first!\n");	return -3;	}
	NEED_VOL NEED_MOLE

	cli->local_vm. conc = cli->local_vm. vol->molesearch(cli->local_vm. mole);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_conc_tovar(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (cli->local_vm. vol ==NULL) return -2;
	if (cli->local_vm. conc == NULL) {
		printf("Need to select conc first!\n");
		return -3;
	}

	if (argc<1) {
		printf("usage: conc tovar VARNAME\n");
		return -11;
	}

//	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], argv[1]);
	char 	name[20];
	sprintf(name, "0x%zX", (long unsigned int) cli->local_vm. conc);

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
	NEED_CLI
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
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
 	item = cli->local_vm.concentration_stack.search( (Concentration*) ptr);
 	if (item==NULL) return -10;
	if (item-> item == NULL) return -11;
	cli->local_vm. conc = item-> item;


	return 0;
}
//---------------------------------//---------------------------------


//---------------------------------//---------------------------------
int	load_cli_conc(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI

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
	sprintf(name, "set");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_set, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_commit, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovol");		r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_tovol, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvol");	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_fromvol, (char*) name);	LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tovar"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_tovar, (char*) name);		LOG("conc_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "fromvar"); 	r = cli-> addcmd(&cli-> conc_cmdlist, 	cli_conc_fromvar, (char*) name);	LOG("conc_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
//---------------------------------//---------------------------------
