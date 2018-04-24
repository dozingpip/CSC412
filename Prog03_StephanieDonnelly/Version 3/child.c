#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void getColumnsRows(FILE **fp, char*** buffer, int** columnsRows);
void freeIntBuffers(int** buffers, int numBuffers);
void freeBuffers(char*** buffers, int numBuffers, int** innerBuffers);
void compareTextToPatterns(char* textFilePath, const char* patternFolder);
int getFilePaths(const char* dataRootPath, int* numFiles, char*** fileNames);

int main(int argc, const char* argv[]){
	const char* textFilePath = argv[1];
	const char* patternFolder = argv[2];
	// get all the pattern file paths and the number of patterns
	int numPatterns;
	char** patternPaths;
	getFilePaths(patternFolder, &numPatterns, &patternPaths);

	FILE *textFilePointer;
	textFilePointer = fopen(textFilePath, "r");

	char** imageBuffer;
	int* imageColumnsRows;
	getColumnsRows(&textFilePointer, &imageBuffer, &imageColumnsRows);
	fclose(textFilePointer);
	
	char*** patternBuffers = (char***) malloc(numPatterns*sizeof(char**));
	int** columnsRows = (int**) malloc(numPatterns*sizeof(int*));
	for(int i = 0; i<numPatterns; i++){
		FILE *patternFilePointer;
		char* patternPath = (char*) malloc((strlen(patternFolder)+strlen(patternPaths[i])+2)*sizeof(char));
		strcpy(patternPath, patternFolder);
		patternFilePointer=fopen(strcat(patternPath, patternPaths[i]), "r");
		getColumnsRows(&patternFilePointer, &(patternBuffers[i]), &(columnsRows[i]));
		fclose(patternFilePointer);
		free(patternPath);
	}

	//comparing begins!
	int** resultsBuffer = (int**) malloc(numPatterns*sizeof(int*));
	int* timesPatternFounds = (int*) malloc(numPatterns*sizeof(int));
	for(int i = 0; i<numPatterns; i++){
		timesPatternFounds[i] = 0;
		resultsBuffer[i] = (int*) malloc(imageColumnsRows[0]*imageColumnsRows[1]*2*sizeof(int));
		char patternLine0[] = {patternBuffers[i][0][0], patternBuffers[i][0][1], patternBuffers[i][0][2]};
		char patternLine1[] = {patternBuffers[i][1][0], patternBuffers[i][1][1], patternBuffers[i][1][2]};
		char patternLine2[] = {patternBuffers[i][2][0], patternBuffers[i][2][1], patternBuffers[i][2][2]};
		for(int a = 0; a<imageColumnsRows[0]-2; a++){
			for(int b = 0; b<imageColumnsRows[1]-2; b++){
				char stringLine0[] = {imageBuffer[a][b], imageBuffer[a][b+1], imageBuffer[a][b+2]};
				if(strncmp(stringLine0, patternLine0, 3) == 0){
					char stringLine1[] = {imageBuffer[a+1][b], imageBuffer[a+1][b+1], imageBuffer[a+1][b+2]};
					if(strncmp(stringLine1, patternLine1, 3) == 0){
						char stringLine2[] = {imageBuffer[a+2][b], imageBuffer[a+2][b+1], imageBuffer[a+2][b+2]};
						if(strncmp(stringLine2, patternLine2, 3) == 0){
							resultsBuffer[i][2*timesPatternFounds[i]] = a;
							resultsBuffer[i][2*timesPatternFounds[i]+1] = b;
							timesPatternFounds[i]++;
						}
					}
				}
			}
		}
	}

	FILE *outputFilePointer;
	
	char* outFileName = (char*) malloc(256*sizeof(char));
	sprintf(outFileName, "p_%d_output",getpid());
	printf("opening %s\n", outFileName);
	outputFilePointer = fopen(outFileName, "w");
	printf("opened %s\n", outFileName);
	for(int c = 0; c<numPatterns; c++){
		fprintf(outputFilePointer, "%d", timesPatternFounds[c]);
		for(int d = 0; d<timesPatternFounds[c]*2; d++){
			fprintf(outputFilePointer, " %d", resultsBuffer[c][d]);
		}
		fprintf(outputFilePointer, "\n");
	}
	fclose(outputFilePointer);
	
	//finished, so free everything
	freeBuffers(patternBuffers, numPatterns, columnsRows);
	freeIntBuffers(columnsRows, numPatterns);
	free(imageBuffer);
	free(timesPatternFounds);
	freeIntBuffers(resultsBuffer, numPatterns);
	printf("child process finished!\n");
	exit(0);
}





void getColumnsRows(FILE **fp, char*** buffer, int** columnsRows){
	int columns, rows;
	fscanf(*fp, "%d %d\n", &columns, &rows);
	*buffer = (char**) malloc(rows*sizeof(char*));
	for(int i=0; i<rows; i++){
		(*buffer)[i] = (char*) malloc(columns*sizeof(char));
		fread((*buffer)[i], sizeof(char), columns, *fp);
		fgetc(*fp);
	}
	*columnsRows = (int*) malloc(2*sizeof(int));
	(*columnsRows)[0] = rows;
	(*columnsRows)[1] = columns;
	
}

void freeBuffers(char*** buffers, int numBuffers, int** innerBuffers){
	for(int i = 0; i< numBuffers; i++){
		for(int j = 0; j<innerBuffers[i][0]; j++){
			free(buffers[i][j]);
		}		
		free(buffers[i]);
	}
	free(buffers);
}

void freeIntBuffers(int** buffers, int numBuffers){
	for(int i = 0; i<numBuffers; i++){
		free(buffers[i]);
	}
	free(buffers);
}

int getFilePaths(const char* dataRootPath, int* numFiles, char*** fileNames){
	
    DIR* directory = opendir(dataRootPath);
    if (directory == NULL) {
		printf("data folder %s not found\n", dataRootPath);
		return 1;
	}
	
    struct dirent* entry;
	int counter = 0;
	
	//	First pass: count the entries
    while ((entry = readdir(directory)) != NULL) {
        char* name = entry->d_name;
        if (name[0] != '.') {
			counter++;
        }
    }
	closedir(directory);
	
	printf("%d files found\n", counter);

	//	Now allocate the array of file names
    char** fileName = (char**) malloc(counter*sizeof(char*));

	//	Second pass: read the file names
	int k=0;
	directory = opendir(dataRootPath);
    while ((entry = readdir(directory)) != NULL) {
        char* name = entry->d_name;
        //	Ignores "invisible" files (name starts with . char)
        if (name[0] != '.') {
			fileName[k] = malloc((strlen(name) +1)*sizeof(char));
			strcpy(fileName[k], name);
			k++;
        }
    }
	closedir(directory);

	for (int k=0; k<counter; k++) {
		printf("\t%s\n", fileName[k]);
	}
	*fileNames = fileName;
	*numFiles = counter;

	return 0;
}


