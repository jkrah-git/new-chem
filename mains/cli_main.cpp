/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */


#include "../chem/Concentration_CLI.h"

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

//-----------------------------------------
//===============================================================
char **character_name_completion(const char *text, int start, int end)
{
	//printf("(1.completion-> start[%d] end[%d] text[%s])", start, end, text);
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
