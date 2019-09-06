//
//  main.cpp
//  LL1
//
//  Created by 贾皓翔 on 2019/9/4.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include <iostream>
#include "StringUtils.hpp"
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include "grammar.hpp"
using namespace std;
using namespace JSTR;

unordered_set<string> Terminals{"ε","a","b","c","d"};
unordered_set<string> nonTerminals;

unordered_map<std::string,vector<vector<string>>> pr;

// @代替
int main(int argc, const char * argv[]) {
//    cout<<"请输入终结符号,结束输入end:"<<endl;
//    while (cin>>tmp) {
//        if (!tmp.compare("end")) {
//            break;
//        }
//        if (Terminals.count(tmp)<1) {
//            Terminals.insert(std::move(tmp));
//        }
//    }
    //    string tmp;
//
//    cout<<"请输入生成式,结束输入end:"<<endl;
//    while (getline(cin,tmp)) {
//        if (tmp.empty()) {
//            continue;
//        }
//        if (!tmp.compare("end")) {
//            break;
//        }
//        vector<string> v;
//        StringUtils::Split(tmp, v, ' ');
//        if (pr.count(v[0])==0) {
//            pr[v[0]]=vector<vector<string>>();
//
//        }
//        nonTerminals.insert(v[0]);
//        vector<string> expr;
//        for (int i=2;i<v.size();i++){
//            if (!v[i].compare("|")) {
//                pr[v[0]].push_back(expr);
//                expr.clear();
//            }else{
//                if (!Terminals.count(v[i])&&!nonTerminals.count(v[i])) {
//                    nonTerminals.insert(v[i]);
//                }
//                expr.push_back(v[i]);
//                if (i==v.size()-1) {
//                    pr[v[0]].push_back(expr);
//                }
//            }
//        }
//    }
    LLParser ll(cin,Terminals);
    
    return 0;
}
