/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */

//===============================================================
//#include "chem/Concentration_CLI.h"
#include "chem/display.old/ChemDisplay.h"
//===============================================================
char  **get_args(mylist<CLI_Command> *menu);


// these two are joined by call backs so have to be globals
Concentration_CLI	cli;
ChemDisplay			display(&cli);
World				world;

int 	run_callto(int argc, char **argv);
char  **get_possible_args(void);
// --------------------------
char 	**build_args(void){

	cli.world = &world;
	cli.run_callto = run_callto;

//	int r = world.chem_engine.logger.start((const char*)  "./chem.fifo", 1024);
//	PRINT("Logger start = [%d]\n", r);
//	sprintf(world.chem_engine.logger.get_buf(), "Logger started..\n");
//	world.chem_engine.logger.flush();


	return get_possible_args();
}
#include <unistd.h>
//-----------------------------------
int 	run(int argc, char **argv){
	return cli.run(&cli.base_cmdlist, argc, argv);
}
//-----------------------------------
int 	run_callto(int argc, char **argv){
	return display.run(&display.display_cmdlist, argc, argv);
}
//===============================================================
extern char 		**args;
char  **get_possible_args(void){
//	PRINT("start.possible_args[0x%zX]\n", (long unsigned int)  args);
	if (args!=NULL) {
		int c=0;
		while (args[c] != NULL)
			free(args[c++]);
		free(args);
		args = NULL;
	}

//	PRINT("free.possible_args[0x%zX]\n", (long unsigned int)  args);
	// add one for NULL ptr at end of list..
	int c = cli.base_cmdlist.count()+1;
	c = c + display.display_cmdlist.count();
//		PRINT("c(count+1)=[%d]\n", c);

	args = (char **) malloc(sizeof(char*)*c);
//		PRINT("malloc=[0x%zX]\n",  (long unsigned int)  args);
	if (args==NULL) return NULL;


	int i=0;
	{
		mylist<Display_Command>::mylist_item<Display_Command>  *item = display.display_cmdlist.gethead();
		while ((item!=NULL)&&(item-> item !=NULL)) {
			args[i] = strdup(item->item->name);
	//			PRINT("arg[%d]=[%s]\n", i, args[i]);
			//
			item = item-> next;
			i++;
		}
	}

	{
		mylist<CLI_Command>::mylist_item<CLI_Command>  *item = cli.base_cmdlist.gethead();
		while ((item!=NULL)&&(item-> item !=NULL)) {
			args[i] = strdup(item->item->name);
	//			PRINT("arg[%d]=[%s]\n", i, args[i]);
			//
			item = item-> next;
			i++;
		}
	}
	// terminate word array
	args[i] = NULL;
//	PRINT("final_null[0x%zX]=[%d]\n", (long unsigned int)  args, i);
	if (args!=NULL) {
		int c=0;
		while (args[c] != NULL) {
		//	printf("possible_args[%d]=[%s]\n", c, args[c]);
			c++;
		}
	}
	//possible_args = args;
	return args;
}

//-----------------------------------------------------------------------------
