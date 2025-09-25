#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>

int FhCloseFile(FILE* pFile);
int FhCheckFile(char* pFilename);
int FhMakeFile(char* pFilename);
FILE* FhOpenFile(char* pFilename);
int FhDeleteFile(char* pFilename);
int FhAppendFile(char* pFilename, char* pText);

#endif
