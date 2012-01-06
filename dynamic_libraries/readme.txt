Dynamic Libraries (aka shared libraries)
1- ADV: the executable doesn't need to be recompiled when the 
library is updated (unlike the case of a static library, where 
the used library code gets copied to the executable, and hence, 
any updates require recompiling the exec)
2- ADV: avoids duplicating code (like printf, scanf) in processes.
Instead, they share the code.


create a shared library (with .so extension on Unix):
>> gcc -shared -fPIC -o libvector.so addvec.c multvec.c

then there are 2 ways to use a shared library:

1- Link it at compile time, and the library gets loaded right before the
program executes (at load time, which is technically runtime)

2- Use the library symbols during program execution (in your code) without
linking during compile time.

Dynamic linker is program (actually a shared library itself) that
does the linking at runtime


1>> gcc main.c libvector.so

2>> gcc dll.c
