//
//  test.cpp
//  LR
//
//  Created by 贾皓翔 on 2019/9/17.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include <stdio.h>
#include "LRParser.hpp"
MyTest::MyTest(){
    using namespace std;
    stringstream ss;
    ss<<"E -> E + T | T"<<endl;
    ss<<"T -> T * F | F"<<endl;
    ss<<"F -> ( E ) | id"<<endl;
    LRParser lr("E",ss,unordered_set<std::string>{"(",")","+","*","ε","id"});
    lr.Parse("id * id + id");
  //  lr.ActionAndGoto();

    
}
