#==============================================================================#
#  Let's move beyond typing build commands at the command line:  The make file #
#==============================================================================#

Part I: Build a project with multiple source files and a library
-----------------------------------------------------------------

This project is a bit more complex than the previous ones because we have more file.
(the code also has some new stuff, but this READ_ME file concentrates on the
building aspect.

Besides the source file containing the main function, we have an additional
source file and the header that gives the prototype of its single function.

This is no big deal, we can ask gcc to compile the different source files
and combine them (this is the job of the "linker" to produce the executable.

gcc main.c otherFile.c -o myProg

We can, but if you do that you will get an error message and the build will 
fail.  The build error should be:

        random characters here 
       /----\
/tmp/ccXXXXXX.o  in function 'myFunc':
otherFile.c (.text+0x1b): undefined reference to 'cos'
collect2: error: ld returned 1 exit status

Agreed, this is not the clearest error message.  You could believe that the problem is
that the *compiler* doesn't know about 'cos', even though we load the header 'math.h'.
This is, however, not the case.  To verify that, in otherFile.c comment out the line

#include <math.h> 

and try again to build the program.  This time the error message is a compiler error.
You get a line number where the error occurs (the line where the call to cos() takes
place.  And here you actually get a valid recommendation as to the solution.  This is
because the compiler "knows" about cos() anyway, even if it pretends not to.  It
just takes a snarky, annoying tone to tell you that it knows perfectly well what you are
trying to do, but won't do it unless you #include <math.h>.

So, you remove the comment out, and we are back to the original problem.  
So, what is the error we are encountering?

The key to what is going on is here
                                |
                 +--------------+
                 |
                 V
collect2: error: ld returned 1 exit status

This tells you that this is an error happening in the linker, when it tries to load
the different pieces to object code to build the executable: The linker does not
find object code for 'cos'

This is a fundamental difference with an 'import <whatever>' statement in Java, which
is a one-stop solution to letting the compiler know about what pieces to use to build
the application.  If you look at your own header file otherFile.h, you can see that it
contains no code, only the declaration.  The same is true of the system headers
stdio.h, stdlib.h, and, then, math.h

The header file just tells to the compiler "trust me, there does exist a function 
named 'cos' that takes a double as parameter and return a double value.  Trust me
that it exists and that you will encounter it sooner or later."  The compiler makes
a note of that and creates a symbol for this 'cos' function.

The same thing happens when you #include the header 'otherFile.h'  That header tells
the compiler about a function named myFunc that also takes a double as parameter and 
return a double value.  The compiler notes that, creates a symbol for myFunc, and 
does not create an error when it encounters a call to myFunc later in the main
function (it just verifies that the syntax of the call agrees with the declaration.

When, later, the compiler processes otherFile.c (it does so because we ask for it
in our gcc command), it finds the code of myFunc and goes "ah ha! [or the equivalent
in compiler-speak], now I have code to match that myFunc label in my symbol tables!"
So that when the linker loads the object file for the main, main.o and the object file
otherFile.o, the object code for myFunc is properly associated to the label in the
symbol table.

The problem is that the object code for 'cos' is not loaded in the same fashion.
Why is the object code for 'cos' not loaded, but that for 'printf' and 'calloc' is,
you ask?  Because the object code for the basic functions in stdio.h, stdlib.h, 
string.h, etc. is loaded by default, but the object code for all the other functions, 
and in particular math functions, has to be loaded explicitly.

The gcc option for loading a specific library is   -l<library>
where <library> is the name of the library.
The name of the math library is  m  (I am not kidding, ridiculous as it sounds, and is),
so the option to add will be  -lm

The full command is now 

gcc main.c otherFile.c -lm -o myProg

and it should succeed in building the executable, that you can now build in the 
usual way.


Part II: Further precisions on the gcc command
------------------------------------------------

I should mention that the order of *some* of the options is arbitrary.  So, we could
as well have written

gcc -o myProg  main.c otherFile.c  -lm

On the other hand, I cannot do -lm *before* compiling otherFile.c because if the m(ath)
library is loaded first, then none of its symbols are yet listed in the 'need code for
this' symbol table.
This brings up another common issue:  The order in which you load libraries does matter,
in the case that different libraries have symbols (functions) with the same name.  The 
first one loaded is the one that will be used by the linker.

Commonly, to help the compiler locate the user header files, programmers add the
-r option to their gcc command, to say that the search should proceed in the current
./ directory.  Note that this only works if you launch the gcc command from within
the folder where the header files are.


Part III: Basic make file
---------------------------

Now, I am sure that you can envision a situation where you are going to have a bunch of
source files that must be compiled using multiple libraries, some of them third-party
libraries, and the gcc command is going to become really complicated.

This is where the make file comes into play.

make is a command that reads configuration information from a text file to build
complex projects.

So, create a file named makefile or Makefile (no extension)
In that file, type the following

myProg: main.c  otherFile.c
	gcc main.c otherFile.c -lm -o myProg
	
save the file in the same folder as your source code and header and now
enter the command

make

Just like that.  No parameters.  This is going to build your executable as before.
The good news is that you won't have anymore to enter a complex gcc command.  All you
have to do is edit the makefile to reflect additions and changes in your project.

If we look at what the makeFile says, we can see that the second line is just the
usual gcc command.  What about the first line?  It is telling make that the project
only needs to be rebuilt if  main.c or otherFile.c has been modified.  
Try to run the make command again and see by yourself.


Part IV: More advanced make
----------------------------
What we have created is only a very basic make file.  There are lots of powerful options
that let you specify folders where to look for headers and source files, options for
the compiler, and many more things.  There are a number of very good tutorials on 
make and make files.  One such tutorial is at this URL:
http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
but there are many more out there. Consult them if you need to access more powerful 
options and configurations.



