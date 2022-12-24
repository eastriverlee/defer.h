#include "defer.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    char* first;
    char* second;
} two_words;

void free_two_words(two_words* words)
{
    free(words->first);
    free(words->second);
    puts("freed two words");
}

int main()
{ DEFERRABLE
    two_words words;

    words.first = strdup("hello");
    words.second = strdup("words");
    defer(free_two_words, &words);
    RETURN (printf("%s %s\n", words.first, words.second));
}
