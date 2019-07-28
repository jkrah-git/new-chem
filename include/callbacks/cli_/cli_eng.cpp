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
// --------------------------
// 'run'
int	cli_eng_run(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	PRINT("-------------\n");
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
	Cell *cell= NULL;
	if (cli->selected_ambcell !=NULL)
		cell = cli->selected_ambcell->cell;


	return cli->world-> chem_engine. run( cell, &cli->local_vm, run_time, argc, next_argv);


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
	int r = cli->world-> chem_engine.reaction_list.count();
	printf("Found [%d] cache entries..\n", r);
	cli->world-> chem_engine.reaction_list.dump();
	return r;
}
// --------------------------
// --------------------------
// 'runvol'
int	cli_eng_runmatch(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VOL
	// ----------------------------
	return cli->world-> chem_engine.get_reactions(cli->local_vm.vol);
}
// --------------------------
// --------------------------
// 'match'
int	cli_eng_runfunc(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD  NEED_VOL
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
	return cli->world-> chem_engine. run_reactions(cli->selected_ambcell-> cell, cli->local_vm.vol, run_time);
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
	NEED_CLI NEED_WORLD NEED_VOL
	int r =  cli->world-> chem_engine. get_reactions(cli->local_vm. vol);
	printf("chem_engine. get_reactions(vol) = [%d]\n", r);
	return r;

}
// --------------------------
// int	ChemEngine::run_reactions(Concentration_VM *vm, ConcentrationVolume *vol, ChemTime run_time){
// --------------------------
// 'run'
int	cli_eng_react(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VOL

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
	return cli->world-> chem_engine. run_reactions(cli->selected_ambcell-> cell, cli->local_vm. vol, run_time);
}
// --------------------------
#include <time.h>
#include <unistd.h>
#include <stdio.h>
// --------------------------
// 'runvol'
int	cli_eng_runvol(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD NEED_VOL
	// ----------------------------
	float run_time = 1.0;
	int 	repeat = 1;
	if (argc>0)	{
		float t;
		int r = sscanf(argv[0], "%f", &t);
		if (r<1) { printf ("Bad Data\n"); return -20; }
		run_time = t;
		if (argc>1)	{
			int t;
			int r = sscanf(argv[1], "%d", &t);
			if (r<1) { printf ("Bad Data\n"); return -20; }
			repeat = t;
		}
	}
	int n=0;
	printf("run_time = [%f]\n", run_time);
	printf("repeat = [%d]\n", repeat);
	//-------
	clock_t 	start_ticks = clock();
	time_t 		start_time;
	time(&start_time);

	//-------
	for (int i=0; i<repeat; i++) {
		int r = cli->world-> chem_engine.run_volume(cli->selected_ambcell-> cell, cli->local_vm.vol, run_time);
		if (r>=0)
			n++;
		//printf("chem_engine.run_volume[%d] = [%d]\n", i, r);
	}
	//-------
	clock_t end_ticks = clock();
	time_t end_time;
	time(&end_time);
	//-------

	long elapsed_ticks = ((long) (end_ticks - start_ticks)/1000);
	//printf("start_t[%ld], end_t[%ld] , elapsed_t[%ld]\n", start_t, end_t, elapsed_t);
	printf("chem_engine.run_volume[%d] took ..\n", repeat);
	printf("%.3f (sec) Real Time and %ld (msec) CPU Time\n", difftime(end_time, start_time), elapsed_ticks);

	return n;
}
// --------------------------
// int	ChemEngine::clean_volume_moles(ConcentrationVolume *vol) {
// --------------------------
// 'runvol'
//int	cli_eng_cleanmoles(Concentration_CLI *cli, int argc, char **argv){
//	NEED_CLI NEED_WORLD NEED_VOL	return cli->world-> chem_engine. clean_volume_moles(cli->local_vm. vol);
//}
// --------------------------
// 'enzstart'
int	cli_eng_enzstart(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	//Concentration_VM 	*vm = cli-> get_selected_vm();
	// if (vm==NULL) { printf("Need to select vm\n"); return -11; }

	if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
	if (cli->local_vm.conc==NULL) { printf("Need to select conc\n"); return -11; }
	//------------------
	int r =  cli-> selected_enz->match_start(cli->local_vm. conc->getmole(), &cli->local_vm);
	return r;
}
// --------------------------
// --------------------------
int	cli_eng_enznext(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	//Concentration_VM 	*vm = cli-> get_selected_vm();
	if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
	//if (vm==NULL) { printf("Need to select vm\n"); return -11; }
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
	ChemFunc *f =cli-> selected_enz->match_next(&cli->local_vm);
	int r = -1;
	if ((f!=NULL) && (f->operation!=NULL)) {
		r = f->operation(
				cli->selected_ambcell-> cell, &cli->world-> chem_engine, &cli->local_vm, run_time, 0, NULL);
	}

	return r;
}
// --------------------------
// 'ldr - load reaction'
int	cli_eng_ldr(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD


	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit>  *reaction_item = NULL;

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

	// we include M2 rotation this time
	int r = cli->local_vm.matchpos.load_match(
			reaction_item-> item-> m1,
			reaction_item-> item-> enz-> get_mole(),
			match_item->item , true);

	return r;
}
// --------------------------
// 'ldr - load reaction'
int	cli_eng_clip(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	float conc_clip = cli->world->chem_engine.conc_clip;
	float conc_min = cli->world->chem_engine.conc_min;
	float conc_max = cli->world->chem_engine.conc_max;

	if ((argc>0) && (sscanf(argv[0], "%f", &conc_clip)<0)) { printf("Bad Data\n"); return -30; }
	if ((argc>1) && (sscanf(argv[1], "%f", &conc_min)<0)) { printf("Bad Data\n"); return -31; }
	if ((argc>2) && (sscanf(argv[2], "%f", &conc_max)<0)) { printf("Bad Data\n"); return -32; }

	if (argc>0) {
		if (conc_max <=conc_min) { printf("max must be > min\n"); return -35; }
		if (conc_clip <= conc_min) { printf("clip must be > min\n"); return -36; }

		cli->world->chem_engine.conc_clip = conc_clip;
		cli->world->chem_engine.conc_min = conc_min;
		cli->world->chem_engine.conc_max = conc_max;
	}

	printf("conc_clip=[%f] conc_min=[%f] conc_max=[%f]\n",
			cli->world->chem_engine.conc_clip,
			cli->world->chem_engine.conc_min,
			cli->world->chem_engine.conc_max);
	return 0;
}
// --------------------------
// 'ldr - load reaction'
int	cli_eng_clear(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD

	int r = cli->world->chem_engine. clear_all_hits();
	printf(" clear_all_hits() = [%d]\n", r);
	return r;
}
// --------------------------

// --------------------------
// -------------------------- // --------------------------
int	load_cli_eng(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "eng");		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_eng, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_dump, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "list");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_list, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_run, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "runmatch");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_runmatch, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "runfunc");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_runfunc, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "tick");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_tick, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "maxtick");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_maxtick, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_get, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "react");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_react, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "runvol");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_runvol, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "cleanmoles"); r = cli-> addcmd(&cli-> eng_cmdlist,	cli_eng_cleanmoles, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enzstart");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_enzstart, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enznext");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_enznext, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ldr");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_ldr, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clip");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_clip, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear");		r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_clear, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}

// --------------------------// --------------------------// --------------------------
