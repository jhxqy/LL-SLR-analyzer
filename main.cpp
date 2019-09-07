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

// @代替
int main(int argc, const char * argv[]) {
    stringstream ss;

    /*
     RegexList -> Regex RegexList|ε
     Regex     -> term R'
     R'        -> + term R'|ε
     term      -> factor T'
     T'        -> *|ε
     factor    -> (RegexList)|STR|CHAR
     */
    

    /*
    ss<<"RegexList -> Regex RegexList | ε"<<endl;
    ss<<"Regex -> term R'"<<endl;
    ss<<"R' -> + term R' | ε"<<endl;
    ss<<"term -> factor T'"<<endl;
    ss<<"T' -> * | ε"<<endl;
    ss<<"factor -> ( RegexList ) | STR | CHAR"<<endl;
     */
    
    
    /*
     E -> T E'
     E' -> + T E' | ε
     T -> F T'
     T' -> * F T' | ε
     F -> ( E ) | id
     */
    ss<<"E -> T E'"<<endl;
    ss<<"E' -> + T E' | ε"<<endl;
    ss<<"T -> F T'"<<endl;
    ss<<"T' -> * F T' | ε"<<endl;
    ss<<"F -> ( E ) | id"<<endl;
    LLParser ll(ss,unordered_set<string>{"ε","id","(",")","*","+"});
    ll.PrintAllFollow();
    cout<<endl;
    ll.PrintAllFirst();
    
    return 0;
}
