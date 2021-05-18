
#include "set.h"
#include <math.h>
#include <stdlib.h>

#define GROW_RATIO 0.25f
#define START_SIZE 13

#define unlikely(x)    (__builtin_expect(!!(x), 0))



static inline int hashfn(void *key){
    return (int)key / 16;
};

static short grow(set *s){
    // grows a set by twice size
    // returns 1 on failure

    s->memsize *= 2;

    free(s->data);
    s->data = malloc(s->memsize * sizeof(_set_bucket));
    if unlikely(!s->data){
        return 1;
    }
    for (int i=0; i < s->memsize; i++){
        s->data[i].bool_taken = 1;
    }

    s->ptrs = realloc(s->ptrs, sizeof(void*) * (s->nitems + 1) * 2); // add 1 to be safe 
    if unlikely(!s->ptrs){
        return 1;
    }

    for (int i=0; i < s->nitems; i++){
        set_add(s, s->ptrs[i]);
    }
    return 0;
}



short set_add(set *s, void *ptr){
    _set_bucket buck = {
        .index = s->nitems + 1,
        .key = ptr,
        .bool_taken = (char)1
    };

    if ((s->nitems + 1) > (s->memsize * GROW_RATIO)){
        // then grow the set
        short failed = grow(s);
        if unlikely(failed){
            return 1;
        }
    };

    s->ptrs[s->nitems] = ptr;
    s->nitems++;

    int i = hashfn(ptr) % s->memsize;
    int ctr = 1;

    while (s->data[i].bool_taken){ // quadratic bucket probe
        i = (i + (ctr * ctr)) % s->memsize;
        ctr += 1;
    }

    s->data[i] = buck;
    return 0;
}



set *set_new(void){
    // initial size of 13 (nice and prime-y)
    set *ret = malloc(sizeof ret);
    if (unlikely(!ret)){
        return NULL; // failed
    }

    ret->memsize = START_SIZE;
    ret->data = malloc(ret->memsize * sizeof(void *));
    ret->ptrs = malloc((START_SIZE/4) * sizeof(_set_bucket));
    ret->nitems = 0;

    if unlikely((!ret->data) || (!ret->ptrs)){
        free(ret->data);
        free(ret->ptrs);
        free(ret);
        return NULL; // also failed
    }

    return ret;
}


short set_has(set *s, void *ptr){
    int i = hashfn(ptr) % s->memsize;
    int ctr = 1;

    int ret;

    while (s->data[i].key != ptr){ // quadratic bucket probe
        if (!s->data[i].bool_taken){
            return 0;
        }
        i = (i + (ctr * ctr)) % s->memsize;
        ctr += 1;
    }

    if(!s->data[i].bool_taken){
        return 0;
    }else{
        return 1;
    }
}



void set_remove(set *s, void *ptr){
    int i = hashfn(ptr) % s->memsize;
    int ctr = 1;
    
    while (s->data[i].key != ptr){
        if (!s->data[i].bool_taken){
            // ptr is not in the set
            return;
        }
        i = (i + (ctr * ctr)) % s->memsize;
        ctr += 1;
    }

    int index = s->data[i].index;
    s->ptrs[index] = s->ptrs[s->nitems-1]; // put last item in slot of other
    s->nitems--;

    s->data[i].bool_taken = (char)0;
}



void set_free(set *s){
    free(s->data);
    free(s->ptrs);
    free(s);
}


void set_clear(set *s){
    set_free(s);

    s->memsize = START_SIZE;
    s->data = malloc(s->memsize * sizeof(void *));
    s->ptrs = malloc((START_SIZE/4) * sizeof(_set_bucket));
    s->nitems = 0;
}
