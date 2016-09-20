//
//  Dictionary.cpp
//  password-mac
//
//  Created by Jungho Lim on 9/13/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//
#include "CountingMachine.h"
#include "Sha1.h"
#include "Timer.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <tbb/parallel_invoke.h>
#include <iostream>


class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    void ReadDictionaryFile(std::ifstream& fileStream);
    void ReadPasswordFile(std::ifstream& fileStream);
    void BruteForceHelper(const std::string unsolvedPassword, const unsigned int startIndex, const unsigned int endIndex, const unsigned int vectorIndex);
    
private:
    std::unordered_map<std::string,std::string> mHashPasswordMap;
    std::vector<std::tuple<unsigned,std::string,std::string>> mDecryptedInformation;
    std::vector<std::pair<unsigned,std::string>> mUnsolvedPassword;
};