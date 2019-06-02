

// --------------------------// --------------------------// --------------------------
// main VM Callback
int main_cb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.main();
	return 0;
}

// --------------------------// --------------------------// --------------------------
void matchcb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return;
	cli->display.gfx.title = (const char*) "Match";
	cli->display.gfx.open();
	cli->display.gfx.clear();
	cli->display.grid(0,0,100);
	cli->display.draw_match(&cli->core->matchpos);
}
// --------------------------
void molecb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return;
	cli->display.gfx.title = (const char*) "Mole";
	cli->display.gfx.open();
	cli->display.gfx.clear();
	//cli->display.setcol(0,100,0);
	cli->display.draw_vm(cli-> core);

	cli->display.grid(0,0,100);
	cli->display.draw_mole(cli->core->mole, 0, 100, 0);

	char msg[128];
	if (cli->core->mole==NULL)
		sprintf(msg, "<NULL>");
	else
		sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) cli->core->mole);
	cli->display.gfx.printg(msg);

}

// --------------------------
int	cli_load_gfx(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

/*
	CLI_Command  *cmd;
	cmd = search_cmd_list(&cli-> base_cmdlist, "match");
	if (cmd!=NULL) { cmd->callback = matchcb; 	}

	cmd = search_cmd_list(&cli-> base_cmdlist, "mole");
	if (cmd!=NULL) { cmd->callback = molecb; 	}
	return 0;
	*/
	cli-> callback = main_cb;
	main_cb(cli, argc, argv);
	return 0;
}
