
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    set *s = set_new();

    int *i = malloc(sizeof(*i));
    *i=70;

    set_add(s, i);
    if (set_has(s, i)){
        printf("nice :)");
    }
    set_remove(s, i);
    set_remove(s,i);
    if (!set_has(s, i)){
        printf("nice :)");
    }

}

