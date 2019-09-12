//
//  LRMain.cpp
//  LL1
//
//  Created by 贾皓翔 on 2019/9/11.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include <stdio.h>
#include "LRParser.hpp"
using namespace std;
struct A{
    int a;
    int b;
    bool operator==(const A&a)const{
        auto h=hash<int>();
        return h(this->a)==h(a.a)&&h(this->b)==h(a.b);
    }
};
struct AHash{
    std::size_t operator()(const A& a)const{
        auto h=hash<int>();
        return h(a.a)+h(a.b);
    }
};

int main(){
    stringstream ss;
    ss<<"S -> S S + | S S * | a"<<endl;
    LRParser lr("S",ss,unordered_set<std::string>{"+","*","a"});
    cout<<1<<endl;

    
}
