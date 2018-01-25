/*
 *  asciiIO.h
 *  C Input-Output
 *
 *  Created by jean-yves hervé on 2009/02/09.
 *	Updated 2016-01-31, revised 2018-01-24
 *
 */

//	You need to "protect" your header files against multiple loads
#ifndef ASCII_IO_H
#define ASCII_IO_H

#include "dataTypes.h"

DataPoint* readSimpleDataASCII(char* filePath, int *nbPts);
DataPoint* readFancierDataASCII(char* filePath, int *nbPts);

void writeDataASCII(int nbPts, DataPoint *dataSet, char* filePath);




#endif		//	ASCII_IO_H
