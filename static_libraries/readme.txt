first compiled to object files addvec.c and multvec.c
used command: 
>> gcc -c addvec.c multvec.c
creates addvec.o and multvec.o

create a library (archive format) from those two object
files using the following command
>> ar rcs libvector.a addvec.o multvec.o

create a header file that defines the function protypes
in libvector.a (call it vector.h)

compile main.c that uses only 1 of the functions from libvector.a
>> gcc -c main.c
this creats main.o

Now we need to link main.o with only the addvec.o symbol from libvector.a
>> gcc main.o libvector.a

OPTIONAL
The -static argument tells the compiler that the linker should build a fully
linked executable object file that can be loaded and run without further
linking at load time

