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
