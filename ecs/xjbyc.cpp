#include "xjbyc.h"
#include <string.h>
#include <algorithm>
#include <map>
#include <iostream>
#include <time.h>

using namespace std;

int find_vm(string vmName, std::vector<vm> &vmInfoVec){
    for(unsigned int i = 0; i < vmInfoVec.size(); ++i){
        if(strcmp(vmInfoVec[i].vmName, vmName.c_str()) == 0){
            return i;
        }
    }
    return -1;
}

void data_clean(std::vector<vm_data> &data, vector<time_1s> &rubish, float &day_num){
    time_1s day_s = data[0].time;
    float average_num = 0, count = 0;
    day_num = c_time(data[0].time, data[data.size() - 1].time);
    average_num = data.size() / day_num; 
    for(unsigned int i = 0; i < data.size(); ++i){
        if(!(data[i].time == day_s)){
            if(data[i].time.day - day_s.day > 0 && data[i].time.day - day_s.day > 1){
                day_num -= (data[i].time.day - day_s.day - 1);
            }
            //cout << "count = " << count << endl;
            
            if(count > average_num * 3){
                day_num -= 1;
                cout << "rubish count = " << count << endl;
                rubish.push_back(day_s);
                cout << day_s.year << "-" << day_s.month << "-" << day_s.day << endl;
            }
            
            day_s = data[i].time;
            count = 0;
        }
        count += 1;
    }
}

void xjbyc(std::vector<vm> &foreVm, std::vector<vm_data> &data, std::vector<vm> &vmInfoVec, float day_len){
    float day_num = 0, day_s = data[0].time.day, a0 = 0.2, an = 2.0 - a0, b = 0, ai = 0.1;
    int number = 0;
    map<string, float> foreVmMap;
    vector<time_1s> rubish;
    srand((unsigned) time(NULL));
    data_clean(data, rubish, day_num);
    b = (an - a0) / (day_num - 1);
    for(unsigned int i = 0; i < vmInfoVec.size(); ++i){
        foreVmMap[vmInfoVec[i].vmName] = 0;
    }
    for(unsigned int i = 0; i < data.size(); ++i){
        if(day_s != data[i].time.day){
            day_s = data[i].time.day;
            ai += b;
            //cout << "ai = " << ai << endl;
        }
        if(foreVmMap.find(data[i].vmName) != foreVmMap.end()){
            //cout << data[i].vmName << " " << data[i].time.day << endl;
            if(find(rubish.begin(), rubish.end(), data[i].time) != rubish.end()){
                foreVmMap[data[i].vmName] += (ai * 0.1);
            }else{
                foreVmMap[data[i].vmName] += ai;
            }
        }
    }
    cout << "day_len = " << day_len << endl;
    cout << "day = " << day_num << endl;
    for(map<string, float>::iterator it = foreVmMap.begin(); it != foreVmMap.end(); ++it){
        //cout << it->first << " " << it->second << endl;
        //number = rand() % 5;
        for(int i = 1; i < it->second / day_num * day_len * 2; ++i){
            foreVm.push_back(vmInfoVec[find_vm(it->first, vmInfoVec)]);
        }
    }
}