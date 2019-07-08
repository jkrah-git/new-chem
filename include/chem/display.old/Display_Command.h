/*
 * Display_Command.h
 *
 *  Created on: Jun 30, 2019
 *      Author: jkrah
 */

#ifndef DISPLAY_COMMAND_H_
#define DISPLAY_COMMAND_H_
class ChemDisplay;
#define DISPLAY_COMMAND_MAX_NAME 	32

class Display_Command {
public:
	int 	(*operation)(ChemDisplay*, int, char**);
	int		(*callback)(ChemDisplay*, int, char**);
	char 	name[DISPLAY_COMMAND_MAX_NAME];
	//-----

public:
	Display_Command();
	virtual ~Display_Command();
	void	dump(void);
};

#endif /* DISPLAY_COMMAND_H_ */
