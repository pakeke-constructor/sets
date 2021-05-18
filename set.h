

// do NOT instantiate these structs directly, with malloc or anything!
// use `set_new()`.
typedef struct {
    int index;
    void *key;
} _set_bucket;

// Do not instantiate this directly, use `set_new()`.
typedef struct {
    _set_bucket *buckets;
    void **ptrs;
    unsigned int memsize; 
    unsigned int nitems;
} set;





short set_add(set *s, void *ptr);
void set_remove(set *s, void *ptr);
short set_has(set *s, void *ptr);

void set_clear(set *s);
void set_free(set *s);

set *set_new(void);


#define set_FORJ(sett, T) \
T *jptr;                          \
for(int j=0; j < (sett).n_items; j++, jptr = (T*) (sett).ptrs[j])


#define set_FORI(sett, T) \
T *iptr;                       \
for(int i=0; i < (sett).n_items; i++, iptr = (T*) (sett).ptrs[i])




