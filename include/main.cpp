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
const char 		**args = NULL;

//=================== need to be declared externally
const char 	**build_args(void);
int 	run(int argc, char **argv);
//==========================================================
//  run_args(char *line){
#define MAX_LINELEN 64
#define MAX_ARGS 8
//----------------
int run_args(char *line){
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
		//printf("line read error\n");
		return -100;
	}

	add_history(buf);
	return run(c, argv);
	//int r = run(cmd_list, c, argv);
}

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
    const char *name;

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
	printf("(main.setup..)\n");
	args = build_args();

	printf("(main.run..)\n");
	int argn = 1;
	char *line = NULL;
	int r =0;
	while(true) {

		if (argn < argc) {
			//r = run_line(argv[argn++]);
			r = run_args(argv[argn++]);
		} else {
			sprintf(prompt, "[%d]># ", r);
			line = readline(prompt);
			if (line==NULL)
				break;
			r = run_args(line);
			free(line);
			line = NULL;
		}
	}
	printf("(main.end..)\n");
	return 0;
}
//=======================================================

//----------------------------------
