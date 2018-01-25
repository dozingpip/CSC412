/*--------------------------------------------------------------+
|		A simple C program to demonstrate some basic elements	|
|	of the language to Java programmers.						|
|																|
|	Jean-Yves Hervé, 3DG URI									|
|	2016-02-01.  revised 2018-01-23								|
+--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		//	guess what this one does?
//
//	The previous headers were called "system" headers because they are part of the
//	development environment.  This includes all basic C headers, but also headers
//	of any third-party library you may be using in your code.  The header
//	that we load below is a "user" header.  It is one of your own header files.
//	You indicate that by using double quote signs around the name.  Normally,
//	the C compiler will search for this header file within your project folder.
#include "otherFile.h"


//	In C, you must declare a function before you call it.  This is what we call the
//	prototype.  In fact, you don't need to give the name of the variable.
//	I write the name of the variable because this allows me to use javadoc-style
//	comments to produce documentation for my code through Doxygen.
int getFibNum(int n);	//	could have been    int getFibNum(int);
void printFib(int num);
void getOrd(int num, char* ord);

//	At this point, take it the way you did the void main(String[] s) in Java
//	before you knew what [] meant.  It has to be there and we will explain
//	it later
int main (int argc, const char* argv[]) {

	//----------------------------------------------------------
	//	Part 1
	//	Strings and arrays of char
	//----------------------------------------------------------
	printf("Part 1\n----------------\n");
	
	//	In C, a string is nothing more than an array of char.  The important
	//	thing about C strings is that they are "0-terminated."  In other words,
	//	the string is considered to extend up to the first byte with value 0 that
	//	it encounters.
	char s[] = "ABCDEFGHI";
	
	printf("Point 1\n");

	//	Even though s only counts 9 characters, the array that stores it is 10 char long,
	//	and the last char has value 0 (note that value 0 is not the same as character '0',
	//	which has the value 48
	//	Note that contrary to a regular array, you can ask for the length of a string, because
	//	of that 0-valued terminator
	unsigned long ls = strlen(s);
	printf("s is %ld characters long.  These characters are\n", ls);
	for (int k=0; k<ls; k++)
		printf("s[%d] = \'%c\', ASCII code %d\n", k, s[k], s[k]);
	printf("and s[%ld] = ASCII code %d\n\n", ls, s[ls]);
	
	printf("Seen as a string, s stores -->%s<--\n\n", s);
	
	//	Setting (accidentally) one of the characters in the middle of the array
	//	to the value 0 (rather than, say, to the character '0') will "cut" the
	//	string
	s[5] = 0;   // oops, I meant to write s[5] = '0';
	s[6] = '1';
	
	printf("Point 2\nSeen as a string, s now stores -->%s<--\n", s);
	printf("s is %ld characters long, but the characters in the array are\n", strlen(s));
	for (int k=0; k<ls; k++)
		printf("s[%d] = \'%c\', ASCII code %d\n", k, s[k], s[k]);
	printf("and s[%ld] = ASCII code %d\n\n", ls, s[ls]);
	
	//	Changing the value of the zero-terminating character of a string can have
	//	disastrous effects because your string could then become thousands of characters long
	//	(extends until a byte with the value 0 is encountered).


	//----------------------------------------------------------
	//	Part 2
	//	Some basic string manipulation
	//----------------------------------------------------------
	printf("Part 2\n----------------\n");

	for (int i = 1; i< 20; i++)
		printf("fib(%d) = %d\n", i, getFibNum(i));
	
	for (int i = 1; i< 40; i++)
		printFib(i);
	
	
	//----------------------------------------------------------
	//	Part 3
	//	More string manipulation
	//----------------------------------------------------------
	printf("\nPart 3\n----------------\n");

	//	We have already see strcpy in Part 2.  So now, how to extract a substring?
	//	string.h doesn't define a substring function.  So, instead, you need to
	//	do a partial copy.
	char a[] = "ABCDEFGHIJK";
	
	//	do the equivalent of what in Java would be b = a.substring(3, 8);
	//	that is, extracting from a the characters as indices 3, 4, 5, 6, 7
	//	a substring of 8-3 = 5 characters

	//	my destination string.  B has size 6 because of the extra character
	//	to store the terminating 0
	char b[6];
	//	So, copy into the array stored in b the substring starting 3 characters
	//	after the beginning of a, and extending for 5 characters.
	//	This also adds the terminating 0;
	strncpy(b, a+3, 5);
	printf("a = -->%s<-- and has length %ld\n", a, strlen(a));
	printf("b = -->%s<-- and has length %ld\n", b, strlen(b));
	
	//	note that I could copy into an oversized array and that I would still
	//	get the right substring, because the terminating 0 is written at the right place.
	//	the *array* still has 10 characters, even if the string it stores only has 5
	char c[10];
	strncpy(c, a+3, 5);
	printf("c = -->%s<-- and has length %ld\n\n", c, strlen(c));

	//	You can also do string concatenation.  But be careful that the function
	//	does not create a new array of char.  It produces the concatenation inside
	//	an existing one.  So the destination array must be large enough to
	//	accommodate the final string.
	char d[] = "12345678";
	char dest[25];
	//	1. copy a into dest
	strcpy(dest, a);
	//  2. now concatenate d the end of dest
	strcat(dest, d);
	printf("dest = -->%s<-- and has length %ld\n\n", dest, strlen(dest));
	
	
	//----------------------------------------------------------
	//	Part 4
	//	This one is just to use the function defined in that external source file
	//----------------------------------------------------------
	printf("\nPart 4\n----------------\n");
	double y = 3.141592654L;
	double z = myFunc(y);
	printf("myFunc(%lf) = %lf\n\n", y, z);
	

	//----------------------------------------------------------
	//	Part 5
	//	Last, but definitely not least part:  How to convert
	//  the string "1234" into the number 1234.
	//----------------------------------------------------------
	printf("\nPart 5\n----------------\n");
	
	//	If you remember, the program gets its arguments as a list of C-style strings,
	//	in the argv array.  You will need to convert these to whatever you were
	//	expecting to get.
	//	Here, I work from hard-coded C strings
	
	//	The C function to use is sscanf.  It is declared in the <stdio.h> header
	//		int sscanf ( const char * s, const char * format, ...);
	//	It attempts to read values from the string using a classical C I/O format.
	
	char s1[] = "1234";
	int val1;
	sscanf(s1, "%d", &val1);
	printf("The value read from the string \'%s\' is val1 = %d, and 2*val1 = %d\n", s1, val1, (2*val1));
	
	//	Because the function uses a C I/O format, you can work with fancier strings
	char s2[] = "x = 23, y = 67";
	int val21, val22;
	sscanf(s2, "x = %d, y = %d", &val21, &val22);
	printf("The values read from the string \'%s\' are val1 = %d, and val2 = %d\n", s2, val21, val22);

	//	Be careful, though, because if you mess up the format, your reading will fail
	char s3[] = "x = 23; y = 67";
	//                 ^____ note the ; instead of ,
	int val31, val32;
	sscanf(s3, "x = %d, y = %d", &val31, &val32);
	printf("The values read from the string \'%s\' are val1 = %d, and val2 = %d\n", s3, val31, val32);

	//	This is where you want to use the value returned by the function scanf, which is the
	//	number of values successfully read.
	int nbValsRead = -1;
	
	//	So, let's return to s2
	nbValsRead = sscanf(s2, "x = %d, y = %d", &val21, &val22);
	if (nbValsRead == 2)
		printf("The values read from the string \'%s\' are val1 = %d, and val2 = %d\n", s2, val21, val22);
	else
		printf("Reading formatted data from \'%s\' failed.  Could only read: %d\n", s2, nbValsRead);

	//	and then to s3
	nbValsRead = sscanf(s3, "x = %d, y = %d", &val31, &val32);
	if (nbValsRead == 2)
		printf("The values read from the string \'%s\' are val1 = %d, and val2 = %d\n", s3, val31, val32);
	else
		printf("Reading formatted data from \'%s\' failed.  Could only read: %d\n", s3, nbValsRead);

	//	Be careful that you will need to to some clever things on your own to do checking between
	//	numerical types, though.
	char s5[] = "-12.34";

	//	First, I read this string as a float and it works well
	float val51;
	nbValsRead = sscanf(s5, "%f", &val51);
	if (nbValsRead == 1)
		printf("Successfully read a float value from the string \'%s\' --> val = %f\n", s5, val51);
	else
		printf("Couldn't read a float value from the string \'%s\'\n", s5);

	//	Next, I try to read it as an int, and it also works, because it still agrees with the format
	int val52;
	nbValsRead = sscanf(s5, "%d", &val52);
	if (nbValsRead == 1)
		printf("Successfully read an int value from the string \'%s\' --> val = %d\n", s5, val52);
	else
		printf("Couldn't read an int value from the string \'%s\'\n", s5);


	return 0;
}


void printFib(int num){

	//	This is the array in which I will store the appropriate ordinal suffix
	//	for num.  All these suffixes are 2-character long, so the array needs
	//	 a size of three, for the terminating 0;
	char ord[3];

	getOrd(num, ord);
	
	int fib = getFibNum(num);
	printf("The %d%s Fibonacci number is %d.\n",num, ord, fib);

//	printf("Address %p contains %s.\n", ord, ord);
}



/* This function compute the proper ordinal suffix for a given number.
 * With the exception of numbers ending in 11, 12 or 13, numbers ending in 1 have the
 * ordinal suffix "st," numbers ending in 2 have the ordinal suffix "nd," numbers ending
 * in 3 have the ordinal suffix "rd" and all the rest end in "th."
 */
void getOrd(int num, char* ord){

	int hundredRemainder = num % 100;
	int tenRemainder = num % 10;
	
	switch (hundredRemainder) {
	
		case 11:
		case 12:
		case 13:
			strcpy(ord, "th");
			break;
			
		default:
			switch(tenRemainder){ 
				case 1:
					strcpy(ord, "st");
					break;
				case 2:
					strcpy(ord, "nd");
					break;
				case 3:
					strcpy(ord, "rd");
					break;
				default:
					strcpy(ord, "th");
					break;
			}
			break;
	}
}


//	Computes the num-th Fibonacci number.
int getFibNum(int num) {

	if (num <= 0)
		return 0;
	else {
		int m = 0;
		int n = 1;
		int p = 0;
		for (int i=2; i<=num; i++) {
			p = m + n;
			m = n;
			n = p;
		}
		return p;
	}
}
