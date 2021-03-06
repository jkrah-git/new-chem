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
	//////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
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
	//////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//ConcentrationVolume *vol = cli->local_vm.vol; if (vol==NULL) return -11;
	//-------
	DUMP(cli->local_vm.vol);
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_dumpmoles(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	ConcentrationVolume *vol = cli->local_vm.vol; 			if (vol==NULL) return -11;
	//-------
	vol-> dumpmoles();
	return 0;
}
//---------------------------//---------------------------//---------------------------//---------------------------
int	cli_vol_list(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	ConcentrationVolume *vol = cli->local_vm.vol; 			if (vol==NULL) return -11;
	//-------

	vol->list();
	return 0;
	//=================
	mylist<Concentration> 		*conc_list = vol-> get_conc_list();
	int n = 0;
	mylist<Concentration>::mylist_item<Concentration>  *conc_item = conc_list->gethead();
	while (conc_item!=NULL) {
		//printf("Molecule[0x%zX].len(%d)")
		if (conc_item->item !=NULL) {
			Molecule *m = conc_item->item-> getmole();
			printf("Conc[0x%zX].Mole[0x%zX]", (long unsigned int) conc_item-> item,  (long unsigned int)  m);
			if (m!=NULL) {
				m->print_short(5);
			}
			printf(" = Level[%.3f].Delta[%.3f]\n", conc_item->item->get(), conc_item->item->getdelta());
			n++;
		}
		//---------------
		conc_item = conc_item->next;
	}
	return n;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	cli->local_vm.vol-> clear();
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_listmoles(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	mylist<Molecule> 		*mole_list = cli->local_vm.vol-> get_mole_list();
	int n = 0;
	mylist<Molecule>::mylist_item<Molecule>  *mole_item = mole_list->gethead();
	while (mole_item!=NULL) {
		//printf("Molecule[0x%zX].len(%d)")
		if (mole_item->item !=NULL)
			mole_item->item->print_short(5); NL
		n++;
		//---------------
		mole_item = mole_item->next;
	}
	return n;
}
//---------------------------//---------------------------
/****************
//---------------------------//---------------------------
int	cli_vol_ld(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	ChemEngine *eng = cli->chem_engine; if (eng==NULL) return -11;
	//-------
	mylist<ConcentrationVolume>::mylist_item<ConcentrationVolume>  *vol_item = NULL;
	if (argc<1) {
		vol_item = cli-> vol_list.gettail();
	} else {

		if (strcmp(argv[0], "help" ) == 0) {
			printf("+-[0xn]\n");
			return 0;
		}
		int off;
		if ( sscanf(argv[0], "%x", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		printf("..load [%d]\n", off);
		vol_item = cli-> vol_list.offset(off);
	}

	// ----------- save
	if (vol_item ==NULL) return -10;
	if (vol_item-> item ==NULL) return -11;
	cli->selected_vol = vol_item-> item;

	return 0;
}
****************/
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_commit(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI  NEED_VOL
//	if (cli==NULL) return -1;
//	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
//	if (cli->local_vm.vol==NULL) { printf("vol is NULL\n"); return -11; }
	//-------
	float f = 1.0;

	if ((argc>0) && (strcmp(argv[0], "max")==0)){
		f = cli->local_vm. vol->get_maxcommit( cli->world->chem_engine.conc_min, cli->world->chem_engine.conc_max);
	} else {
		if ((argc>0) && (sscanf(argv[0], "%f", &f)<1)) { printf("Bad Data\n"); return -20; }
	}

	printf("vol.commit[%f]\n", f);
	cli->local_vm.vol->commit(f);
	return 0;
}
//---------------------------//---------------------------
int	cli_vol_maxcommit(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI  NEED_WORLD NEED_VOL
	// BufCommitType getmax(T floor, T ceiling) {
	printf("vol.max_commit = [%f]\n",
			cli->local_vm. vol->get_maxcommit( cli->world->chem_engine.conc_min, cli->world->chem_engine.conc_max) );
	return 0;
}
//---------------------------//---------------------------
int	cli_vol_reset(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI  NEED_VOL
//	if (cli==NULL) return -1;
//	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	cli->local_vm.vol-> reset();
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_clean(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI  NEED_VOL
//	if (cli==NULL) return -1;
//	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	ConcLevelType conc_clip = cli->world->chem_engine.conc_clip;
	//ConcLevelType conc_min = cli->world->chem_engine.conc_min;
	ConcLevelType conc_max = cli->world->chem_engine.conc_max;

	if (argc>0) {
		if (sscanf(argv[0], "%f", &conc_clip)<1) { printf("Bad Data\n"); return -20; }
		if (argc>1) {
			if (sscanf(argv[1], "%f", &conc_max)<1) { printf("Bad Data\n"); return -20; }
		}
	}

	int n = cli->local_vm. vol-> clip_conc(conc_clip, conc_max);
	printf("clean(clip[%f], max[%f]) = [%d]\n", conc_clip, conc_max, n);
	//n += cli->chem_engine->clean_volume_moles(cli->local_vm. vol);
	return n;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_vol_addmole(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI  NEED_VOL
//	if (cli==NULL) return -1;
//	////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
//	if (cli->local_vm.vol==NULL) { printf("vol is NULL\n"); return -11; }
	//-------
	if (cli->local_vm.mole==NULL) { printf("need to select mole first\n"); return -20; }

	float f = 10.0;

	if (argc==1) {
		if (sscanf(argv[0], "%f" , &f) <1) {	printf("err: cant read amount[%s]..\n", argv[0]);	return -2;	}
	}

	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	// ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
	// ConcLevelType	put(Molecule	*m, ConcLevelType amount);

	float res;
	if (f <0) {
		res  = 0;
		cli->local_vm. vol->take(cli->local_vm.mole, -f);
		printf("take[%.3f] = [%.3f]\n", f, res);
	}
	else {
		res  = 0;
		cli->local_vm. vol->put(cli->local_vm.mole, f);
		printf("put[%.3f] = [%.3f]\n", f, res);
	}

	//PRINT("res=[%f]\n", res);

	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------

//---------------------------------//---------------------------------
int	load_cli_vol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// ////Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];
	//--------------
	// 'VOL' (reg) commands
	cli-> vol_cmdlist.clear();
	sprintf(name, "vol");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_vol, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");	 	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_dump, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dumpmoles");	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_dumpmoles, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "listmoles");	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_listmoles, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear");	 	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_clear, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "list");	 	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_list, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "ld");	 	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_ld, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "commit");	r = cli-> addcmd(&cli-> vol_cmdlist,	cli_vol_commit, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "maxcommit");	r = cli-> addcmd(&cli-> vol_cmdlist,	cli_vol_maxcommit, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "reset");	 	r = cli-> addcmd(&cli-> vol_cmdlist,	cli_vol_reset, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clean");	 	r = cli-> addcmd(&cli-> vol_cmdlist,	cli_vol_clean, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "addmole");	r = cli-> addcmd(&cli-> vol_cmdlist, 	cli_vol_addmole, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
