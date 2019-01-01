/*
 * common.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */


#ifdef LOG
#undef LOG
#endif

#ifdef DEBUG
#define LOG printf("##-- %s.", __PRETTY_FUNCTION__); printf
#else
#define LOG if (false) printf
#endif




#define NL printf("\n");
//#define LOGGER(p) printf("$:%s.", __PRETTY_FUNCTION__); printf(p); printf("\n");


//#define LOG(p) printf("##-- %s.", __PRETTY_FUNCTION__); printf(p); printf("\n");
//#else
//#define LOG(p) void(0); // p
//#endif

void sprintb(char *str, char val, char zero);
void sprintb(char *str, char val);
void printb(char val);
