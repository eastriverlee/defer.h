#ifndef DEFER_H
#define DEFER_H
#include <stdlib.h>
#include "array.h"

typedef void(*fn_t)(void*);
typedef void* pointer;

#define DEFERRABLE              \
declare_array(fn_t);            \
declare_array(pointer);         \
Ifn_tI deferred;                \
IpointerI deferred_parameter;   \
II__init(deferred, NULL);       \
II__init(deferred_parameter, NULL);

#define RETURN(result)                                                                  \
do {                                                                                    \
	const typeof(result) RESULT = result;                                               \
	size_t deferred_count = deferred.length;                                            \
	while (deferred_count)                                                              \
	{                                                                                   \
		deferred_count--;                                                               \
		deferred.elements[deferred_count](deferred_parameter.elements[deferred_count]); \
	}                                                                                   \
	II__free(deferred);                                                                 \
	II__free(deferred_parameter);                                                       \
	return RESULT;                                                                      \
} while(0)

#define defer(fn, parameter)                          \
do {                                                  \
	II__append(deferred, (fn_t)fn);                   \
	II__append(deferred_parameter, parameter);        \
} while(0)

#endif
