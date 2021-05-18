

typedef struct {
    int index;
    void *key;
    char bool_taken;
} _set_bucket;

typedef struct {
    _set_bucket *data;
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


#define FORSETi(sett) \
void * iptr;                 \
for(int i=0; i < (sett).n_items; i++, iptr = (sett).ptrs[i])


#define FORSETj(sett) \
void * jptr;                 \
for(int j=0; j < (sett).n_items; j++, jptr = (sett).ptrs[j])


