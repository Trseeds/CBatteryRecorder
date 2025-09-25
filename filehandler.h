#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>

int CloseFile(FILE* pFile);
int CheckFile(char* pFilename);
int MakeFile(char* pFilename);
FILE* OpenFileNW(char* pFilename);
int DeleteFileNW(char* pFilename);
int AppendFile(char* pFilename, char* pText);

#endif
