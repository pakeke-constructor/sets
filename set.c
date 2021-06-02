
#include "set.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define GROW_RATIO 4 // for every item in hash, there are 4 buckets
#define START_SIZE 13

#define unlikely(x)    (__builtin_expect(!!(x), 0))



static inline int hashfn(void *key){
    return (int)key / 16;
}



static short grow(set *s){
    // grows a set by twice size
    // returns 1 on failure

    s->memsize *= 2;

    free(s->buckets);
    s->buckets = malloc(s->memsize * sizeof(_set_bucket));
    if unlikely(!s->buckets){
        return 1;
    }
    for (int i=0; i < s->memsize; i++){
        s->buckets[i].key = NULL;
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
    if ((s->nitems + 1) > (s->memsize / GROW_RATIO)){
        // then grow the set
        short failed = grow(s);
        if unlikely(failed){
            return 1;
        }
    };

    s->ptrs[s->nitems] = ptr;
    s->nitems++;

    int i = hashfn(ptr) % s->memsize;
    int ctr = 0;

    while (s->buckets[i].key){ // quadratic bucket probe
        i = (i + (ctr * ctr)) % s->memsize;
        ctr += 1;
    }

    s->buckets[i].index = s->nitems;
    s->buckets[i].key = ptr;
    return 0;
}



set *set_new(void){
    // initial size of 13 (nice and prime-y)
    set *ret = malloc(sizeof ret);
    if (unlikely(!ret)){
        return NULL; // failed
    }

    ret->memsize = START_SIZE * GROW_RATIO;
    ret->buckets = malloc(ret->memsize * sizeof(void*));
    ret->ptrs = malloc(START_SIZE * sizeof(_set_bucket));
    ret->nitems = 0;

    for (int i=0; i < ret->memsize; i++){
        ret->buckets[i].key = NULL; // initialize all ptrs to NULL
    }

    if unlikely((!ret->buckets) || (!ret->ptrs)){
        free(ret->buckets);
        free(ret->ptrs);
        free(ret);
        return NULL; // also failed
    }

    return ret;
}


short set_has(set *s, void *ptr){
    int i = hashfn(ptr) % s->memsize;
    int ctr = 0;

    while (s->buckets[i].key != ptr){ // quadratic bucket probe
        if (!s->buckets[i].key){
            // if key ptr is null, return 0; unfound.
            return 0;
        }
        i = (i + (ctr * ctr)) % s->memsize;
        ctr += 1;
    }

    if(!s->buckets[i].key){
        return 0;
    }else{
        return 1;
    }
}



void set_remove(set *s, void *ptr){
    int i = hashfn(ptr) % s->memsize;
    int ctr = 0;
    
    while (s->buckets[i].key != ptr){
        if (!s->buckets[i].key){
            // ptr is not in the set
            // because data[i].key is NULL
            return;
        }
        i = ((i + (ctr * ctr)) % s->memsize);
        ctr += 1;
    }

    int index = s->buckets[i].index;
    _set_bucket *end = s->ptrs[s->nitems-1];
    s->ptrs[index] = end; // put last item in slot of other
    end->index = index;
    s->nitems--;

    s->buckets[i].key = NULL;
}



void set_free(set *s){
    free(s->buckets);
    free(s->ptrs);
    free(s);
}


void set_clear(set *s){
    free(s->buckets);
    free(s->ptrs);

    s->memsize = START_SIZE * GROW_RATIO;
    s->buckets = malloc(s->memsize * sizeof(void *));
    s->ptrs = malloc(START_SIZE * sizeof(_set_bucket));
    s->nitems = 0;
}

