

// do NOT instantiate these structs directly, with malloc or anything!
// use `set_new()`.
typedef struct {
    int index;
    void *key;
} _set_bucket;

// Do not instantiate this directly, use `set_new()`.
typedef struct {
    _set_bucket *buckets;
    // list of void*
    void **ptrs;
    // number of buckets available
    unsigned int memsize; 
    // number of items in set
    unsigned int nitems;
} set;





short set_add(set *s, void *ptr);
void set_remove(set *s, void *ptr);
short set_has(set *s, void *ptr);

void set_clear(set *s);
void set_free(set *s);

set *set_new(void);


#define set_FOR(sett, T, obj_name, ctr_name) \
T * obj_name;                                       \
for(int ctr_name=0; ctr_name < (sett).n_items; ctr_name++, obj_name = (T*) (sett).ptrs[ctr_name])


