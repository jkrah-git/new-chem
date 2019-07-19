/*
 * Concentration_CLI.cpp
 *
 *  Created on: Jan 26, 2019
 *      Author: jkrah
 */

#include "Concentration_CLI.h"
#include <string.h>

// -------------------
//#include "Concentration_CLI_External_Commands.cpp"

//#include "callbacks/Concentration_CLI.Callbacks/base.cpp"
//#include "callbacks/Concentration_CLI.Callbacks/vars.cpp"
//#include "callbacks/Concentration_CLI.Callbacks/match.cpp"
//#include "Concentration_CLI.Callbacks/display.cpp"
//#include "../include/callbacks/menu/menu_callbacks.h"
//#include "callbacks/screen_callbacks.h"
#include "callbacks/command_callbacks.h"
// -------------------
//---------------------------------//---------------------------------
/*
//---------------------------------//---------------------------------
class Concentration_CLI {
private:
public:
	Concentration_VM			*core;
	mylist<Concentration_VM>	vm_list;
	int							last_result;

	mylist<CLI_Command>			base_cmdlist;
	mylist<CLI_Command>			dump_cmdlist;
	mylist<CLI_Command>			load_cmdlist;
	mylist<CLI_Command>			clear_cmdlist;
	mylist<CLI_Command>			stack_cmdlist;
	mylist<CLI_Command>			pep_cmdlist;
	mylist<CLI_Command>			mole_cmdlist;
	mylist<CLI_Command>			conc_cmdlist;
	mylist<CLI_Command>			var_cmdlist;
	mylist<CLI_Command>			match_cmdlist;

	KeyValList					var_list;
	char 						**args;
	MoleDisplay 				mole_display;
	void 	(*run_callback)(void);

	Concentration_CLI(ConcentrationVolume &cvol, Concentration_VM &vm);
	virtual ~Concentration_CLI();
	void	load_commands();
	void 	dump();
	void 	test();

	int		addcmd(mylist<CLI_Command> *cmd_list, int 	(*op)(Concentration_CLI*, int, char**), char *name);
	int		run(mylist<CLI_Command> *cmd_list, int argc, char **argv);
	int		run(mylist<CLI_Command> *cmd_list, char *line);

	void	base_cmdlist_dump(void) { printf ("Basic Commands => ");  	base_cmdlist.dump(); }
	void	dump_cmdlist_dump(void) { printf ("'dump' Commands => ");  	dump_cmdlist.dump(); }
	void	load_cmdlist_dump(void) { printf ("'load' Commands => ");  	load_cmdlist.dump(); }
	void	clear_cmdlist_dump(void) { printf ("'clear' Commands => ");	clear_cmdlist.dump(); }
	void	stack_cmdlist_dump(void) { printf ("'stack' Commands => "); stack_cmdlist.dump(); }
	void	pep_cmdlist_dump(void) { printf ("'pep' Commands => ");  	pep_cmdlist.dump(); }
	void	mole_cmdlist_dump(void) { printf ("'mole' Commands => ");  mole_cmdlist.dump(); }
	void	conc_cmdlist_dump(void) { printf ("'conc' Commands => ");  	conc_cmdlist.dump(); }
	void	var_cmdlist_dump(void) { printf ("'var' Commands => ");  	var_cmdlist.dump(); }
	void	match_cmdlist_dump(void) { printf ("'match' Commands=> "); 	match_cmdlist.dump(); }

	void	var_list_dump(void) { printf ("'Variables' => ");  			var_list.dump(); }
	char 	**get_possible_args(mylist<CLI_Command> *menu);

};
//---------------------------------
*/


char  **Concentration_CLI::get_possible_args(mylist<CLI_Command> *menu){

//	PRINT("start.possible_args[0x%zX]\n", (long unsigned int)  args);
	if (args!=NULL) {
		int c=0;
		while (args[c] != NULL)
			free(args[c++]);
		free(args);
		args = NULL;
	}

//	PRINT("free.possible_args[0x%zX]\n", (long unsigned int)  args);

	if (menu!=NULL) {
		// add one for NULL ptr at end of list..
		int c = menu->count()+1;
//		PRINT("c(count+1)=[%d]\n", c);

		args = (char **) malloc(sizeof(char*)*c);
//		PRINT("malloc=[0x%zX]\n",  (long unsigned int)  args);
		if (args==NULL) return NULL;


		int i=0;
		mylist<CLI_Command>::mylist_item<CLI_Command>  *item = menu-> gethead();
		while ((item!=NULL)&&(item-> item !=NULL)) {
			args[i] = strdup(item->item->name);
//			PRINT("arg[%d]=[%s]\n", i, args[i]);
			//
			item = item-> next;
			i++;
		}

		// terminate word array
		args[i] = NULL;
	//	PRINT("final_null[0x%zX]=[%d]\n", (long unsigned int)  args, i);
	}


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
//---------------------------------
void Concentration_CLI::dump() {

//	printf("Concentration_CLI[0x%zX]:: vol[0x%zX],conc[0x%zX],mole[0x%zX]\n",
//			(long unsigned int) this,
//			(long unsigned int) vol,
//			(long unsigned int) conc,
//			(long unsigned int) mole );
	printf("Concentration_CLI[0x%zX]\n", (long unsigned int) this);
	//ChemEnzyme *enz = NULL;
	//if (chem_engine != NULL) enz = chem_engine-> search_enz(selected_enz);
	if (selected_enz==NULL) { printf("selected_enz[NULL]\n");	}
	else {
		printf("selected_enz[0x%zX]", (long unsigned int) selected_enz);
		selected_enz-> dump();
	}

	//printf("World:\n");	DUMP(world)
	//world.dump();

	local_vm.dump();
	//local_vol.dump();

	printf("=========== World ==========\n");
	DUMP(world);


	/*
	printf("============ VOL's ================..\n");
	vol_list.dump();

	printf("==================== VM's ==============\n");
	vm_list.dump();
	*/

	return;
	base_cmdlist_dump(); 	//printf("'Base' Commands..\n");	base_cmdlist.dump();
	dump_cmdlist_dump(); 	//printf("'dump' Commands..\n");	dump_cmdlist.dump();
	load_cmdlist_dump(); 	//printf("'load' Commands..\n");	load_cmdlist.dump();
	clear_cmdlist_dump(); 	//printf("'clear' Commands..\n");	clear_cmdlist.dump();
	stack_cmdlist_dump(); 	//printf("'stack' Commands..\n");	stack_cmdlist.dump();
	pep_cmdlist_dump(); 	//printf("'pep' Commands..\n");	pep_cmdlist.dump();
	mole_cmdlist_dump(); 	//printf("'mole' Commands..\n");	mole_cmdlist.dump();
	conc_cmdlist_dump(); 	//printf("'conc' Commands..\n");	conc_cmdlist.dump();
	var_cmdlist_dump(); 	//printf("'var' Commands..\n");		var_cmdlist.dump();
	var_list_dump(); 		//printf("Variables..\n");		vars_list.dump();
	//printf("last_result = [%d] : last_line = [%s]\n", last_result, last_line);
	//display.dump();
}
//---------------------------------

Concentration_CLI::Concentration_CLI(){ //ConcentrationVolume &cvol){ //, Concentration_VM &vm) {

	args = NULL;
	callback = NULL;
	run_callto = NULL;
	last_result = 0;
	selected_enz = NULL;
	selected_ambcell = NULL;
	world = NULL;
	local_vm.vol = NULL; //&local_vol;

	load_commands();

}
//---------------------------------
Concentration_CLI::~Concentration_CLI() {}

//========================================================
//---------------------------------//---------------------------------//---------------------------------
int	Concentration_CLI::addcmd(mylist<CLI_Command> *cmd_list, int 	(*op)(Concentration_CLI*, int, char**), char *name){
	if ((cmd_list==NULL)||(op==NULL)||(name==NULL)) return -1;

	mylist<CLI_Command>::mylist_item<CLI_Command> *cmd = cmd_list-> add();
	if (cmd==NULL) return -10;
	if (cmd-> item ==NULL) return -11;

	cmd-> item-> operation = op;
	sprintf(cmd-> item-> name, "%s", name);
	return 0;
}


//---------------------------------
int	Concentration_CLI::runline(mylist<CLI_Command> *cmd_list, char *line) {
	if ((cmd_list==NULL) || (line==NULL)) return -100;

	// make a local copy
	char buf[MAX_LINELEN];
	strncpy(buf, line, MAX_LINELEN);


	char	*word, *argv[MAX_ARGS];
	int c = 0;
	word = strtok (line," \n");
	if (word!=NULL) {
		for (int i=0; i<MAX_ARGS; i++) {
			c++;
			argv[i] = word;
			word = strtok (NULL," \n");
			if (word==NULL) break;
		}
	}
	// check split results
	if (c<1) {
		return -10;
	}

	return run(cmd_list, c, argv);
	//return r;
}
/*******************************
//-----------------------------------
CLI_Command  *search_cli_cmd_list(mylist<CLI_Command> *cmd_list, const char *name) {
	CLI_Command  *cmd = NULL;
	mylist<CLI_Command>::mylist_item<CLI_Command>  *next_item = cmd_list-> gethead();
	while ((next_item!=NULL) && (next_item-> item != NULL)) {
		int r = strcmp(name, next_item-> item->name);
		if (r==0) {
			cmd = next_item-> item;
			break;
		}
		// ---
		next_item = next_item->next;
	}
	return cmd;
}
//---------------------------------
*******************************/
//-----------------------------------
CLI_Command *Concentration_CLI::search_cli_cmd_list(mylist<CLI_Command> *cmd_list, const char *name) {
	CLI_Command  *cmd = NULL;
	mylist<CLI_Command>::mylist_item<CLI_Command>  *next_item = cmd_list-> gethead();
	while ((next_item!=NULL) && (next_item-> item != NULL)) {
		int r = strcmp(name, next_item-> item->name);
		if (r==0) {
			cmd = next_item-> item;
			break;
		}
		// ---
		next_item = next_item->next;
	}
	return cmd;
}
//---------------------------------
int	Concentration_CLI::run(mylist<CLI_Command> *cmd_list, int argc, char **argv){
	if ((cmd_list==NULL) || (argc<1) || (argv==NULL)) return -100;

	// start with base command list..
	CLI_Command  *cmd = search_cli_cmd_list(cmd_list, argv[0]);
	last_result = 0;

	// if not in  base command list..
	if (cmd==NULL) {
		// fwd to 'callto' or 'not found' error (-110)
		if (run_callto==NULL) {	last_result =  -110;	}
		else {	last_result = run_callto(argc, argv);		}

	} else { // is base command
		// check/run base_command,operator
		if (cmd-> operation==NULL) {
			printf("[%s].Command.operation NULL\n", argv[0]);
			last_result =  -111;
		} else  {
			last_result = cmd-> operation(this, argc-1, &argv[1]);
		}

		//LOG("[%s].[%d]\n", argv[0], last_result);
/*
		if (cmd->callback !=NULL) {
			cmd->callback(this, 0, NULL);
		}
*/

	} // end base command

	if (last_result == -110) printf("[%s].Command Not Found\n", argv[0]);

	// Cli.callbak
	if (callback!=NULL) {
		callback(this, argc-1, &argv[1]);
	}

	// if base command - include (callto)(final callbacks)
	if ((cmd!=NULL)&&(run_callto !=NULL)) {
		run_callto(0, NULL);
	}


	//PRINT("final.last_result=[%d]\n", last_result);
	return last_result;
}
//---------------------------------

//---------------------------------
int Concentration_CLI::argstr(char *dest, int max, int argc, char **argv){
	int r = 0;
	if (dest!=NULL) {
		int a=0;
		int p=0;
		while (a<argc) {
			int len = strlen(argv[a]);
			if ((p+len+1) >= max) break;
			// -- else ok to get next arg
			if (p>0) {  dest[p++] = ' '; }
			strncpy(&dest[p], argv[a], (max-p));
			p+= len;
			a++;
			r=p;
		}
	}
	return r;
}

//---------------------------------//---------------------------------
void Concentration_CLI::load_commands() {
	//cli_load_commands(this, 0, NULL);

	cli_load_base(this, 0, NULL);
	load_cli_dump(this, 0, NULL);

	load_cli_pep(this, 0, NULL);
	load_cli_mole(this, 0, NULL);
	load_cli_conc(this, 0, NULL);
	load_cli_vol(this, 0, NULL);
	load_cli_var(this, 0, NULL);
	load_cli_match(this, 0, NULL);
	load_cli_stack(this, 0, NULL);
	load_cli_vm(this, 0, NULL);
	load_cli_eng(this, 0, NULL);
	load_cli_enz(this, 0, NULL);
	load_cli_world(this, 0, NULL);
	load_cli_cell(this, 0, NULL);

	//cli_load_gfx(this, 0, NULL);

	/* moved to void ChemDisplay::load_display_commands(void){
	cli_load_screen(this, 0, NULL);
	cli_load_menu(this,0, NULL);
	cli_load_button(this,0, NULL);
	cli_load_pepdisp(this,0, NULL);
	cli_load_moledisp(this,0, NULL);
	cli_load_peplist(this,0, NULL);
	cli_load_molelist(this,0, NULL);
	*/
}

//---------------------------------//---------------------------------
/*
Concentration	*Concentration_CLI::search_conc(char *name) {
	Concentration *result  = NULL;
	return result;
}
*/
