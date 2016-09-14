/*
 * common.h
 *
 *  Created on: 2016年9月13日
 *      Author: Bill
 */

#ifndef COMMON_H_
#define COMMON_H_

//#include <malloc.h>
#include <sys/malloc.h>

#ifdef _WIN32 // note the underscore: without it, it's not msdn official! 
#include <malloc.h> 
#elif __unix__ // all unices 
#include <malloc.h>
#elif __posix__ 
#include <malloc.h>
#elif __linux__ 
#include <malloc.h>
#elif __APPLE__ 
#include <sys/malloc.h>
#endif

#ifndef NULL
#define NULL 0
#endif

#endif /* COMMON_H_ */
