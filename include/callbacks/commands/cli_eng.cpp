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


			//int r =  cli-> selected_enz->match_next(cli-> chem_engine, vm);
			// r = chemfunc->operation(eng, vm, 0 , NULL);
			ChemFunc *f =cli-> selected_enz->match_next(vm);
			int r = -1;
			if ((f!=NULL) && (f->operation!=NULL))
					r = f->operation(cli->chem_engine, vm, run_time, 0, NULL);
			//printf("next(t=%.f) = [%d]\n", run_time, r);
			return r;
		}
	}
	// else
	return cli->chem_engine-> run(cli-> get_selected_vm(), run_time, argc, next_argv);
}
*****************/
// --------------------------
// 'run'
int	cli_eng_run(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
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
	return cli->chem_engine-> run(cli-> get_selected_vm(), run_time, argc, next_argv);

}
// --------------------------
// 'dump'
int	cli_eng_dump(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	DUMP(cli-> chem_engine)
	return 0;
}
// --------------------------
// --------------------------
// 'list'
int	cli_eng_list(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI
	DUMP(cli-> chem_engine)
	return 0;
}
// --------------------------
// 'enzstart'
int	cli_eng_enzstart(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli-> chem_engine == NULL) return -2;

	Concentration_VM 	*vm = cli-> get_selected_vm();
	if (vm==NULL) { printf("Need to select vm\n"); return -11; }

	if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
	if (vm->conc==NULL) { printf("Need to select conc\n"); return -11; }
	//------------------
	int r =  cli-> selected_enz->match_start(vm-> conc->getmole(), vm);
	return r;
}
// --------------------------
int	cli_eng_enznext(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli-> chem_engine == NULL) return -2;
	Concentration_VM 	*vm = cli-> get_selected_vm();
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
		r = f->operation(cli->chem_engine, vm, run_time, 0, NULL);
	}

	return r;
}
/*****************************
	int r = -1;

	if (argc>1) {
		int s = sscanf(argv[1], "%f", &_time);
		if (s<0)  { printf("DataError\n"); return -20; }
		r= cli->chem_engine-> run(cli-> get_selected_vm(), _time, argc-1, &argv[1]);

	} else {
		r= cli->chem_engine-> run(cli-> get_selected_vm(), _time, argc, argv);
	}
	//printf("run(t=%.f) = [%d]\n", _time, r);
	return r;
}
*******************/
// --------------------------
int	load_cli_eng(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "eng");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_eng, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_dump, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_run, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enzstart");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_enzstart, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "enznext");	r = cli-> addcmd(&cli-> eng_cmdlist, 	cli_eng_enznext, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}

// --------------------------// --------------------------// --------------------------
