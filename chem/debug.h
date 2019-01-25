/*
 * debug.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#ifdef LOG
#undef LOG
#endif

#ifndef PRINT
#define PRINT printf("::%s.", __PRETTY_FUNCTION__); printf
#endif

#ifdef DEBUG
#define LOG PRINT
#else
#define LOG if (false) printf
#endif



//--------------------------
#ifndef DEBUG_H_
#define DEBUG_H_

#define NL printf("\n");
#define DUMP(p); if (p==NULL) printf("<NULL>"); else p-> dump();
//--------------------------
#endif /* DEBUG_H_ */
