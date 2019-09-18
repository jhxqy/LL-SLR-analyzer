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


void LRParser::_First(const std::string&X){
    for(auto i:Terminals){
        
        firstMap[i]=std::unordered_set<std::string>{i};
    }
    for(auto i:nonTerminals){
        for(auto j:pr[i]){
            std::unordered_set<std::string> last{"ε"};
            const std::vector<std::string> &expr=pool.Get(j).Expr;
            if (expr.size()==1&&expr[0].compare("ε")==0){
                if(firstMap.count(i)==0){
                    firstMap[i]=std::unordered_set<std::string>();
                }
                firstMap[i].insert("ε");
            }else{
                for(auto k:expr){
                    if(last.count("ε")){
                        for(auto l:firstMap[k]){
                            firstMap[i].insert(l);
                        }
                    }
                    last=firstMap[k];
                }
            
            }
        }
    }

}

std::unordered_set<std::string> LRParser::First(const std::string &start){
    static bool finish=false;
    if(finish){
        return firstMap[start];
    }
    int count=0,n=0;
    for(auto i:firstMap){
        n+=i.second.size();
    }
    do{
        count=n;
        _First(startSymbol);
        n=0;
        for(auto i:firstMap){
            n+=i.second.size();
        }
    }while(count!=n);
    finish=true;
    return First(start);
}

std::unordered_set<std::string> LRParser::Follow(const std::string &start){
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
        _Follow(startSymbol);
        n=0;
        for(auto i:followMap){
            n+=i.second.size();
        }
    }while(count!=n);
    finish=true;
    return Follow(start);
}
void LRParser::_Follow(const std::string &start){
    if (!followMap.count(start)) {
        followMap.insert(std::make_pair(start,std::unordered_set<std::string>()));
        followMap[start].insert("$");
    }
    for(auto CA:pr){
        for(auto eachCA:CA.second){
            const std::vector<std::string> &v=pool.Get(eachCA).Expr;
            for (int i=0; i<v.size(); i++) {
                if (nonTerminals.count(v[i])) {
                    if (i!=v.size()-1) {
                        for (auto x:First(v[i+1])) {
                            if (x!="ε") {
                                followMap[v[i]].insert(x);
                            }else if(i==v.size()-2){
                                for(auto c:followMap[CA.first]){
                                    followMap[v[i]].insert(c);
                                }
                            }
                        }
                    }else{
                        for(auto c:followMap[CA.first]){
                            followMap[v[i]].insert(c);
                        }
                    }
                    
                }else{
                    
                }
            }
        }
    }
    
    
}


std::unordered_set<LRCollection,LRCollectionHash> LRParser::Items(){
    
    std::unordered_set<LRCollection,LRCollectionHash> C;
    LRCollection c1=LRCollection();
    c1.collection.insert(LRItem(pr[startSymbol+"'"][0], 0, pool));
    c1=Closure(c1);
    c1.collectionId=0;
    C.insert(c1);
    int count=0;
    int n=0;
    int id=c1.collectionId+1;
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
                if (tmp.collection.size()!=0&&C.count(tmp)==0) {
                    tmp.collectionId=id++;
                    C.insert(tmp);
                    n++;
                }
            }
            for(auto X:nonTerminals){
                LRCollection tmp=GOTO(I, X);
                tmp=Closure(tmp);
                if (tmp.collection.size()!=0&&C.count(tmp)==0) {
                    tmp.collectionId=id++;
                    
                    C.insert(tmp);
                    n++;
                }
            }
        }
    }while(n!=count);
    return C;
}

void LRParser::ActionAndGoTo(){
    std::unordered_set<LRCollection,LRCollectionHash> states=Items();
    ActionMap am(Sequence(0, int(states.size()-1)),Terminals);
    GotoMap gm(Sequence(0, int(states.size()-1)),nonTerminals);
    for(auto i:states){
        LRCollection::PrintLRC(i);
    }
    for(LRCollection lrCollection:states){
        std::unordered_set<LRItem,LRItemHash> &collection=lrCollection.collection;
        for(LRItem item:collection){
            GeneratingExpr &e=pool.Get(item.exprId);
            if (!item.End()&&Terminals.count(item.NextExpr())) {
                LRCollection lr=GOTO(lrCollection, item.NextExpr());
                lr=Closure(lr);
                auto existedState=states.find(lr);
                if(existedState!=states.end()){
                    am[lrCollection.collectionId][item.NextExpr()]=ActionStatus(ActionStatus::Action::SHIFT,existedState->collectionId);
                }
            }else if(item.End()&&e.nonTerminal.compare(startSymbol+"'")!=0){
                for(std::string t:Follow(e.Expr[item.pointPosition-1])){
                    am[lrCollection.collectionId][t]=ActionStatus(ActionStatus::Action::REDICE,item.exprId);
                }
            }else if(item.End()&&e.nonTerminal.compare(startSymbol+"'")==0){
                am[lrCollection.collectionId]["$"]=ActionStatus(ActionStatus::Action::ACCEPT);
            }else{
                LRCollection lr=GOTO(lrCollection, item.NextExpr());
                lr=Closure(lr);
                auto existedState=states.find(lr);
                if(existedState!=states.end()){
                    gm[lrCollection.collectionId][item.NextExpr()]=existedState->collectionId;
                }
            }
        }
    }
}
