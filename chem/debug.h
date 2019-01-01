/*
 * debug.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#ifdef LOG
#undef LOG
#endif

#ifdef DEBUG
#define LOG printf("::%s.", __PRETTY_FUNCTION__); printf
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
