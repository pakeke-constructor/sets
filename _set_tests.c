
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    set *s = set_new();

    int *i = malloc(sizeof(*i));
    *i=70;

    set_add(s, i);
    if (set_has(s, i)){
        printf("nice 1\n");
    }
    set_remove(s, i);
    set_remove(s, i);
    if (!set_has(s, i)){
        printf("nice 2\n");
    }

    set_add(s, i);
    printf("done add\n");
    set_clear(s);

    printf("before if\n");
    fflush(stdout);
    if (!set_has(s, i)){
        printf("nice 3\n");
        fflush(stdout);
    }
    printf("after if\n");
    fflush(stdout);
    set_free(s);
}

