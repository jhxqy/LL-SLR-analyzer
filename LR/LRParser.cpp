//
//  LRParser.cpp
//  LL1
//
//  Created by 贾皓翔 on 2019/9/11.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include "LRParser.hpp"

GeneratingExprPool::GeneratingExprPool(){}


GeneratingExprPool::~GeneratingExprPool(){
    for(auto i:data){
        delete i.second;
    }
}
int GeneratingExprPool::id_=0;

int GeneratingExprPool::CreateExpr(const std::string &nonTerminal, std::vector<std::string> expr){
    auto *p=new GeneratingExpr(nonTerminal,expr);
    int id=id_++;
    data.insert(std::make_pair(id,p));
    return id;
}

GeneratingExpr& GeneratingExprPool::Get(int id){
    return  *(data[id]);
}

LRItem::LRItem(int e,int p,GeneratingExprPool &po):exprId(e),pointPosition(p),pool(po){
    
}
bool LRItem::operator==(const LRItem& a) const{
    return exprId==a.exprId&&pointPosition==a.pointPosition;
}
std::size_t LRItemHash::operator()(const LRItem &a) const{ 
    auto h=std::hash<int>();
    return h(a.exprId)^(h(a.pointPosition)<<2);
    
}

LRCollection LRParser::Closure(const LRCollection &I){
    
    LRCollection J=I;
    J.collectionId=I.collectionId+1;
    int count=0;
    int n=0;
    do{
        n=count;
        for(auto i:J.collection){
            for(auto j:pr[i.NextExpr()]){
                LRItem l=LRItem(j,0,pool);
                if (!J.collection.count(l)) {
                    J.collection.insert(l);
                    n++;
                }
            }
        }
    }while(n!=count);
    return J;
}



LRParser::LRParser(const std::string &startSymbol_,std::basic_istream<char> &ss,std::unordered_set<std::string> t):startSymbol(startSymbol_),Terminals(t){
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
            pr[v[0]]=std::vector<int>();
            
        }
        nonTerminals.insert(v[0]);
        std::vector<std::string> expr;
        for (int i=2;i<v.size();i++){
            if (!v[i].compare("|")) {
                pr[v[0]].push_back(pool.CreateExpr(v[0], expr));
                expr.clear();
            }else{
                if (!Terminals.count(v[i])&&!nonTerminals.count(v[i])) {
                    nonTerminals.insert(v[i]);
                }
                expr.push_back(v[i]);
                if (i==v.size()-1) {
                    pr[v[0]].push_back(pool.CreateExpr(v[0], expr));
                }
            }
        }
        
    }
    
    pr[startSymbol_+"'"].push_back(pool.CreateExpr(startSymbol_+"'", std::vector<std::string>{startSymbol_}));
}

LRCollection LRParser::GOTO(const LRCollection &I,const std::string &X){
    LRCollection J;
    J.collectionId=I.collectionId+1;
    for(auto i:I.collection){
        if(!i.End()&&i.NextExpr().compare(X)==0){
            LRItem item(i.exprId,i.pointPosition+1,i.pool);
            J.collection.insert(item);
        }
    }
    return J;
}

MyTest::MyTest(){
    using namespace std;
    stringstream ss;
    ss<<"E -> E + T | T"<<endl;
    ss<<"T -> T * F | F"<<endl;
    ss<<"F -> ( E ) | id"<<endl;
    
    LRParser lr("E",ss,unordered_set<std::string>{"(",")","+","*","ε"});
    LRCollection l1;
    l1.collectionId=1;
    l1.collection.insert(LRItem(lr.pr["E'"][0],0,lr.pool));
    LRCollection l2=lr.Closure(l1);
    LRCollection l3=lr.GOTO(l2, "E");
    
    cout<<"helloworld"<<endl;
    
}
