//
//  grammar.cpp
//  LL1
//
//  Created by 贾皓翔 on 2019/9/6.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include "grammar.hpp"
void printPr(std::unordered_map<std::string,std::vector<std::vector<std::string>>> &p){
    using namespace std;
    for(auto expr:p){
        for(auto chansheng :expr.second){
            cout<<expr.first<<" ->";
            for(auto str:chansheng){
                cout<<str<<" ";
            }
            cout<<endl;
        }
    }
}

std::unordered_set<std::string> LLParser::_First(const std::string &a,std::unordered_map<std::string,std::unordered_set<std::string> > &m){
    std::unordered_set<std::string> ret;
    if (m.count(a)) {
        return m[a];
    }
    if (Terminals.count(a)) {
        ret.insert(a);
        if (!m.count(a)) {
            m.insert(std::make_pair(a,ret));
        }
        return ret;
    }
    for(auto i:pr[a]){  //遍历每个产生式
        bool add=true;

        if (i.size()==1&&!i[0].compare("ε")) {
            ret.insert("ε");
        }
        for(auto j:i){
            std::unordered_set<std::string> n;
            if (add) {
                n=_First(j,m);
                
                if (!n.count("ε")) {
                    add=false;
                }
                for(auto k=n.begin();k!=n.end();k++){
                    ret.insert(*k);
                }
            }else{
                
            }
        }

    }
    if (!m.count(a)) {
        m.insert(std::make_pair(a,ret));
    }
    return ret;
} 

std::unordered_set<std::string> LLParser::First(const std::string& a){
    
    auto i=_First(a,firstMap);
    return i;
}


void LLParser::_Follow(const std::string &start){
    if (!followMap.count(start)) {
        followMap.insert(std::make_pair(start,std::unordered_set<std::string>()));
        followMap[start].insert("$");
    }
    
    for(auto CA:pr){
        for(auto eachCA:CA.second){
            for (int i=0; i<eachCA.size(); i++) {
                if (nonTerminals.count(eachCA[i])) {
                    if (i!=eachCA.size()-1) {
                        for (auto x:First(eachCA[i+1])) {
                            if (x!="ε") {
                                followMap[eachCA[i]].insert(x);
                            }else if(i==eachCA.size()-2){
                                for(auto c:followMap[CA.first]){
                                    followMap[eachCA[i]].insert(c);
                                }
                            }
                        }
                    }else{
                        for(auto c:followMap[CA.first]){
                            followMap[eachCA[i]].insert(c);
                        }
                    }
                    
                }else{
                    
                }
            }
        }
    }
    
}
void LLParser::PrintAllFollow(){
    for(auto i:nonTerminals){
        std::cout<<i<<":";
        for(auto j:Follow(i)){
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }
}

void LLParser::PrintAllFirst(){
    for(auto i:nonTerminals){
        std::cout<<i<<":";
        for(auto j:First(i)){
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }
}
