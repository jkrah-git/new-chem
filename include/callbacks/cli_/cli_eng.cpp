/*
 * cli_eng.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: jkrah
 */
#include "../command_callbacks.h"
//=======================//=======================//=======================
#include <string.h>
// --------------------------
int	cli_eng(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//------------------------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if (argc<1) {	cli->eng_cmdlist.dump();	return 0;	} // else
	return 	cli-> run(&cli-> eng_cmdlist, argc,  &argv[0]);
	return 0;
}
	/****************
	//  time
	float run_time = 1.0;
	char **next_argv = &argv[0];
	{
		float t;
		int r = sscanf(next_argv[0], "%f", &t);
		if (r>0) {
			run_time = t;
			printf("eng.time = [%f]\n", run_time);
			next_argv = &argv[1];
			argc--;
		}
	}


	if (argc>0) {
		if ((strcmp(next_argv[0], "help"))==0) {
		//	PRINT("engine match..\n");
			printf("eng start\n");
			printf("eng [time] next\n");
			printf("eng [time] [func]\n");
			return 0;
		}

		if ((strcmp(next_argv[0], "start"))==0) {
		//	PRINT("engine start..\n");
			if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
			if (vm==NULL) { printf("Need to select vm\n"); return -11; }
			if (vm->conc==NULL) { printf("Need to select conc\n"); return -11; }
			// int	ChemEnzyme::match(Concentration *conc, Concentration_VM *vm){
			int r =  cli-> selected_enz->match_start(vm-> conc, vm);
			//printf("match = [%d]\n", r);
			return r;
		}
		if ((strcmp(next_argv[0], "next"))==0) {
		//	PRINT("engine next..\n");
			if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
			if (vm==NULL) { printf("Need to select vm\n"); return -11; }
			//if (vm->conc==NULL) { printf("Need to select conc\n"); return -11; }
			// int	ChemEnzyme::match(Concentration *conc, Concentration_VM *vm){


			//int r =  cli-> selected_enz->match_next(cli->world.chem_engine, vm);
			// r = chemfunc->operation(eng, vm, 0 , NULL);
			ChemFunc *f =cli-> selected_enz->match_next(vm);
			int r = -1;
			if ((f!=NULL) && (f->operation!=NULL))
					r = f->operation(cli->world.chem_engine, vm, run_time, 0, NULL);
			//printf("next(t=%.f) = [%d]\n", run_time, r);
			return r;
		}
	}
	// else
	return cli->world.chem_engine. run(cli-> get_selected_vm(), run_time, argc, next_argv);
}
*****************/
// --------------------------
// 'run'
int	cli_eng_run(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD //NEED_CELL
	//  time
	float run_time = 1.0;
	char **next_argv = &argv[0];
	{
		float t;
		int r = sscanf(next_argv[0], "%f", &t);
		if (r>0) {
			run_time = t;
			printf("eng.time = [%f]\n", run_time);
			next_argv = &argv[1];
			argc--;
		}
	}
//	return cli->world.chem_engine. run(cli-> get_selected_vm(), run_time, argc, next_argv);
	return cli->world-> chem_engine. run(
			cli->selected_ambcell-> cell, cli-> get_selected_vm(), run_time, argc, next_argv);


}
// --------------------------
// 'dump'
int	cli_eng_dump(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	cli->world-> chem_engine.dump();
	return 0;
}
// --------------------------
// --------------------------
// 'list'
int	cli_eng_list(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
//	DUMP(cli->world.chem_engine)
	cli->world-> chem_engine.dump();
	return 0;
}
// --------------------------
// --------------------------
// 'runvol'
int	cli_eng_runmatch(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM
	// ----------------------------
	return cli->world-> chem_engine.get_reactions(vm);
}
// --------------------------
// --------------------------
// 'match'
int	cli_eng_runfunc(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM
	// ----------------------------
	float run_time = 1.0;
	char **next_argv = &argv[0];
	{
		float t;
		int r = sscanf(next_argv[0], "%f", &t);
		if (r>0) {
			run_time = t;
			printf("eng.time = [%f]\n", run_time);
			next_argv = &argv[1];
			argc--;
		}
	}
	return cli->world-> chem_engine. run_reactions(cli->selected_ambcell-> cell, vm, run_time);
}
// --------------------------// --------------------------
// int	ChemEngine::eng_tick(void){
// --------------------------
// 'tick'
int	cli_eng_tick(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if (argc>0) {
		int t;
		int r = sscanf(argv[0], "%d", &t);
		if ((r<0)||(t<1)) { printf("Bad Data\n"); return -20; }
		//printf("ttl's[%d]..\n", t);
		for (int i=0; i<t; i++) {
			cli->world-> chem_engine.next_tick();
			//cli-> display-> draw_screen(cli-> display-> selected_screen, cli);
		}
	}

return cli->world-> chem_engine.get_tick();
}
// --------------------------// --------------------------
// int	ChemEngine::eng_maxtick(void){
// --------------------------
// 'tick'
int	cli_eng_maxtick(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	if (argc<1) {
		return cli->world-> chem_engine.get_maxtick();
	}

	int t;
	int r = sscanf(argv[0], "%d", &t);
	if ((r<0)||(t<1)) { printf("Bad Data\n"); return -20; }
	cli->world-> chem_engine.set_maxtick(t);

	return cli->world-> chem_engine.get_maxtick();
}
// --------------------------// --------------------------
// int	ChemEngine::get_reactions(Concentration_VM *vm, ConcentrationVolume *vol){
// --------------------------
// 'get'
int	cli_eng_get(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM
	return cli->world-> chem_engine. get_reactions(vm);
}
// --------------------------
// int	ChemEngine::run_reactions(Concentration_VM *vm, ConcentrationVolume *vol, ChemTime run_time){
// --------------------------
// 'run'
int	cli_eng_react(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VM

	if (argc<1) {
		printf("usage: eng react <run_time>\n");
		return -1;
	}
	float run_time = 1.0;
	{
		float t;
		int r = sscanf(argv[0], "%f", &t);
		if (r<1) { printf ("Bad Data\n"); return -20; }
		run_time = t;
		printf("run_time = [%f]\n", run_time);

	}
	return cli->world-> chem_engine. run_reactions(cli->selected_ambcell-> cell, vm, run_time);
}
// --------------------------
// ChemTime	ChemEngine::run_volume(Concentration_VM *vm, ConcentrationVolume *vol, ChemTime run_time){
// --------------------------
// 'runvol'
int	cli_eng_runvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_WORLD NEED_VOL
	// ----------------------------
	float run_time = 1.0;
	if (argc>0)	{
		float t;
		int r = sscanf(argv[0], "%f", &t);
		if (r<1) { printf ("Bad Data\n"); return -20; }
		run_time = t;
		printf("run_time = [%f]\n", run_time);
	}
	//ChemTime actual_time = cli->world-> chem_engine.run_volume(vm, run_time);
	int r  = cli->world-> chem_engine.run_volume(
			cli->selected_ambcell-> cell, vm->vol, run_time);
	return r;
}
// --------------------------
// int	ChemEngine::clean_volume_moles(ConcentrationVolume *vol) {
// --------------------------
// 'runvol'
int	cli_eng_cleanmoles(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_WORLD NEED_VOL
	return cli->world-> chem_engine. clean_volume_moles(vm-> vol);
}
// --------------------------
// 'enzstart'
int	cli_eng_enzstart(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_ENG
	Concentration_VM 	*vm = cli-> get_selected_vm();
	if (vm==NULL) { printf("Need to select vm\n"); return -11; }

	if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
	if (vm->conc==NULL) { printf("Need to select conc\n"); return -11; }
	//------------------
	int r =  cli-> selected_enz->match_start(vm-> conc->getmole(), vm);
	return r;
}
// --------------------------
/*
int	cli_eng_run_vol(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	ChemEngine *eng = cli->world.chem_engine;
	if (eng == NULL) return -2;

	//
	mylist<ChemEnzyme>::mylist_item<ChemEnzyme>  *enz_item = eng-> enz_list.gethead();
	while (enz_item!=NULL) {
		if (enz_item->item != NULL) {

	}
		// ------------
		enz_item = enz_item->next;
	}

}
*/
// --------------------------
int	cli_eng_enznext(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_VM NEED_WORLD
	//Concentration_VM 	*vm = cli-> get_selected_vm();
	if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
	if (vm==NULL) { printf("Need to select vm\n"); return -11; }
	//------------------
	//  time
	float run_time = 1.0;
	char **next_argv = &argv[0];
	{
		float t;
		int r = sscanf(next_argv[0], "%f", &t);
		if (r>0) {
			run_time = t;
			printf("eng.time = [%f]\n", run_time);
			next_argv = &argv[1];
			argc--;
		}
	}
	//------------
	ChemFunc *f =cli-> selected_enz->match_next(vm);
	int r = -1;
	if ((f!=NULL) && (f->operation!=NULL)) {
		r = f->operation(
				cli->selected_ambcell-> cell, &cli->world-> chem_engine, vm, run_time, 0, NULL);
	}

	return r;
}
/*****************************
	int r = -1;

	if (argc>1) {
		int s = sscanf(argv[1], "%f", &_time);
		if (s<0)  { printf("DataError\n"); return -20; }
		r= cli->world.chem_engine. run(cli-> get_selected_vm(), _time, argc-1, &argv[1]);

	} else {
		r= cli->world.chem_engine. run(cli-> get_selected_vm(), _time, argc, argv);
	}
	//printf("run(t=%.f) = [%d]\n", _time, r);
	return r;
}
*******************/
// --------------------------
int	cli_eng_ldr(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_ENG


	mylist<ChemReaction>::mylist_item<ChemReaction>  *reaction_item = NULL;

	if ((argc <1) || (strcmp(argv[0], "help" ) == 0)) {
		printf("usage: ldr +-[0xn]\n");
		cli->world-> chem_engine.reaction_list.dump();
		return 0;
	}

	int off;
	if ( sscanf(argv[0], "%x", &off) <0) {
		printf("bad offset [%s].\n", argv[0]);
		return -20;
	}
	printf("..load [%d]\n", off);

	reaction_item = cli->world->chem_engine.reaction_list.offset(off);
	if (reaction_item==NULL) {	printf("Failed to load reaction[%d]\n", off); return -30;	}
	if (reaction_item->item==NULL) {	printf("item has null reaction[%d]\n", off); return -31;	}

	mylist<MatchPos>::mylist_item<MatchPos> *match_item = reaction_item-> item-> matchpos_list.gethead();
	if (match_item==NULL) { printf("ld reaction[%d] returned NULL match_pos\n", off); return -32;	}

	cli->local_vm.matchpos.clear();

	// DODGY.. but rotate resets current_pos ... so haveto reload for now..
	int r = cli->local_vm.matchpos.load_match( reaction_item-> item-> m1, reaction_item-> item-> enz-> get_mole(),	 match_item->item );
	if (r>=0)
		cli->local_vm.matchpos.rotatemole();
	cli->local_vm.matchpos.load_match( reaction_item-> item-> m1, reaction_item-> item-> enz-> get_mole(),	 match_item->item );
	//cli->world->chem_engine.vm.matchpos.dump();
	return r;
}

// --------------------------
int	load_cli_eng(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "eng");		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_eng, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_dump, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_run, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "runmatch");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_runmatch, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "runfunc");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_runfunc, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tick");	r = cli-> addcmd(&cli-> eng_cmdlist, 		cli_eng_tick, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "maxtick");	r = cli-> addcmd(&cli-> eng_cmdlist, 		cli_eng_maxtick, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "nexttick");	r = cli-> addcmd(&cli-> eng_cmdlist, 		cli_eng_nexttick, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get");	r = cli-> addcmd(&cli-> eng_cmdlist, 		cli_eng_get, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "react");	r = cli-> addcmd(&cli-> eng_cmdlist, 		cli_eng_react, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "runvol");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_runvol, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "cleanmoles");	r = cli-> addcmd(&cli-> eng_cmdlist,  cli_eng_cleanmoles, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enzstart");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_enzstart, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enznext");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_enznext, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ldr");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_ldr, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}

// --------------------------// --------------------------// --------------------------
