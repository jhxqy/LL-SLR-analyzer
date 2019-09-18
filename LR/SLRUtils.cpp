//
//  SLRUtils.cpp
//  LR
//
//  Created by 贾皓翔 on 2019/9/18.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#include "SLRUtils.hpp"

std::unordered_set<int> Sequence(int from,int to){
    std::unordered_set<int> res;
    for(int i=from;i<=to;i++){
        res.insert(i);
    }
    return res;
}
