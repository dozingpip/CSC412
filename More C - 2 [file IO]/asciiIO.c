/*
 *  asciiIO.c
 *  C Input-Output
 *
 *  Created by jean-yves hervé on 2009/02/09.
 *	Updated 2016-01-31, revised 2018-01-24
 *
 */

#include <stdio.h>
#include <stdlib.h>
//
#include "dataTypes.h"
#include "asciiIO.h"

//	"private" functions
void readOneDataPoint(FILE *fp, DataPoint* pt);
void removeComments(char* line);
void readLine(FILE *fp, char *buffer);


//========================================================================================
//	readSimpleDataASCII
//
//	The simplest form of file input, from a human-readable text file that contains
//	the data and only the data, and even indicates how much of the data there is
//	(no need to check for end of file).
//========================================================================================

DataPoint* readSimpleDataASCII(char* filePath, int* nbPts) {

	//	1. Open the file to read from it.  By default the file is open as a "text" file
	//	meaning that the number 17 is written as 2 characters '1' '7'.  By opposition
	//	a "binary" file would store this number as 4 bytes in the standard IEEE format
	FILE* fp = fopen(filePath, "r");
	if (fp == NULL) {
		//	cry for help
		printf("Cannot open %s\n", filePath);
		exit(1);
	}
	
	//	read the number of data points.  This works exactly as console input,
	//	except that we have to specify where to read from (and we use fscanf instead of scanf)
	int itemsRead;
	itemsRead = fscanf(fp, "%d", nbPts);
	if (itemsRead != 1) {
		//	do something
		printf("Incorrect data format\n");
		exit(1);
	}
	
	//	Allocate the array of DataPoint structs
	DataPoint* dataPt = (DataPoint*) malloc((*nbPts)*sizeof(DataPoint));
	
	//	Now I read my data points
	for (int i=0; i<(*nbPts); i++) {
		readOneDataPoint(fp, dataPt + i);
	}
	
	//	close the file
	fclose(fp);
	
	return dataPt;
}


//========================================================================================
//	readFancierDataASCII
//
//	What makes the data "fancier" is that a line of the data file may contain 
//	(or even consist of) a comment starting with the # character
//========================================================================================

DataPoint* readFancierDataASCII(char* filePath, int* nbPts) {

	//	1. Open the file to read from it.
	FILE* fp = fopen(filePath, "r");
	if (fp == NULL) {
		//	cry for help
	}
	
	//	this is what I wil be reading my lines of data into
	char buffer[256];
	
	//	read the number of data points: should be the first line of data
	readLine(fp, buffer);
	if (sscanf(buffer, "%d", nbPts) != 1){
		//	do something
	}

	//	Allocate the array of DataPoint structs
	DataPoint* dataPt = (DataPoint*) malloc((*nbPts)*sizeof(DataPoint));
	
	//	No I read my data points
	for (int i=0; i<(*nbPts); i++) {
		readLine(fp, buffer);
		//	now I extract my data from the buffer using sscanf instead of scanf or fscanf
		//	I get 2 int, one float, and then 4 characters.  Note that I could not read the
		//	4 characters as a string using format %s because it is not 0-terminated.
//		if (sscanf( buffer, "%d%d%f%c%c%c%c",
//					//	pass pointers to x, y, z fields of the dataPt[i] struct
//					&(dataPt[i].x), &(dataPt[i].y), &(dataPt[i].z),
//					// dataPt[i].c is a pointer to char, so c, c+1, c+2, c+3 are pointers
//					// to the four characters to read.
//					dataPt[i].c, dataPt[i].c+1, dataPt[i].c+2, dataPt[i].c+3) != 7) {
//			//	do something
//			
//		}
		if (sscanf( buffer, "%d%d%f",
					//	pass pointers to x, y, z fields of the dataPt[i] struct
					&(dataPt[i].x), &(dataPt[i].y), &(dataPt[i].z)) != 3) {
			//	do something
			
		}
	}
	
	//	close the file
	fclose(fp);
	
	return dataPt;
}


//========================================================================================
//	readOneDataPoint
//
//	I don't really need to do that in a separate function.  I just wanted to give
//	one more example of parameter passing
//========================================================================================

void readOneDataPoint(FILE *fp, DataPoint* pt) {

		fscanf(fp, "%d%d%f%c%c%c%c",
					//	pass pointers to x, y, z fields of the dataPt[i] struct
					&(pt->x), &(pt->y), &(pt->z),
					// dataPt[i].c is a pointer to char, so c, c+1, c+2, c+3 are pointers
					// to the four characters to read.
					pt->c, pt->c+1, pt->c+2, pt->c+3);
									
}


//========================================================================================
//	readLine
//
//	Reads a line of the data file, skipping comment lines
//========================================================================================

void readLine(FILE *fp, char *buffer) {
	while (1)
	{
		if (fgets(buffer, 255, fp) == NULL)
		{
			buffer[0] = '\0';
			return;
		}
		else if (buffer[0] != '#')
		{
			removeComments(buffer);
			return;
		}
	}
}

//========================================================================================
//	removeComments
//
//	Removes comments at the end of a 0-terminated input line
//========================================================================================

void removeComments(char* line) {
	int		i, r;
	
	for(i=0; (line[i]!='#') && (line[i]!='\0'); i++);
	
	//	if we have found a comment at the end of the line
	if (line[i] == '#')
	{
		r = i;
		//	we go back to find the last non-blank character
		for (i=r-1; (i>=0) && ((line[i]==' ') || (line[i] == '\t')); i--);
		
		if (i>0)
			line[i+1] = '\0';
	}
}

//	What follows is a "cosmetic" precompiler statement.  #pragma statements
//	are specific to some compilers or IDEs , unlike other # statements like #if, #define, etc.,
//	which work the same for all compilers.
//	#pragma mark -    creates a thin line separator in the list of functions in the file
//						for some IDEs (this was an original CodeWarrior feature borrowed
//						by Xcode
//	To "protect" that statement for compilers that don't support it, I wrap it into an
//	#if 0 statement, which guarantees that the compiler wil never see it.
//	#pragma mark -   is caught by the editor, not the compiler, so it does not care about the
//						#if 0
#if 0
#pragma mark -
#endif


//========================================================================================
//	writeDataASCII
//
//	Nothing fancy, just writes formatted data into a text file
//========================================================================================

void writeDataASCII(int nbPts, DataPoint *dataPt, char* filePath) {

	//	open e file to write into.  Again, the default file format is a text file
	FILE* fp = fopen(filePath, "w");
	
	//	And now I write my data using whatever format I want.  Nothing particularly
	//	illuminating, maybe the fact that I output the first two characters as their
	//	ASCII Code, and the next two as characters proper.  Of course, to read the
	//	characters I would have to use %c in my scanf format.
	fprintf(fp, "%d", nbPts);
	
	for (int i=0; i<nbPts; i++) {
		fprintf(fp, "%d %d %f %d %d %c %c\n", dataPt[i].x, dataPt[i].y, dataPt[i].z,
											dataPt[i].c[0], dataPt[i].c[1], dataPt[i].c[2],
											dataPt[i].c[3]);
	}
	
	//	close the file
	fclose(fp);
}
