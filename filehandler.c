#include <stdio.h>
#include <stdlib.h>

int FhCloseFile(FILE* pFile)
{
    fclose(pFile);
    return(0);
}

int FhCheckFile(char* pFilename)
{
    FILE* pCheck = fopen(pFilename,"r");
    if (pCheck == NULL)
    {
        return(1);
    }
    FhCloseFile(pCheck);
    return(0);
}

int FhMakeFile(char* pFilename)
{
    FILE* pNewFile = fopen(pFilename, "w+");
    if (pNewFile == NULL)
    {
        return(1);
    }
    FhCloseFile(pNewFile);
    return(0);
}

FILE* FhOpenFile(char* pFilename)
{
    if (FhCheckFile(pFilename) != 0)
    {
        if (FhMakeFile(pFilename) != 0)
        {
            return(NULL);
        }
    }
    FILE* pNewFile = fopen(pFilename, "a");
    if (pNewFile == NULL)
    {
        return(NULL);
    }
    return(pNewFile);
}

int FhDeleteFile(char* pFilename)
{
    if (remove(pFilename) != 0)
    {
        return(1);
    }
    return(0);
}

int FhAppendFile(char* pFilename, char* pText)
{
    FILE* pFile = FhOpenFile(pFilename);
    if (pFile == NULL)
    {
        return(1);
    }
    fprintf(pFile, pText);
    FhCloseFile(pFile);
    return(0);
}
