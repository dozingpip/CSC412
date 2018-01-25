/*--------------------------------------------------------------+
|		A simple C program to demonstrate some basic elements	|
|	of the language to Java programmers.						|
|																|
|	Jean-Yves Hervé, 3DG URI									|
|	2017-09-13, nodified 2018-01-23								|
+--------------------------------------------------------------*/

//	This plays a role kinda somewhat not competely
//	unlike (but still fairly different from) the Java "import" statement
//	you are familiar with
#include <stdio.h>

//	Compare the "parameter signature" of a C program's main function to that of the
//	main method of a Java application.
//	Java Reminder:  int main(String[] arg) {...}
//	The parameters of the main function are in fact the name of the executable
//	and the arguments passed to the program when it is launched from the console.
int main(int argc, const char * argv[]) {

	//	The next code sample will dive into formatted output.  Right now, I am
	//	just illustrating the fact that we can get and print the arguments passed
	//	when the program was launched from the command line.
	printf("Hello, World!\n");
	
	//	Here the %d is a formating instruction.  It says that an integer should be included
	//	in the output string about there.  So, the first (and only) parameter in the list
	//	following the format string, argc, is to be interpreted as an int.
	printf("argc = %d\n", argc);
	
	//	Here, argv[0] is to be interpreted as a C-style string.  This is what %s means
	printf("name of the executable: %s\n", argv[0]);
	
	for (int k=1; k<argc; k++)
		//	Here I print the first parameter, k as an int and the second, argv[k],
		//	as a C-style string.
		printf("\targument %d: %s\n", k, argv[k]);
	
	printf("Bye.\n\n");
    return 0;
}
