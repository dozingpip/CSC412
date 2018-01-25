/*
 *  main.c
 *  C Input-Output
 *
 *  Created by jean-yves hervé on 2009/02/09.
 *	Revised 2016-01-31, 2017-02-11, 2018-01-24
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>		//	for C string manipulation (strcpy, strcat)
//
#include "dataTypes.h"
#include "asciiIO.h"
#include "binaryIO.h"

// Here I hard code my file paths.  Replace if you want a different organization
#define INPUT_ROOT_PATH "./Data/"
#define OUTPUT_ROOT_PATH "./Output/"

void consoleIO(void);


int main (int argc, const char * argv[]) {

	//----------------------------------------------------
	//	Part I:    Console I/O
	//----------------------------------------------------
	consoleIO();

	//----------------------------------------------------
	//	Part II:   I/O from and to a *text* file (ASCII)
	//----------------------------------------------------
	
	//	I build the paths to my input and output files

	char inputFilePath1[256], inputFilePath2[256], asciiOutputFilePath[256],
		 binaryOutputFilePath1[256], binaryOutputFilePath2[256];

	//	copy the root path
	strcpy(inputFilePath1, INPUT_ROOT_PATH);
	//	and then append the name of the file I expect to find in that folder
	strcat(inputFilePath1, "simpleAsciiData.txt");
	
	//	rince and repeat
	strcpy(inputFilePath2, INPUT_ROOT_PATH);
	strcat(inputFilePath2, "fancierAsciiData.txt");
	strcpy(asciiOutputFilePath, OUTPUT_ROOT_PATH);
	strcat(asciiOutputFilePath, "asciiDataOut.txt");
	strcpy(binaryOutputFilePath1, OUTPUT_ROOT_PATH);
	strcat(binaryOutputFilePath1, "binaryOut1.dat");
	strcpy(binaryOutputFilePath2, OUTPUT_ROOT_PATH);
	strcat(binaryOutputFilePath2, "binaryOut2.dat");
	
	//	Please note here a very important detail that you will waste lots of time
	//	this semester.  This only works because my path strings are terminated with a '/'
	//	In a future program, you are going to ask the use to give you a root path string
	//	and your program will fail because
	//		o you assume that the path string ends with a '/', but it doesn't
	//		o you autimatically add a '/' without checking, and the string you build ends
	//			up with a "//" somewhere in the middle.
	
	int nbPts1, nbPts2;
	//	Here you may get a compiler warning about an unknown escape sequence
	//	character.  This is because my path contains space characters and some compilers
	//	are not happy with that.
	DataPoint* dataSet1 = readSimpleDataASCII(inputFilePath1, &nbPts1);
	DataPoint* dataSet2 = readFancierDataASCII(inputFilePath2, &nbPts2);
	writeDataASCII(nbPts1, dataSet1, asciiOutputFilePath);
		
	//----------------------------------------------------
	//	Part III:  I/O from and to a *binary* file
	//----------------------------------------------------
	//	this time I work in reverse, I generate my data, write it into a binary file,
	//	and check that I can read it back
	int	n = 5;
	double x[5] = {6.5, -2.3, 10, 12345.6, 0.0625};
	writeDataBinary(n, x, binaryOutputFilePath1);
	writeDataBinaryCharByChar(n, x, binaryOutputFilePath2);
	
	int nbPtsRead;
	double* y = readDataBinary(binaryOutputFilePath1, &nbPtsRead);

	printf("\nnumber of elements read back (regular mode): %d\n", nbPtsRead);
	int i=0;
	for (i=0; i<nbPtsRead; i++)
	printf("%lf\t", y[i]);
	printf("\n");
	
	double* z = readDataBinaryCharByChar(binaryOutputFilePath2, &nbPtsRead);

	printf("\nnumber of elements read back (char by char mode): %d\n", nbPtsRead);
	for (i=0; i<nbPtsRead; i++)
	printf("%lf\t", z[i]);
	printf("\n");

	//----------------------------------------------------
	//	Part V:		We don't have to do that, but this is
	//				often a way to expose pointer problems.
	//----------------------------------------------------
	free(z);
	free(y);
	free(dataSet2);
	free(dataSet1);
	
    return 0;
}


//-------------------------------------------------------------
//	This function gets formatted input data from the console
//	and prints data to the console as well
//-------------------------------------------------------------
void consoleIO(void) {

	int		m, n;
	float	x, y;
	
	//	In all the examples that follow, if what you type does not match the format specified
	//	in scanf, then nonsense values will be assigned to your variables (unlike Java, where
	//	an Exception would get thrown.  Youcan detect that something when wrong by checking
	//	that the value returned by scanf, which is the number of assigned and successfully 
	//	matched items
	int itemsRead;

	//	ask the user to enter an integer
	printf("Please enter an integer between 0 and 10000: ");
	//	the format %d refers to an integer. So here I want to convert into an int [%d]
	//	what will be entered by the user and record that int at the address of m
	itemsRead = scanf("%d", &m);
	if (itemsRead != 1) {
		//	cry for help
		printf("Data input did not match specified format\n");
	}
	
	//	I confirm what I read.  Again %d indicates a conversion: the value of m at this position
	//	in the output string
	printf("You typed: %d\n", m);

	//	This time I ask for two numbers separated by a comma
	printf("Please enter two integers between 0 and 10000, separated by a comma: ");
	itemsRead = scanf("%d,%d", &m, &n);
	if (itemsRead != 2) {
		//	note that I don't know which item was not properly matched
		printf("Data input did not match specified format\n");
	}
	
	//	I confirm what I read.  Again %d indicates a conversion: the value of m at this position
	//	in the output string
	printf("you typed %d and %d\n", m, n);

	//	I confirm again what I read, but this time I reformat my output
	//	I assigns 5 characters for the first number, printed left-justified (the - before 5),
	//  and 6 characters for the second number
	printf("Formatted output: you typed -->|%-5d|<-- and -->|%6d|<--\n", m, n);

	printf("Done with console I/O.  Moving on!\n");
}
