#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include "filehandler.h"

void AddTrailingZero(int Num, char* NumString)
{
    if (Num < 10)
    {
        sprintf(NumString, "0%d", Num);
    }
    else
    {
        sprintf(NumString, "%d", Num);
    }
}

void GetTimeString(char* TimeString)
{
    char NumString[3];
    char NumString2[3];
    char Meridiem[3];
    char Hour[3];
    SYSTEMTIME UnfTime;
    GetLocalTime(&UnfTime);
    if (UnfTime.wHour > 11)
    {
        AddTrailingZero(UnfTime.wHour-12, NumString);
        sprintf(Hour, "%s", NumString);
        sprintf(Meridiem, "PM");
    }
    else
    {
        AddTrailingZero(UnfTime.wHour, NumString);
        sprintf(Hour, "%s", NumString);
        sprintf(Meridiem, "AM");
    }
    AddTrailingZero(UnfTime.wMinute, NumString);
    AddTrailingZero(UnfTime.wSecond, NumString2);
    sprintf(TimeString, "%s:%s:%s %s",Hour,NumString,NumString2,Meridiem);
}

int GetBatteryPercentage()
{
    SYSTEM_POWER_STATUS PowerStatus;
    GetSystemPowerStatus(&PowerStatus);
    return(PowerStatus.BatteryLifePercent);
}

int main()
{
    char DesiredFile[32];
    int ExitPercentage;
    int LastPercentage = 0;
    int Percentage = GetBatteryPercentage();
    char Time[12];
    char NumString[3];
    char FinalString[128];
    char UserChoice[3];
    char WorkingSymbols[] = {'\\','|','/','-'};
    
    puts("Charge test (1) or discharge test? (2)\nNote that this only changes when the test stops and where it saves.");
    while (1)
    {
        fgets(UserChoice, 3, stdin);
        if (UserChoice[0] == '1' || UserChoice[0] == '2')
        {
            break;
        }
        else
        {
            puts("\nInvalid selection.");
        }
    }
    if (UserChoice[0] == '1')
    {
        ExitPercentage = 100;
        sprintf(DesiredFile,"charge.csv");
    }
    else
    {
        ExitPercentage = 10;
        sprintf(DesiredFile,"discharge.csv");
    }
    FhDeleteFile(DesiredFile);
    for(int i = 0; i < 40; i++)
    {
        Percentage = GetBatteryPercentage();
        if (LastPercentage != Percentage)
        {
            GetTimeString(Time);
            sprintf(FinalString, "%s, %d%%\n",Time,Percentage);
            int res = FhAppendFile(DesiredFile, FinalString);
            if (res != 0)
            {
                printf("File error with file %s",DesiredFile);
                return(1);
            }
        }
        if (Percentage == ExitPercentage)
        {
            spawnlp(0x00, "python", "python", "plot.py", DesiredFile, NULL);
            return(0);
        }
        LastPercentage = Percentage;
        printf("\rRecording %c", WorkingSymbols[(i/10)]);
        if (i == 39)
        {
            i = -1;
        }
    }
    return(0);
}
