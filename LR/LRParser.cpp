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
            if (!i.End()) {
                for(auto j:pr[i.NextExpr()]){
                    LRItem l=LRItem(j,0,pool);
                    if (!J.collection.count(l)) {
                        J.collection.insert(l);
                        n++;
                    }
                }
            }
            
        }
    }while(n!=count);
    return J;
}

void LRCollection::PrintLRC(const LRCollection &c){
    using namespace std;
    cout<<"id:"<<c.collectionId<<endl;
    for(auto i:c.collection){
        string nonTem=i.pool.Get(i.exprId).nonTerminal;
        cout<<nonTem<<" -> ";
        vector<string> v=i.pool.Get(i.exprId).Expr;
        for(size_t j=0;j<v.size();j++){
            if (j==i.pointPosition) {
                cout<<". ";
            }
            cout<<v[j]<<" ";
        }
        if(i.pointPosition==v.size()){
            cout<<".";
        }
        cout<<endl;
    }
    cout<<endl;

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
    
    LRParser lr("E",ss,unordered_set<std::string>{"(",")","+","*","ε","id"});
    LRCollection l1;
    l1.collectionId=1;
    l1.collection.insert(LRItem(lr.pr["E'"][0],0,lr.pool));
    LRCollection l2=lr.Closure(l1);
    LRCollection l3=lr.GOTO(l2, "E");

    lr.Items();
}

void LRParser::Items(){
    
    std::unordered_set<LRCollection,LRCollectionHash> C;
    LRCollection c1=LRCollection();
    c1.collectionId=1;
    c1.collection.insert(LRItem(pr[startSymbol+"'"][0], 0, pool));
    c1=Closure(c1);
    C.insert(c1);
    int count=0;
    int n=0;
    do{
        count=n;
        for(auto I:C){
            for(auto X:Terminals){
                if(!X.compare("ε")){
                    continue;
                }
               // LRCollection::PrintLRC(I);
                LRCollection tmp=GOTO(I, X);
                tmp=Closure(tmp);
              //  LRCollection::PrintLRC(tmp);
                if (tmp.collection.size()!=0&&C.count(tmp)==0) {
                    C.insert(tmp);
                    n++;
                }
            }
            for(auto X:nonTerminals){
           //     LRCollection::PrintLRC(I);
                LRCollection tmp=GOTO(I, X);
                tmp=Closure(tmp);
          //      LRCollection::PrintLRC(tmp);
                if (tmp.collection.size()!=0&&C.count(tmp)==0) {
                    C.insert(tmp);
                    n++;
                }
            }
        }
    }while(n!=count);
    for(auto i:C){
        LRCollection::PrintLRC(i);
    }
}
