//
//  LRParser.hpp
//  LL1
//
//  Created by 贾皓翔 on 2019/9/11.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef LRParser_hpp
#define LRParser_hpp
#include <stdio.h>
#include <iostream>
#include "StringUtils.hpp"
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
class LRParser{
    std::string startSymbol;
    std::unordered_set<std::string> Terminals;
    std::unordered_set<std::string> nonTerminals;
    std::unordered_map<std::string,std::vector<std::vector<std::string>>> pr;
public:
      LRParser(const std::string &startSymbol_,std::basic_istream<char> &ss,std::unordered_set<std::string> t);
    
};



#endif /* LRParser_hpp */
