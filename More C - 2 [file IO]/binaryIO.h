/*
 *  binaryIO.h
 *  C Input-Output
 *
 *  Created by jean-yves hervé on 2009/02/09.
 *	Updated 2016-01-31, revised 2018-01-24
 *
 */

//	You need to "protect" your header files against multiple loads
#ifndef BINARY_IO_H
#define BINARY_IO_H

double* readDataBinary(char* filePath, int* nbPts);

double* readDataBinaryCharByChar(char* filePath, int* nbPts);

void writeDataBinary(int nbPts, double* data, char* filePath);

void writeDataBinaryCharByChar(int nbPts, double *data, char* filePath);

#endif		//	BINARY_IO_H
