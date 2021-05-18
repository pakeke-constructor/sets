# sparse sets in c

This is my sparse set implementation.
It's heavily untested and may have memory leaks and bugs.


however, it should have (amortized) O(1) removal, addition, as well
as nice iteration macros. The hasher uses quadratic probing, and allocates 4*n space
for every n pointers added to the data structure (may change it to 3*n in the future,
4 times could be a bit overkill.)


Also, sets will automatically reallocate their own space in an efficient manner

### Bugs:
- heap corruption somewhere (use Dr Memory or valgrind)

### TODO:
- Maybe reduce grow threshold
- check for mem leaks
- add a hash collision counter 
