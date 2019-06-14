/*
 * cli_coods.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
//int	read_arg(char *argv) {
//	int v,r;
//	r= sscanf(argv, "%d", &v);
//}
// --------------------------
int cli_redraw(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.draw_screen(cli-> display.selected_screen, cli);
	return 0;
}
// --------------------------
int	cli_col(ChemDisplayColor *col, int argc, char **argv) {
	if (col==NULL) return -1;

//	if (argc>0) { PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]); }
//	else { PRINT(" attribs : argc[%d][]\n", argc); }

	// argc=0 argv()  (list)
	if ((argc<2) ||(strcmp(argv[0], "help")==0)) {
		printf("r g b\n");
		return 0;
	}
	//================================
	// 1 argv(dump)
	if (argc==1) {
		//---------------- dump
		if (strcmp(argv[0], "dump")==0) {
			col-> dump(); NL
			return 0;
		}
	}

	//---------------- dump
	if (strcmp(argv[0], "dump")==0) {
		col-> dump(); NL
		return 0;
	}

	if (argc==3) {
		int r,g,b;
		if ((sscanf(argv[0], "%d", &r)<1) ||
			(sscanf(argv[1], "%d", &g)<1) ||
			(sscanf(argv[2], "%d", &b)<1))	{
			printf("data error\n");
			return -10;
		}
		col->set(r,g,b);
		printf("col[%d,%d,%d]\n", r,g,b);
		return 0;


	}
	return -1;
}

// --------------------------
int	cli_coords(ChemDisplayCoords *coods, int argc, char **argv) {
	if (coods==NULL) return -1;

//	if (argc>0) { PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]); }
//	else { PRINT(" attribs : argc[%d][]\n", argc); }

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "help")==0)) {
		printf("(attrib)\n");
		printf("dump\n");
		printf("pos x y\n");
		printf("scale x y\n");
		printf("offset x y\n");
		return 0;
	}
	//================================
	// 1 argv(dump)
	if (argc==1) {
		//---------------- dump
		if (strcmp(argv[0], "dump")==0) {
			coods-> dump(); NL
			return 0;
		}

		// --- else unknown command
 		printf("unknown command[%s]\n", argv[0]);
 		return -10;
		//----------
	} // -- end (argc==1) (known commands)
	//================================
	//---------------- pos
	if (strcmp(argv[0], "pos")==0) {

/*
		PepPosVecType *p = coods->getpos();
		if (p==NULL) {	printf("pos[NULL]\n");	return -20;	}
		if (argc<3)  {	printf("pos[%d,%d]\n", p[PEPPOS_X], p[PEPPOS_Y]);	return 0;		}
*/
	//	PepPosVecType *p = coods->getpos();
	//	if (p==NULL) {	printf("pos[NULL]\n");	return -20;	}
		if (argc<3)  {	printf("pos[%d,%d]\n", coods->posx, coods->posy);	return 0;		}



		int px,py;
		if ((sscanf(argv[1], "%d", &px)<1) ||
			(sscanf(argv[2], "%d", &py)<1))	{
			printf("data error\n");
			return -10;
		}
	//	coods->setpos(px, py);
		coods->posx = px;
		coods->posy = py;
		printf("pos[%d,%d]\n", coods->posx, coods->posy);
		return 0;
	} // end argv(pos)
	//================================
	//================================
	//---------------- scale
	if (strcmp(argv[0], "scale")==0) {
		if (argc<3) {
			printf("scale[%d,%d]\n", coods-> scalex, coods-> scaley);
			return 0;
		}
		//attribs-> dump();
		int px,py;
		if ((sscanf(argv[1], "%d", &px)<1) ||
			(sscanf(argv[2], "%d", &py)<1))	{
			printf("data error\n");
			return -10;
		}
		coods->scalex  = px;
		coods->scaley  = py;
		printf("scale[%d,%d]\n", coods-> scalex, coods-> scaley);

		return 0;
	} // end argv(scale)
	//================================

	//================================
	//---------------- offset
	if (strcmp(argv[0], "offset")==0) {
		if (argc<3) {
			printf("offset[%d,%d]\n", coods-> offsetx, coods-> offsety);
			return 0;
		}
		//attribs-> dump();
		int px,py;
		if ((sscanf(argv[1], "%d", &px)<1) ||
			(sscanf(argv[2], "%d", &py)<1))	{
			printf("data error\n");
			return -10;
		}
		coods->offsetx = px;
		coods->offsety = py;
		printf("offset[%d,%d]\n", coods-> offsetx, coods-> offsety);
		return 0;
	} // end argv(pos)
	//================================


	// --- else unknown command
	printf("unknown command[%s]\n", argv[0]);
	//------------
	return 0;
}
//----------------------
// ChemMenuButton:: int		(*callback)(Concentration_CLI*, int, char**)
// int		cli_callback(Concentration_CLI*, int argc, char **argv) {
//---------------
/*** https://www.newty.de/fpt/fpt.html#r_value ***
 * 	// Direct solution: Function takes a char and returns a pointer to a
	// function which is taking two floats and returns a float. <opCode>
	// specifies which function to return
		float (*GetPtr1(const char opCode))(float, float)
 */
//---------------
int (*cli_callback(Concentration_CLI*, int argc, char **argv))(Concentration_CLI*, int argc, char **argv) {

	// if (argc>0) { PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]); }
	// else { PRINT(" attribs : argc[%d][]\n", argc); }

	//PRINT("=======\n");
	if ((argc<1) ||(strcmp(argv[0], "help")==0)) {
		printf("(callback)\n");
		//printf("help\n");
		printf("cli_button_select\n");
		return NULL;
	}

	//cli_button_select

	// 1 argv(dump)
	if (argc==1) {
		//---------------- dump
		if (strcmp(argv[0], "cli_button_select")==0) {	printf("[%s]\n", argv[0]); 	return cli_button_ping;	}
	} // end(argc==1)

	return NULL;
}
