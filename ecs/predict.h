#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "lib_io.h"
#include <map>

#define MAX_NAME_LEN 64

struct realComputer{
	int cupNum;
	int RAMSize;
	int ROMSize;
};

struct vm{
    char vmName[MAX_NAME_LEN];
    int cpuNum;
    int RAMSize;
    bool operator == (const vm& vma){
        return this->vmName == vma.vmName;
    }
};

struct time_1s{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct vm_data{
    char dataID[MAX_NAME_LEN];
    char vmName[MAX_NAME_LEN];
    char date[MAX_NAME_LEN];
    char time[MAX_NAME_LEN];
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct Fore{
	char vmName[MAX_NAME_LEN];
	int Num;
};

void predict_server(char * info[MAX_INFO_NUM], int info_num, char * data[MAX_DATA_NUM], int data_num, char * filename);	

#endif
