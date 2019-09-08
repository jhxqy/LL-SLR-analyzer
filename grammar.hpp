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
#include <map>
void printPr(std::unordered_map<std::string,std::vector<std::vector<std::string>>> &p);
class LLParser{
    std::unordered_set<std::string> Terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string,std::vector<std::vector<std::string>>> pr;
    std::unordered_map<std::string,std::unordered_set<std::string> > firstMap;
    std::unordered_map<std::string,std::unordered_set<std::string>> followMap;
    void _Follow(const std::string &start);
    std::unordered_set<std::string> _First(const std::string&,std::unordered_map<std::string,std::unordered_set<std::string> > &m);

public:
    
    std::unordered_set<std::string> First(const std::string&);
    std::unordered_set<std::string> Follow(const std::string& start){
        static bool finish=false;
        if(finish){
            return followMap[start];
        }
        int count=0,n=0;
        for(auto i:followMap){
            n+=i.second.size();
        }
        do{
            count=n;
            _Follow(start);
            n=0;
            for(auto i:followMap){
                n+=i.second.size();
            }
        }while(count!=n);
        finish=true;
        return Follow(start);
    } 

    
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
    void PrintAllFollow();
    void PrintAllFirst();
    
    std::map<std::string,std::map<std::string,std::string>> M();
};

#endif /* grammar_hpp */
