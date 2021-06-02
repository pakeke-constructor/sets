
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int *i = malloc(sizeof(int));
    *i=70;

    printf("HELLO??? START TESTS\n");
    set *s = set_new();

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
    if (!set_has(s, i)){
        printf("nice 3\n");
    }
    printf("after if\n");
    set_free(s);
    printf("END TESTS\n");
}

