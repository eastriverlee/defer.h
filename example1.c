#include "defer.h"

#include <stdio.h>
#include <string.h>

void free_(void* malloced)
{
	puts("freeing");
	free(malloced);
}

void when_will_I_execute(void* _)
{
	puts("pick-a-boo");
}

int main()
{ DEFERRABLE

	char* message = strdup("hello world");
	defer(free_, message);
	defer(when_will_I_execute, NULL);
	puts(message);

	RETURN (puts("bye world"));
}
