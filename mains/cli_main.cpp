/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */


#include "../chem/Concentration_CLI.h"
#include "../include/gfx/MoleDisplay.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
//===============================================================
char  **get_args(mylist<CLI_Command> *menu);
char **character_name_completion(const char *, int, int);
char *character_name_generator(const char *, int);

Concentration_VM vm;
ConcentrationVolume vol;
Concentration_CLI cli(vol, vm);

//char **possible_args = NULL;

// --------------------------
int main(int argc, char **argv) {

/*
	printf("main.start\n");
	printf("main.new vm\n");
	printf("main.new vol\n");
	printf("....  new cli\n");*/
	printf("main.start loading commands\n");
	cli.load_commands();
	printf("main.ended loading commands\n");

	int r;
	if (argc>1)
	{ printf("main.args: argc[%d] ", argc);
	  for (int i=0 ; i<argc; i++)	printf("main.argv[%d]=[%s] ", i, argv[i]);	  printf("\n");
	  r = cli.run(&cli.base_cmdlist, argc-1, &argv[1]);
	  printf("Run = [%d]\n", r);
	}

	r = 0;
	char 	prompt[32];

	rl_attempted_completion_function = character_name_completion;

	cli.get_possible_args(&cli.base_cmdlist);
	//printf("cli.possible_args=[0x%zX]\n",  (long unsigned int) cli.args);

	/*
	MoleDisplay mole_display;
	mole_display.open();
	mole_display.grid();

	Peptide pep;
	pep.set('A');
	//mole_display.draw_pep(&pep);

	Molecule m;
	m.test();
	m.dump();
	mole_display.draw_mole(&m);
	*/

	char *line = NULL;
	while(true) {
		sprintf(prompt, "[%d]># ", r);

		line = readline(prompt);
		if (line==NULL) break;

		if (strlen(line)>0) {
			add_history(line);
			r = cli.run(&cli.base_cmdlist, line);
			if (r!=0) printf("Run = [%d]\n", r);
		}
		free(line); line = NULL;
	}
	return r;
}

/*
void get_realine_opts() {

	mylist<CLI_Command> *menu = &cli.base_cmdlist;
    printf("(lb=[%s])", rl_line_buffer);

	int len = strlen(rl_line_buffer);
	if ((len>0) && (rl_line_buffer[len-1]==' ')) {
		char *line = strdup(rl_line_buffer);
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
		if (c>0) {
			printf("last word[%d][%s]", c, argv[c-1]);

			for (int i=0; i<c; i++) {
				mylist<CLI_Command>::mylist_item<CLI_Command>  *item = menu-> gethead();
				mylist<CLI_Command>::mylist_item<CLI_Command>  *submenu_item = NULL;
				while ((item!=NULL)&&(item-> item !=NULL)) {
					if (strcmp(item->item->name, argv[i])==0) {
						submenu_item = item;
						break;
					}
					//--- next item
					item = item-> next;
				}
				if ((submenu_item==NULL)||(submenu_item-> item==NULL)) break;
				//menu = item-> item;
			}// next i

		}//endif

		free(line);
	}

	cli.get_possible_args(menu);
}
*/
//-----------------------------------------
//===============================================================
char **character_name_completion(const char *text, int start, int end)
{
	//printf("(1.completion-> start[%d] end[%d] text[%s])", start, end, text);
    //printf("(lb=[%s])", rl_line_buffer);
   // get_realine_opts();

    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
}
//===============================================================
char *character_name_generator(const char *text, int state)
{
	//printf("(2.gen-> state[%d] text[%s])", state, text);
	if ( cli.args==NULL) {
		//printf("possible_args=[0x%zX]\n",  (long unsigned int)  cli.args);
		return NULL;
	}

	//-------------------
    static int list_index, len;
    char *name;

    if (state==0) {
        list_index = 0;
        len = strlen(text);
    }

//    while ((name = cli.possible_args[list_index++])) {
    while ((name =  cli.args[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

//===============================================================
