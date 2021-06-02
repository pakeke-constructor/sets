


### Bugs:
- heap corruption somewhere (use Dr Memory or valgrind)
- Need to add a tombstone bucket upon hashtable removal (Else chaining gets
    messed up when an item is removed.)

### TODO:
- Maybe reduce grow threshold
- check for mem leaks
- add a hash collision counter 



# sparse sets in c

This is my sparse set implementation.
It's heavily untested and may have memory leaks and bugs.


however, it should have (amortized) O(1) removal, addition, as well
as a nice iteration macro. The hasher uses quadratic probing, and allocates 4*n space
for every n pointers added to the data structure (may change it to 3*n in the future,
4 times could be a bit overkill.)


Also, sets will automatically reallocate their own space in an efficient manner
