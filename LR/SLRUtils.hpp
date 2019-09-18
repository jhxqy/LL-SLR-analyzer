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
#include <iostream>
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
    operator std::string(){
        std::string res;
        switch(a){
            case Action::ACCEPT:
                res.append("AC");
                break;
            case Action::SHIFT:
                res.append("S");
                res.append(std::to_string(shiftTo));
                break;
            case Action::REDICE:
                res.append("R");
                res.append(std::to_string(exprID));
                break;
            case Action::ERROR:
                res.append("");
                break;
        }
        return res;
    }
    
};
template <typename T>
struct PrintTrait{
    using Type=T;
};

template<>
struct PrintTrait<ActionStatus>{
    using Type=std::string;
};

template<typename T1,typename T2,typename Value>
class TwoDArray{
    std::unordered_set<T1> key1s_;
    std::unordered_set<T2> key2s_;
    std::unordered_map<T1, std::unordered_map<T2,Value>> data;
public:
    const std::unordered_set<T1>& Key1s()const{
        return key1s_;
    }
    const std::unordered_set<T2>& Key2s()const{
        return key2s_;
    }
    TwoDArray(const std::unordered_set<T1> &first,const std::unordered_set<T2> &second):key1s_(first),key2s_(second){
        for(auto i:first){
            for(auto j:second){
                data[i][j]=Value();
            }
        }
    }
    std::unordered_map<T2,Value>& operator[](const T1 &first){
        return data[first];
    }
    void printTable(){
        using namespace std;
        cout<<"| |";
        for(auto i:Key2s()){
            cout<<" "<<i<<"|";
        }
        cout<<endl;
        for(int i=0;i<Key2s().size()+1;i++){
            cout<<"---|";
        }
        cout<<endl;
        for(auto i:Key1s()){
            cout<<i<<"|";
            for(auto j:Key2s()){
                cout<<(typename PrintTrait<Value>::Type)(data[i][j])<<"| ";
            }
            cout<<endl;
        }
        
    }
};

using ActionMap=TwoDArray<int, std::string, ActionStatus>;
using GotoMap=TwoDArray<int, std::string, int>;


std::unordered_set<int> Sequence(int from,int to);

#endif /* SLRUtils_hpp */
