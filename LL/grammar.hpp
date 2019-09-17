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
    std::string startSymbol;
    std::unordered_set<std::string> Terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string,std::vector<std::vector<std::string>>> pr;
    std::unordered_map<std::string,std::unordered_set<std::string> > firstMap;
    std::unordered_map<std::string,std::unordered_set<std::string>> followMap;
    void _Follow(const std::string &start);
    void _First(const std::string&);

public:
    
    std::unordered_set<std::string> First(const std::string&);
    std::unordered_set<std::string> First(const std::vector<std::string>&);
    std::unordered_set<std::string> Follow(const std::string& start);

    
    LLParser(const std::string &startSymbol_,std::basic_istream<char> &ss,std::unordered_set<std::string> t);
    void PrintAllFollow();
    void PrintAllFirst();
    void PrintTable();
    JSTR::String2Array<std::string> M();
    void TableDriveParser(std::vector<std::string>w);
    
};

#endif /* grammar_hpp */
