#include "xjbyc.h"
#include <string.h>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

int find_vm(string vmName, std::vector<vm> &vmInfoVec){
    for(unsigned int i = 0; i < vmInfoVec.size(); ++i){
        if(strcmp(vmInfoVec[i].vmName, vmName.c_str()) == 0){
            return i;
        }
    }
    return -1;
}

void xjbyc(std::vector<vm> &foreVm, std::vector<vm_data> &data, std::vector<vm> &vmInfoVec){
    float day_num = 1.0, day_s = data[0].day;
    map<string, float> foreVmMap;
    for(unsigned int i = 0; i < vmInfoVec.size(); ++i){
        foreVmMap[vmInfoVec[i].vmName] = 0;
    }
    for(unsigned int i = 0; i < data.size(); ++i){
        if(data[i].day != day_s){
            day_num += 1;
            day_s = data[i].day;
        }
        if(foreVmMap.find(data[i].vmName) != foreVmMap.end()){
            //cout << data[i].vmName << " " << data[i].day << endl;
            foreVmMap[data[i].vmName] += 1;
        }
    }
    cout << "map_size = " << foreVmMap.size() << endl;
    cout << "day = " << day_num << endl;
    for(map<string, float>::iterator it = foreVmMap.begin(); it != foreVmMap.end(); ++it){
        cout << it->first << " " << it->second << endl;
        for(int i = 0; i < it->second / day_num * 7; ++i){
            foreVm.push_back(vmInfoVec[find_vm(it->first, vmInfoVec)]);
        }
    }
}