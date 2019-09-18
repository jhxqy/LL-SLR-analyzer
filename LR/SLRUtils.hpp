//
//  SLRUtils.hpp
//  LR
//
//  Created by 贾皓翔 on 2019/9/18.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef SLRUtils_hpp
#define SLRUtils_hpp
#include <string>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
struct ActionStatus{
    enum class Action{
        ACCEPT,SHIFT,REDICE,ERROR
    };
    Action a;
    int shiftTo;
    int exprID;
    ActionStatus(Action aa,int st):a(aa){
        if(aa==Action::SHIFT){
            shiftTo=st;
        }else if(aa==Action::REDICE){
            exprID=st;
        }
    } 

    ActionStatus(Action aa):a(aa){
    }
    ActionStatus():a(Action::ERROR){}
    
};
template<typename T1,typename T2,typename Value>
class TwoDArray{
    std::unordered_map<T1, std::unordered_map<T2,Value>> data;
public:
    TwoDArray(const std::unordered_set<T1> &first,const std::unordered_set<T2> &second){
        for(auto i:first){
            for(auto j:second){
                data[i][j]=Value();
            }
        }
    }
    std::unordered_map<T2,Value>& operator[](const T1 &first){
        return data[first];
    }
};

using ActionMap=TwoDArray<int, std::string, ActionStatus>;
using GotoMap=TwoDArray<int, std::string, int>;


std::unordered_set<int> Sequence(int from,int to);

#endif /* SLRUtils_hpp */
