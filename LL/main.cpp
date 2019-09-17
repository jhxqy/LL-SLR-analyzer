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
//    ss<<"RegexList -> Regex RegexList | ε"<<endl;
//    ss<<"Regex -> term R'"<<endl;
//    ss<<"R' -> + term R' | ε"<<endl;
//    ss<<"term -> factor T'"<<endl;
//    ss<<"T' -> * | ε"<<endl;
//    ss<<"factor -> ( RegexList ) | STR | CHAR"<<endl;
//
    /*
     E -> T E'
     E' -> + T E' | ε
     T -> F T'
     T' -> * F T' | ε
     F -> ( E ) | id
     */
//    ss<<"E -> T E'"<<endl;
//    ss<<"E' -> + T E' | ε"<<endl;
//    ss<<"T -> F T'"<<endl;
//    ss<<"T' -> * F T' | ε"<<endl;
//    ss<<"F -> ( E ) | id"<<endl;
/*
    S -> array | object
    array -> [ values ]
    object -> { members }
    values -> non-empty-values | ε
    non-empty-values -> value addition-values
    addition-values -> ε | , non-empty-values
    members -> non-empty-members | ε
    non-empty-members -> member addition-members
    addition-members -> ε | , non-empty-members
    member -> STRING : value
    value -> STRING | NUMBER | NULL | BOOLEAN | object | array
*/
    ss<<"S -> array | object"<<endl;
    ss<<"array -> [ values ]"<<endl;
    ss<<"values -> non-empty-values | ε"<<endl;
    ss<<"object -> { members }"<<endl;
    ss<<"non-empty-values -> value addition-values"<<endl;
    ss<<"addition-values -> ε | , non-empty-values"<<endl;
    ss<<"members -> non-empty-members | ε"<<endl;
    ss<<"non-empty-members -> member addition-members"<<endl;
    ss<<"addition-members -> ε | , non-empty-members"<<endl;
    ss<<"member -> STRING : value"<<endl;
    ss<<"value -> STRING | NUMBER | NULL | BOOLEAN | object | array"<<endl;

    LLParser ll("S",ss,unordered_set<string>{"ε","[","]","{","}",",",":","STRING","NUMBER","NULL","BOOLEAN",});
//    LLParser ll("E",ss,unordered_set<string>{"ε","+","*","(",")","id"});
//    LLParser ll("RegexList",ss,unordered_set<string>{"ε","+","*","(",")","STR","CHAR"});
    ll.PrintAllFollow();
    cout<<endl;
    ll.PrintAllFirst();
    cout<<endl;
    ll.PrintTable();
    auto i=ll.M();
    vector<string> v;
//    JSTR::StringUtils::Split("id + id * id $", v, ' ');
//    ll.PrintTable();
//    ll.TableDriveParser(v);
    
    
    
    
//    ss<<"stmt -> if e then stmt stmtTail | where e do stmt | begin list end | s"<<endl;
//    ss<<"stmtTail -> else stmt | ε"<<endl;
//    ss<<"list -> stmt listTail"<<endl;
//    ss<<"listTail -> ; list | ε"<<endl;
//
//    LLParser ll("stmt", ss, unordered_set<string>{"ε","if","then","e","s","while","do","begin","end","else",";"});
//    vector<string> v;
//    JSTR::StringUtils::Split("if e then s ; if e then s end", v, ' ');
//    ll.TableDriveParser(v);
//
//    ll.PrintTable();
//
    
//    ss<<"S -> L S R S | ε"<<endl;
//    ss<<"L -> ( | E"<<endl;
//    ss<<"R -> ) | E"<<endl;
//    ss<<"E -> * | ε"<<endl;
//    LLParser ll("S",ss,unordered_set<string>{"(",")","*","ε"});
//    ll.PrintTable();
    
    return 0;
}
