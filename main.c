#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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
    return(&NumString);
}

void GetTimeString(char* TimeString)
{
    char NumString[3];
    char NumString2[3];
    char Meridiem[3];
    char Hour[3];
    SYSTEMTIME UnfTime;
    GetLocalTime(&UnfTime);
    if (UnfTime.wHour > 12)
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
    char WorkingSymbols[] = {'0xFF','\\','|','/','-'};
    while (1)
    {
        puts("Charge test (1) or discharge test? (2)\nNote that this only changes where the test stops and where it saves.");
        fgets(UserChoice, 3, stdin);
        if (UserChoice[0] == '1' || UserChoice[0] == '2')
        {
            break;
        }
        else
        {
            puts("\n\n\nInvalid selection.\n\n");
        }
    }
    if (UserChoice[0] == '1')
    {
        ExitPercentage = 100;
        sprintf(DesiredFile,"charge.csv");
    }
    else
    {
        ExitPercentage = 5;
        sprintf(DesiredFile,"discharge.csv");
    }
    DeleteFileNW(DesiredFile);
    for(int i = 0; i < 500; i++)
    {
        Percentage = GetBatteryPercentage();
        if (LastPercentage != Percentage)
        {
            GetTimeString(Time);
            sprintf(FinalString, "%s, %d%%\n",Time,Percentage);
            int res = AppendFile(DesiredFile, FinalString);
            if (res != 0)
            {
                printf("File error with file %s",DesiredFile);
                return(1);
            }
        }
        if (Percentage == ExitPercentage)
        {
            AppendFile(DesiredFile, "Recording Finished.");
            puts("\rRecording Finished");
            return(0);
        }
        LastPercentage = Percentage;
        printf("\rRecording %c", WorkingSymbols[(i/100)%10]);
        if (i == 499)
        {
            i = 99;
        }
    }
    return(0);
}