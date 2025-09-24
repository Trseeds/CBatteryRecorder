#include <stdio.h>
#include <stdlib.h>

int CheckFile(char* pFilename)
{
    FILE* pCheck = fopen(pFilename,"r");
    if (pCheck == NULL)
    {
        return(1);
    }
    CloseFile(pCheck);
    return(0);
}

int MakeFile(char* pFilename)
{
    FILE* pNewFile = fopen(pFilename, "w+");
    if (pNewFile == NULL)
    {
        return(1);
    }
    CloseFile(pNewFile);
    return(0);
}

FILE* OpenFileNW(char* pFilename) //NW stands for Non-Windows. Thanks Windows.h!
{
    if (CheckFile(pFilename) != 0)
    {
        if (MakeFile(pFilename) != 0)
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

int DeleteFileNW(char* pFilename)
{
    if (remove(pFilename) != 0)
    {
        return(1);
    }
    return(0);
}

int CloseFile(FILE* pFile)
{
    fclose(pFile);
    return(0);
}

int AppendFile(char* pFilename, char* pText)
{
    FILE* pFile = OpenFileNW(pFilename);
    if (pFile == NULL)
    {
        return(1);
    }
    fprintf(pFile, pText);
    CloseFile(pFile);
    return(0);
}