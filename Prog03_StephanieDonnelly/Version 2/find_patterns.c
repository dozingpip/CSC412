#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
int getFilePaths(const char* dataRootPath, int* numFiles, char*** fileNames);

int main(int argc, const char* argv[]) {
	const char* imageFolder = argv[1];
	const char* patternFolder = argv[2];

	// get all the image file paths and the number of images
	int numImages;
	char** imagePaths;
	getFilePaths(imageFolder, &numImages, &imagePaths);
	// get all the pattern file paths and the number of patterns
	int numPatterns;
	char** patternPaths;
	getFilePaths(patternFolder, &numPatterns, &patternPaths);
	
	char** outputFiles = (char**) malloc(numImages*sizeof(char*));
	int* matchCountPerPattern = (int*) calloc(numPatterns, sizeof(int));
	int* processIds = (int*) calloc(numImages, sizeof(int));
	for(int f = 0; f<numImages; f++){
		processIds[f] = fork();
		if(processIds[f]==0){
			char* imageFilePath = (char*) malloc((strlen(imageFolder)+strlen(imagePaths[f])+1)*sizeof(char));
			strcpy(imageFilePath, imageFolder);
			strcat(imageFilePath, imagePaths[f]);
			execlp("./child", "child", imageFilePath, patternFolder, (char*)NULL);
			free(imageFilePath);
		}else if(processIds[f]>0){
			printf("hi, i'm a parent\n");
		}else{
			printf("failed to create process, fork returned %d\n", processIds[f]);
		}
	}

	
	pid_t termProcess;
	int statusVal;
	for(int i = 0; i<numImages; i++){
		termProcess = waitpid(processIds[i], &statusVal, 0);
		printf("process id %d terminated\n", termProcess);
		FILE *fp;
		char* outFileName = (char*) malloc(256*sizeof(char));
		sprintf(outFileName, "p_%d_output.txt", processIds[i]);
		fp = fopen(outFileName, "r");
		int firstInt;
		int counter;
		while(fscanf(fp,"%d", &firstInt)!=EOF){
			matchCountPerPattern[counter]+=firstInt;
			while(fgetc(fp)!='\n');
			counter++;
		}
		fclose(fp);
		free(outFileName);
	}

	
	for(int j = 0; j<numPatterns; j++){
		printf("%s got %d matches\n", patternPaths[j], matchCountPerPattern[j]);
	}
	
	free(outputFiles);
	free(matchCountPerPattern);
	free(processIds);
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
