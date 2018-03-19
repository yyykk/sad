#include "predict.h"
#include "vector"
#include "iostream"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int vmNum = 0;
int foreVmNum = 0;
int foreRealCom = 0;
char opt[MAX_NAME_LEN];
char beginTime[MAX_NAME_LEN];
char endTime[MAX_NAME_LEN];
realComputer computer;
vector<vm> vmInfoVec;
vector<vm_data> dataInfoVec;

vector<Fore> foreVm;
vector<vector<Fore>> result;

void init_vm_info(char * info[MAX_INFO_NUM], int info_num, vector<vm> &vmList){
	vm vmTmp;
	sscanf(info[0], "%d %d %d", &(computer.cupNum), &(computer.RAMSize), &(computer.ROMSize));
	sscanf(info[2], "%d", &vmNum);
	for(int i = 0; i < vmNum; ++i){
		sscanf(info[i + 3], "%s %d %d", vmTmp.vmName, &(vmTmp.cpuNum), &(vmTmp.RAMSize));
		vmList.push_back(vmTmp);
	}
	sscanf(info[vmNum + 4], "%s", opt);
	sscanf(info[vmNum + 6], "%s", beginTime);
	sscanf(info[vmNum + 7], "%s", endTime);

}

void init_data_info(char * data[MAX_DATA_NUM], int data_num, vector<vm_data> &dataList){
	vm_data dataTmp;
	char year[MAX_NAME_LEN], month[MAX_NAME_LEN], day[MAX_NAME_LEN];
	char hour[MAX_NAME_LEN], minute[MAX_NAME_LEN], second[MAX_NAME_LEN];
	for(int i = 0; i < data_num; ++i){
		sscanf(data[i], "%s %s %[0-9]-%[0-9]-%[0-9] %[0-9]:%[0-9]:%[0-9]",
			dataTmp.dataID, dataTmp.vmName, year, month, day, hour, minute, second);
		//cout << year << " " << month << " " << hour << endl;
		dataTmp.year = atoi(year);
		dataTmp.month = atoi(month);
		dataTmp.day = atoi(day);
		dataTmp.hour = atoi(hour);
		dataTmp.minute = atoi(minute);
		dataTmp.second = atoi(second);
		dataList.push_back(dataTmp);
	}
}

void init_info(char * info[MAX_INFO_NUM], int info_num, char * data[MAX_DATA_NUM], int data_num){
	init_vm_info(info, info_num, vmInfoVec);
	init_data_info(data, data_num, dataInfoVec);
	cout << computer.cupNum << " " << computer.RAMSize << " " << computer.ROMSize << endl;
	cout << vmNum << endl;
	for(int i = 0; i < vmNum; ++i){
		cout << vmInfoVec[i].vmName << " " << vmInfoVec[i].cpuNum << " " << vmInfoVec[i].RAMSize << endl;
	}
	cout << opt << endl;
	cout << beginTime << endl;
	cout << endTime << endl;
	for(int i = 0; i < data_num; ++i){
		cout << dataInfoVec[i].dataID << " " << dataInfoVec[i].vmName << " " 
		<< dataInfoVec[i].year << "-" << dataInfoVec[i].month << "-" << dataInfoVec[i].day << " "  
		<< dataInfoVec[i].hour << ":" << dataInfoVec[i].minute << ":" << dataInfoVec[i].second << endl;
	}
}

void get_result(char* &file){

}

void predict_server(char * info[MAX_INFO_NUM], int info_num, char * data[MAX_DATA_NUM], int data_num, char * filename){
	init_info(info, info_num, data, data_num);
}

















