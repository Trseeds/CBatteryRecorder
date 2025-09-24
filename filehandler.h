#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>

int CheckFile(char* pFilename);
int MakeFile(char* pFilename);
FILE* OpenFileNW(char* pFilename);
int DeleteFileNW(char* pFilename);
int CloseFile(FILE* pFile);
int AppendFile(char* pFilename, char* pText);

#endif