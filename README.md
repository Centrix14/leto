![](images/leto_128px.png)

Leto is a library for developing modular and stable software in C language

# How it works?

The library is currently under development and will include:
+ `DONE` **leto-list** — Singly Linked List Library
+ `DONE` **leto-error** — Error and warning handling library
+ `DONE` **leto-test** — Library for simple unit testing
+ `DONE` **leto-so** — Library for working with dynamic libraries
+ `DONE` **leto-type** — Miniature type library
+ `DONE` **leto-utsf** — Data transfer and storage library

# How to use it?

How you use the library is up to you, but I recommend statically
linking it to your program.  
If you follow the instructions in "How to compile it?" then adding the
library to your application is trivial.
1. Include the heading `leto.h` in the right places
2. Add libleto.a to the compilation files (or copy it to the directory
   where the compiler stores the libraries and use the -lleto flag)

## Where can I find code examples?
You can find code examples in the tests. Just look into the directory of
the module you need (for example, leto-list) and open the test.c file

# How to compile it?

To compile you will need a compiler with C11 support and the dl
library.  
To compile use:

``` shell
make build
```

After that, the `libleto.a` file will appear in the directory.  
In addition, you can run tests:

``` shell
make test
```

# Where can I find documentation?
The documentation can be generated using the following script:

``` shell
make docs
```

ALso, you can visit our [website](https://centrix14.github.io/leto)
where documentation is posted.

