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
#include <map>
#include <unordered_map>
#include <unordered_set>
namespace JSTR {
    template<typename T>
    class String2Array{
        std::unordered_set<std::string> key1s;
        std::unordered_set<std::string> key2s;
        std::unordered_map<std::string,std::unordered_map<std::string, T>>data;
    public:
        template<typename E>
        String2Array(const E &e1,const E &e2){
            for(auto i:e2){
                key2s.insert(i);
            }
            for(auto i:e1){
                key1s.insert(i);
                std::unordered_map<std::string, T> m2;
                for(auto j:e2){
                    m2.insert(std::make_pair(j, ""));
                }
                data.insert(std::make_pair(i, m2));
            }
        }
        std::unordered_map<std::string, T>& operator[](const std::string &key){
            return data[key];
        }
        std::unordered_set<std::string> Key1s(){
            return key1s;
        }
        std::unordered_set<std::string> Key2s(){
            return key2s;
        }
        
    };
    
    
    
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
