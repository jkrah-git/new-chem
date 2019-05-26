// -------------------

#include "../chem/Peptide.h"
#include "../chem/Molecule.h"
//#include "../chem/Concentration.h"
//#include "../chem/mybuffer.h"
//#include "../chem/MoleculeMatchPos.h"
//#include "../chem/Concentration_CLI.h"
//#include "../chem/CLI_Command.h"
//#include "../include/mylist.h"
#include "../include/gfx/MoleDisplay.h"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
// --------------------------


char **character_name_completion(const char *, int, int);
char *character_name_generator(const char *, int);
char 						**args = NULL;

//===============================================================
char **character_name_completion(const char *text, int start, int end)
{
	//printf("(1.completion-> start[%d] end[%d] text[%s])", start, end, text);
    //printf("(lb=[%s])", rl_line_buffer);
   // get_realine_opts();

    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
};

#include <string.h>

//===============================================================
char *character_name_generator(const char *text, int state)
{
	//printf("(2.gen-> state[%d] text[%s])", state, text);
	if ( args==NULL) {
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
    while ((name =  args[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}


//===============================================================






void test_mole(void) {
	printf("test_mole.start..\n");
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




	printf("test_mole.end..\n");
}
// --------------------------

int main(int argc, char **argv)
{
	printf("main.start..\n");

	char 	prompt[32];
	rl_attempted_completion_function = character_name_completion;

	if (argc>1) {
		printf("CMD = [%s]\n", argv[1]);
		//if ( (strcmp(argv[1], "test_rot")==0))			test_rot();


	//-------------
	} else {
		printf("running interactive..\n");
		test_mole();

		char *line = NULL;
		int r =0;
		while(true) {
			sprintf(prompt, "[%d]># ", r);
			line = readline(prompt);
			if (line==NULL) break;

			if (strlen(line)>0) {
				add_history(line);
				//r = cli.run(&cli.base_cmdlist, line);
				//if (r!=0) printf("Run = [%d]\n", r);
			}
			free(line); line = NULL;
		}

	}

	printf("main.end..\n");
	return 0;
}

//----------------------------------
