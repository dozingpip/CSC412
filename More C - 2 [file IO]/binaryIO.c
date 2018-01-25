/*
 *  binaryIO.c
 *  C Input-Output
 *
 *  Created by jean-yves hervé on 2009/02/09.
 *	Updated 2016-01-31, revised 2018-01-24
 *
 */

#include <stdlib.h>
#include <stdio.h>
//
#include "binaryIO.h"


//========================================================================================
//	readDataBinary
//
//	Reads data from a binary file.  Shows how to do it one item at a time, or
//	to read in one shot a whole group of data
//========================================================================================

double* readDataBinary(char* filePath, int* nbPts) {

	//	1. Open the file to read from.  This time we say that we open a "binary" file.
	FILE* fp = fopen(filePath, "rb");
	if (fp == NULL) {
		//	cry for help
	}
	
	//	My data consist only of integers in binary form.  The first integer is the
	//	number of data points, and it is followed by al the data (int)

	//	read the number of data points.
	unsigned long itemsRead = fread(	nbPts,			//	start address
									sizeof(int),	//	size of one element in bytes
									1,				//	number of elements to read
									fp);			//	stream to read from
	if (itemsRead != 1) {
		//	do something
	}
	
	//	Allocate the array of doubles
	double* data = (double*) malloc((*nbPts)*sizeof(double));
	
	//	Now I read my data
	itemsRead = fread(	data,					//	start address  
						sizeof(double),			//	size of one element in bytes
						(*nbPts),				//	number of elements to read
						fp);					//	stream to read from
	if (itemsRead != (*nbPts)) {
		//	do something
	}
		
	//	close the file
	fclose(fp);

	return data;
}


//========================================================================================
//	readDataBinaryCharByChar
//
//	This one here is a bit silly for the data I am reading but can be adapted to something
//	useful for some applications:  Here I fread the data byte by byte and "reconstitute"
//	my data (here, ints) from these bytes.
//========================================================================================

double* readDataBinaryCharByChar(char* filePath, int* nbPts) {
	//	1. Open the file to read from.  This time we say that we open a "binary" file.
	FILE* fp = fopen(filePath, "rb");
	if (fp == NULL) {
		//	cry for help
	}
	
	//	Read the number of data points
	//	I map an array of char to the address of my number of points
	char* baseAddr = (char*) nbPts;
	for (int j=0; j<sizeof(int); j++)
		baseAddr[j] = fgetc(fp);	
	//	Allocate the array of doubles
	double* data = (double*) malloc((*nbPts)*sizeof(double));
	
	//	write the data
	for (int i=0; i<(*nbPts); i++) {
		char* dataAddr = (char*) (data + i);
		for (int j=0; j<sizeof(double); j++)
			dataAddr[j] = fgetc(fp);	
	}
		
	//	close the file
	fclose(fp);

	return data;
}

#if 0
#pragma mark -
#endif

//========================================================================================
//	writeDataBinary
//
//	Writes data into a binary file.  Shows how to do it one item at a time, or
//	to write in one shot a whole group of data
//========================================================================================
void writeDataBinary(int nbPts, double *data, char* filePath) {

	//	1. Open the file to write into.  This time we say that we open a "binary" file.
	FILE* fp = fopen(filePath, "wb");
	if (fp == NULL) {
		//	cry for help
	}
	
	//	Write the number of data points
	//	I map an array of char to the address of my number of points
	unsigned long itemsWritten = fwrite(	&nbPts,			//	start address
										sizeof(int),	//	size of one element in bytes
										1,				//	number of elements to write
										fp);			//	stream to read from
	if (itemsWritten != 1) {
		//	cry for help
	}
	
	//	write the data
	for (int i=0; i<nbPts; i++) {
		itemsWritten = fwrite(	data,			//	start address
								sizeof(double),	//	size of one element in bytes
								nbPts,			//	number of elements to write
								fp);			//	stream to read from
		if (itemsWritten != nbPts) {
			//	cry for help
		}
	}
		
	//	close the file
	fclose(fp);
}


//========================================================================================
//	writeDataBinaryCharByChar
//
//	This one here is a bit silly for the data I am writing but can be adapted to something
//	useful for some applications:  Here I decompose my data into bytes and fwrite the 
//	bytes one by one to my file
//========================================================================================
void writeDataBinaryCharByChar(int nbPts, double *data, char* filePath) {
	//	1. Open the file to write into.  This time we say that we open a "binary" file.
	FILE* fp = fopen(filePath, "wb");
	if (fp == NULL) {
		//	cry for help
	}
	
	//	Write the number of data points
	//	I map an array of char to the address of my number of points
	char* baseAddr = (char*) &nbPts;
	for (int j=0; j<sizeof(int); j++)
		if (fputc(baseAddr[j], fp) != baseAddr[j]) {
			//	cry for help
		}
	
	//	write the data
	for (int i=0; i<nbPts; i++) {
		char* dataAddr = (char*) (data + i);
		for (int j=0; j<sizeof(double); j++)
			if (fputc(dataAddr[j], fp) != dataAddr[j]) {
				//	cry for help
			}
	}
		
	//	close the file
	fclose(fp);
}
