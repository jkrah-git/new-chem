#include "../command_callbacks.h"

/*
 * vars.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: jkrah
 */
#include <string.h>
//---------------------------------//---------------------------------
int	cli_var(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	if (argc<1) {
		cli->var_list_dump();
		return 0;
	}
	// else
	return 	cli-> run(&cli-> var_cmdlist, argc,  &argv[0]);
}
//---------------------------------//---------------------------------
int	cli_var_help(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	cli-> var_cmdlist_dump();
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_get(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<1) {
		printf("usage: var get name\n");
		return -1;
	}
	char *val = cli->var_list.get(argv[0]);

	if (val==NULL) {
		printf("Failed to get var[%s]\n", argv[0]);
		return -10;
	}

	printf("'%s'='%s'\n", argv[0], val);
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_set(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc<2) {
		printf("usage: var set name value\n");
		return -1;
	}
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	char buf[KEYVAL_MAX_VAL];
	buf[0] = '\0';
	int c=0;
	for (int i=1; i<argc; i++) {
		if ((strlen(buf) + strlen(argv[i]+1) < KEYVAL_MAX_VAL)) {

			//printf("arg[%d][%s] -> buf[%d][%s]\n", i, argv[i], c, buf);
			if (i>1) buf[c++] = ' ';
			strcpy(&buf[c], argv[i]);
			c += strlen(argv[i]);
			//buf[c+1] = '\0';
		}
	}
	printf("'%s'='%s'\n", argv[0], buf);

	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], buf);
	if (item==NULL) {
		printf("failed to set var[%s]\n", buf);
		return -2;
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc!=1) {
		printf("usage: var clear name\n");
		return -1;
	}
	char S[1] = { '\0' };
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.set(argv[0], S);
	if ((item==NULL)||(item-> item==NULL)) {
		printf("failed to set var[%s]\n", argv[0]);
		return -2;
	} else {
		memset(item-> item-> val, '\0', KEYVAL_MAX_VAL);
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_del(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	if (argc!=1) {
		printf("usage: var clear name\n");
		return -1;
	}
	mylist<KeyValPair>::mylist_item<KeyValPair>  *item = cli->var_list.search(argv[0]);
	if (item!=NULL) {
		cli->var_list.keyvalues.del(item);
	}
	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_var_run(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------

	 if (argc<1) {
		 printf("usage: var run vName..\n");
		 return -1;
	 }

	char *str = cli->var_list.get(argv[0]);
	if (str==NULL) {
		printf("Error reading args\n");
		return -10;
	}
	printf("[%s]\n", str);
	//-----------------------------
	//return 0;
	char payload[KEYVAL_MAX_VAL];
	strncpy(payload, str, KEYVAL_MAX_VAL);

	int r = cli-> runline(&cli-> base_cmdlist, payload);
	if (r!=0) printf("Run = [%d]\n", r);

	return 0;
}
//---------------------------------//---------------------------------
//=======================//=======================//=======================
//---------------------------------//---------------------------------
int	load_cli_var(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];

	// 'VAR' commands
	cli-> var_cmdlist.clear();
	sprintf(name, "var");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_var, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "help"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_help, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "get"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_get, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "set"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_set, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_clear, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "del"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_del, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "run"); 		r = cli-> addcmd(&cli-> var_cmdlist, 	cli_var_run, (char*) name);		LOG("var_cmdlist[%s] = [%d]\n", name, r);
	//----------
	sprintf(name, "run"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_var_run, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
