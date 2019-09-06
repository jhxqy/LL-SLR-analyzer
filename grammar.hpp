//
//  grammar.hpp
//  LL1
//
//  Created by 贾皓翔 on 2019/9/6.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef grammar_hpp
#define grammar_hpp

#include <stdio.h>
#include <iostream>
#include "StringUtils.hpp"
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
void printPr(std::unordered_map<std::string,std::vector<std::vector<std::string>>> &p);
class LLParser{
    std::unordered_set<std::string> Terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string,std::vector<std::vector<std::string>>> pr;
    
public:
    std::unordered_set<std::string> First(const std::string&);
    LLParser(std::basic_istream<char> &ss,std::unordered_set<std::string> t):Terminals(t){
        std::string tmp;
        while (std::getline(ss,tmp)) {
            if (tmp.empty()) {
                continue;
            }
            if (!tmp.compare("end")) {
                break;
            }
            std::vector<std::string> v;
            JSTR::StringUtils::Split(tmp, v, ' ');
            if (pr.count(v[0])==0) {
                pr[v[0]]=std::vector<std::vector<std::string>>();
                
            }
            nonTerminals.insert(v[0]);
            std::vector<std::string> expr;
            for (int i=2;i<v.size();i++){
                if (!v[i].compare("|")) {
                    pr[v[0]].push_back(expr);
                    expr.clear();
                }else{
                    if (!Terminals.count(v[i])&&!nonTerminals.count(v[i])) {
                        nonTerminals.insert(v[i]);
                    }
                    expr.push_back(v[i]);
                    if (i==v.size()-1) {
                        pr[v[0]].push_back(expr);
                    }
                }
            }

        }
    }
    
};

#endif /* grammar_hpp */
