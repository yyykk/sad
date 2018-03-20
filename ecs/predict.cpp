#include "predict.h"
#include "xjbyc.h"
#include "vector"
#include "iostream"
#include <algorithm>
#include <map>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int vmNum = 0;
int foreVmNum = 0;
int foreRealCom = 0;
char opt[MAX_NAME_LEN];
time_1s beginTime;
time_1s endTime;
realComputer computer;
vector<vm> vmInfoVec;
vector<vm_data> dataInfoVec;

vector<vm> foreVm;
vector<map<string, int> > result;

bool foreVm_sort(const vm& vma, const vm& vmb){
	int a = 0, b = 0;
	sscanf(vma.vmName, "flavor%d", &a);
	sscanf(vmb.vmName, "flavor%d", &b);
	return a > b;
}

void init_vm_info(char * info[MAX_INFO_NUM], int info_num, vector<vm> &vmList){
	vm vmTmp;
	char year[MAX_NAME_LEN], month[MAX_NAME_LEN], day[MAX_NAME_LEN];
	char hour[MAX_NAME_LEN], minute[MAX_NAME_LEN], second[MAX_NAME_LEN];
	sscanf(info[0], "%d %d %d", &(computer.cupNum), &(computer.RAMSize), &(computer.ROMSize));
	sscanf(info[2], "%d", &vmNum);
	for(int i = 0; i < vmNum; ++i){
		sscanf(info[i + 3], "%s %d %d", vmTmp.vmName, &(vmTmp.cpuNum), &(vmTmp.RAMSize));
		vmList.push_back(vmTmp);
	}
	sscanf(info[vmNum + 4], "%s", opt);
	sscanf(info[vmNum + 6], "%[0-9]-%[0-9]-%[0-9] %[0-9]:%[0-9]:%[0-9]", year, month, day, hour, minute, second);
	beginTime.year = atoi(year);
	beginTime.month = atoi(month);
	beginTime.day = atoi(day);
	beginTime.hour = atoi(hour);
	beginTime.minute = atoi(minute);
	beginTime.second = atoi(second);
	sscanf(info[vmNum + 7], "%[0-9]-%[0-9]-%[0-9] %[0-9]:%[0-9]:%[0-9]", year, month, day, hour, minute, second);
	endTime.year = atoi(year);
	endTime.month = atoi(month);
	endTime.day = atoi(day);
	endTime.hour = atoi(hour);
	endTime.minute = atoi(minute);
	endTime.second = atoi(second);
}

void init_data_info(char * data[MAX_DATA_NUM], int data_num, vector<vm_data> &dataList){
	vm_data dataTmp;
	char year[MAX_NAME_LEN], month[MAX_NAME_LEN], day[MAX_NAME_LEN];
	char hour[MAX_NAME_LEN], minute[MAX_NAME_LEN], second[MAX_NAME_LEN];
	for(int i = 0; i < data_num; ++i){
		sscanf(data[i], "%s %s %[0-9]-%[0-9]-%[0-9] %[0-9]:%[0-9]:%[0-9]",
			dataTmp.dataID, dataTmp.vmName, year, month, day, hour, minute, second);
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
	//cout << vmNum << endl;
	//for(int i = 0; i < vmNum; ++i){
	//	cout << vmInfoVec[i].vmName << " " << vmInfoVec[i].cpuNum << " " << vmInfoVec[i].RAMSize << endl;
	//}
	//cout << opt << endl;
	//cout << beginTime << endl;
	//cout << endTime << endl;
	//for(int i = 0; i < data_num; ++i){
	//	cout << dataInfoVec[i].dataID << " " << dataInfoVec[i].vmName << " " 
	//	<< dataInfoVec[i].year << "-" << dataInfoVec[i].month << "-" << dataInfoVec[i].day << " "  
	//	<< dataInfoVec[i].hour << ":" << dataInfoVec[i].minute << ":" << dataInfoVec[i].second << endl;
	//}
}

void bag(){
	int s = 0, vm_Val = 0, opt_s = strcmp(opt, "CPU");
	int opt_val = opt_s == 0 ? computer.cupNum : computer.RAMSize;
	sort(foreVm.begin(), foreVm.end(), foreVm_sort);
	vector<int> opt_remain;
	for(unsigned int i = 0; i < foreVm.size(); ++i){
		s = 0;
		vm_Val = opt_s == 0 ? foreVm[i].cpuNum : foreVm[i].RAMSize;
		//cout << "vm_Val = " << vm_Val << endl;
		for(unsigned int j = 0; j < result.size(); ++j){
			//cout << "opt_remain = " << opt_remain[j] << endl;
			if(opt_remain[j] >= vm_Val){
				opt_remain[j] -= vm_Val;
				result[j][foreVm[i].vmName] += 1;
				s = 1;
				break;
			}
		}
		if(s == 0){
			map<string, int> temp;
			temp[foreVm[i].vmName] += 1;
			result.push_back(temp);
			opt_remain.push_back(opt_val - vm_Val);
		}
		for(unsigned int i = 0; i < opt_remain.size(); ++i){
			//cout << opt_remain[i] << endl;
		}
	}
	for(unsigned int i = 0; i < result.size(); ++i){
		cout << i + 1 << endl;
		for(map<string, int>::iterator it = result[i].begin(); it != result[i].end(); ++it){
			cout << it->first << " " << it->second << endl;
		}
		cout << endl;
	}
	cout << "bag_end" << endl;
}

void format_result(char* file){
	sprintf(file, "%d\n", foreVm.size());
	map<string, int> temp;
	for(unsigned int i = 0; i < foreVm.size(); ++i){
		temp[foreVm[i].vmName] += 1;
	}
	for(map<string, int>::iterator it = temp.begin(); it != temp.end(); ++it) {
		sprintf(file, "%s%s %d\n", file, (it->first).c_str(), it->second);
	}
	sprintf(file, "%s\n", file);
	sprintf(file, "%s%d\n", file, result.size());
	for(unsigned int i = 0; i < result.size(); ++i){
		sprintf(file, "%s%d ", file, i + 1);
		for(map<string, int>::iterator it = result[i].begin(); it != result[i].end(); ++it){
			sprintf(file, "%s%s %d ", file, (it->first).c_str(), it->second);
		}
		sprintf(file, "%s\n", file);
	}
	cout << "format_end" << endl;
}

/*
void test(){
	strcpy(opt, "CPU");
	vm temp[6] = 
	{
		{"flavor5", 2, 4096}, {"flavor5", 2, 4096}, {"flavor5", 2, 4096},
		{"flavor10", 8, 8192}, {"flavor10", 8, 8192},
		{"flavor15", 16, 65536}
	};
	for(int i = 0; i < 6; ++i){
		foreVm.push_back(temp[i]);
	}
	cout << "test_end" << endl;
}
*/

void predict_server(char * info[MAX_INFO_NUM], int info_num, char * data[MAX_DATA_NUM], int data_num, char * filename){
	char result_file[MAX_DATA_NUM];
	init_info(info, info_num, data, data_num);
	//test();
	xjbyc(foreVm, dataInfoVec, vmInfoVec);
	bag();
	format_result(result_file);
	cout << result_file;
	write_result(result_file, filename);
}

















