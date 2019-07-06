/*
 * cli_vol.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */
//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------
//---------------------------//---------------------------
int	cli_vol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//PRINT(": argc[%d]", argc);
	//for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	//printf("\n");
	//-------
	//-------
	if (argc<1) {	cli->vol_cmdlist.dump();	return 0;	} // else
	return 	cli-> run(&cli-> vol_cmdlist, argc,  &argv[0]);
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	DUMP(vm->concvol);
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	vm->concvol-> clear();
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_commit(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if (vm->concvol==NULL) { printf("vol is NULL\n"); return -11; }
	//-------
	vm->concvol->commit();


	return 0;
}
//---------------------------//---------------------------
int	cli_vol_addmole(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	if (vm->concvol==NULL) { printf("vol is NULL\n"); return -11; }
	//-------
	if (vm->mole==NULL) { printf("need to select mole first\n"); return -20; }

	float f = 10.0;

	if (argc==1) {
		if (sscanf(argv[0], "%f" , &f) <1) {	printf("err: cant read amount[%s]..\n", argv[0]);	return -2;	}
		//printf("adj=[%f]\n", f);
	}

	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	// ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
	// ConcLevelType	put(Molecule	*m, ConcLevelType amount);

	float res;
	if (f <0)
		res  = vm-> concvol->take(vm->mole, f);
	else
		res  = vm-> concvol->put(vm->mole, f);

	//PRINT("res=[%f]\n", res);

	return res*100;
}
//---------------------------//---------------------------
/*
//---------------------------//---------------------------
int	cli_vol_addconc(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (vm->concvol==NULL) { printf("vol is NULL\n"); return -11; }
	if (vm->conc==NULL) { printf("need to select conc first\n"); return -20; }
	PRINT("=== TODO ===\n");

	//mylist<Concentration>::mylist_item<Concentration> *search_conc(Concentration *c){ return conc_list.search(c); };
	//mylist<Concentration>::mylist_item<Concentration> *conc_item = vm->concvol-> search_conc(Concentration *c){ return conc_list.search(c); };
	// ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	ConcLevelType v = 10.0;
	ConcLevelType	f = vm->concvol-> put(vm->conc->getmole(), v);
	PRINT("vol.addconc[%f]=[%f]\n", v, f);

	return 0;
}
*/
//---------------------------//---------------------------

//---------------------------------//---------------------------------
int	load_cli_vol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];
	//--------------
	// 'VOL' (reg) commands
	cli-> vol_cmdlist.clear();
	sprintf(name, "vol");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_vol, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");	 	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_dump, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear");	 	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_clear, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	 	r = cli-> addcmd(&cli-> vol_cmdlist,cli_vol_commit, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "addmole");	 r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_addmole, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
