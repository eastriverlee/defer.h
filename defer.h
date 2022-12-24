#ifndef DEFER_H
#define DEFER_H
#include <stdlib.h>

#define MAX_DEFER_COUNT 32

typedef void(*fn_t)(void*);

#define DEFERRABLE                         \
fn_t deferred[MAX_DEFER_COUNT];            \
void* deferred_parameter[MAX_DEFER_COUNT]; \
unsigned char deferred_count = 0;

#define RETURN(result)                                                \
do {                                                                  \
	const typeof(result) RESULT = result;                             \
	while (deferred_count)                                            \
	{                                                                 \
		deferred_count--;                                             \
		deferred[deferred_count](deferred_parameter[deferred_count]); \
	}                                                                 \
	return RESULT;                                                    \
} while(0)

#define defer(fn, parameter)                          \
do {                                                  \
	deferred[deferred_count] = (fn_t)fn;              \
	deferred_parameter[deferred_count++] = parameter; \
} while(0)

/*
**  if you prefer functions over macros...
**
**  void defer(fn_t fn, void* parameter)
**  {
**  	deferred[deferred_count] = fn;
**  	deferred_parameter[deferred_count++] = parameter;
**  }
*/

#endif
