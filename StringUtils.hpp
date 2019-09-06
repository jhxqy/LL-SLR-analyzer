//
//  StringUtils.hpp
//  StringUtils
//
//  Created by 贾皓翔 on 2019/9/3.
//  Copyright © 2019 贾皓翔. All rights reserved.
//

#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <set>
#include <unordered_set>
namespace JSTR {
    class StringUtils{
    public:
        template<typename Container>
        static void Split(const std::string &s,Container &container,char c){
            std::stringstream ss(s);
            std::string item;
            while (std::getline(ss,item, c)) {
                container.emplace_back(item);
            }
        }
        static void Split(const std::string &s,std::set<std::string> &container,char c);
        static void Split(const std::string &s,std::unordered_set<std::string> &container,char c);
        
        static std::string Trim(const std::string &s);
        static std::string TrimStart(const std::string &s);
        static std::string TrimEnd(const std::string &s);
        static bool StartsWith(const std::string &s1,const std::string &s2);
        static bool EndsWith(const std::string &str,const std::string &suffix);
    };
    
    
}

#endif /* StringUtils_hpp */
