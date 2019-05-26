// -------------------
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
// --------------------------
 #include <stdlib.h>


char 		**character_name_completion(const char *, int, int);
char 		*character_name_generator(const char *, int);
char 		**args = NULL;

//=================== need to be declared externally
char **build_args(void);
int run_line(char *line);
//===================
//===============================================================
// from .. [char  **Concentration_CLI::get_possible_args(mylist<CLI_Command> *menu)]
//===============================================================
char **character_name_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
};
//===============================================================
char *character_name_generator(const char *text, int state)
{
	if ( args==NULL) {	return NULL;	}
	//-------------------
    static int list_index, len;
    char *name;

    if (state==0) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name =  args[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }
    return NULL;
}
//===============================================================
int main(int argc, char **argv)
{
	printf("(main.start..)\n");
	rl_attempted_completion_function = character_name_completion;
//-------------
	char 	prompt[32];
	sprintf(prompt, "># ");
	args = build_args();

	int argn = 1;
	char *line = NULL;
	//int r =0;
	while(true) {

		if (argn < argc) {
			//line = argv[argn++];
			run_line(argv[argn++]);
		} else {
			line = readline(prompt);
			if (line==NULL)
				break;

			run_line(line);
			free(line);
			line = NULL;
		}

	}
	printf("(main.end..)\n");
	return 0;
}
//=======================================================

//----------------------------------
