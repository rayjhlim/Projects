//
//  Dictionary.cpp
//  password-mac
//
//  Created by Jungho Lim on 9/13/16.
//  Copyright © 2016 Sanjay. All rights reserved.
//

#include "Dictionary.h"


Dictionary::Dictionary()
{
}

Dictionary::~Dictionary()
{
    
}

//Load dictionary into hash map
void Dictionary::ReadDictionaryFile(std::ifstream &fileStream)
{
    std::string originalPassword;
    std::string hashResult;
    unsigned char hash[20];
    char hex_str[41];
    
    //rehash the unordered map to 100,000
    mHashPasswordMap.rehash(100000);
    
    //Times the time taken to load dictionary into hash map
    Timer timer;
    timer.start();
    
    while(std::getline(fileStream, originalPassword))
    {
        //Get the hash value of originalPassword
        sha1::calc(originalPassword.c_str(), originalPassword.size(), hash);
        
        //Convert the hash value to hex string
        sha1::toHexString(hash, hex_str);
        
        hashResult = hex_str;
        
        //Store the hash and password pair into vector
        std::pair<std::string, std::string> hashPasswordPair(hashResult, originalPassword);
        
        mHashPasswordMap.insert(hashPasswordPair);
        
    }
    
    double elapsed = timer.getElapsed();
    std::cout << "Number of seconds taken to load dictionary into hash map: " << elapsed << std::endl;
}

//Read in the Password File and attempt to figure out the password
void Dictionary::ReadPasswordFile(std::ifstream &fileStream)
{
    unsigned passwordIndex = 0;
    std::string hashOfPassword;
    std::string unsolvedPasswordString;
    std::unordered_map<std::string,std::string>::const_iterator mapIterator;
    std::map<unsigned,std::vector<std::tuple<unsigned,std::string,std::string>>*> solvedPassword;
    std::pair<unsigned,std::vector<std::tuple<unsigned,std::string,std::string>>*> indexVectorPointerPair;
    
    std::ofstream outputFile("pass_solved.txt");
    std::string unsolvedPasswordHashed;
    
    while(std::getline(fileStream, hashOfPassword))
    {
        mapIterator = mHashPasswordMap.find(hashOfPassword);
        
        
        //Output original hexadecimal hash, followed by a comma,
        //followed by the plain text password if password is found in the dictionary
        //Output a couple of question marks if failed to find password in the dictionary
        
        if(mapIterator == mHashPasswordMap.end())
        {
            mDecryptedInformation.push_back(std::make_tuple(passwordIndex, hashOfPassword, "??"));
            mUnsolvedPassword.push_back(std::make_pair(passwordIndex, hashOfPassword));
        }
        else
        {
            mDecryptedInformation.push_back(std::make_tuple(passwordIndex, hashOfPassword, mapIterator->second));
            
            indexVectorPointerPair = std::pair<unsigned,std::vector<std::tuple<unsigned,std::string,std::string>>*>(passwordIndex, &mDecryptedInformation);
            
            solvedPassword.insert(indexVectorPointerPair);
        }
        
        passwordIndex++;
    }
    
    //Times the brute force method
    Timer timer;
    timer.start();
    
    //Go through each vector element and use 9 lambda expressions with different
    //range to brute force.
    for(unsigned int i = 0; i < mUnsolvedPassword.size(); i++)
    {
        tbb::parallel_invoke
        (
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 0, 191956, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 191957, 383913, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 383913, 575870, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 575871, 767827, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 767828, 959785, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 959786, 1151701, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 1151702, 1343658, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 1343659, 1535615, i); },
         [&, this]() { BruteForceHelper(mUnsolvedPassword[i].second, 1535616, 1727604, i); }
        );
    }
    
    double elapsed = timer.getElapsed();
    std::cout << "Number of seconds taken to brute force: " << elapsed << std::endl;
    
    //Outputs the final result to pass_solved.txt
    auto decryptedInformatinIterator = mDecryptedInformation.begin();
    while(decryptedInformatinIterator != mDecryptedInformation.end())
    {
        outputFile << std::get<1>(*decryptedInformatinIterator) << "," << std::get<2>(*decryptedInformatinIterator) << "\n";
        ++decryptedInformatinIterator;
    }
    
    outputFile.close();
}

//Brute Force method
void Dictionary::BruteForceHelper(const std::string unsolvedPasswordString, const unsigned int startIndex, const unsigned int endIndex, const unsigned int vectorIndex)
{
    
    char hex_str[41];
    unsigned char hash[20];
    //Construct CountingMachine
    CountingMachine mCountingMachine;
    
    std::string testUnsolvedPassword;

    //Initialize the Counting Machine based on the input
    mCountingMachine.InitializeCountingMachine(startIndex);
    
    //Iterate over unsolvedPassword and brute force each element through the given index
    for(unsigned int i = 0; i < endIndex - startIndex + 1; i++)
    {
        testUnsolvedPassword = mCountingMachine.ReturnStringCountingMachine();
        sha1::calc(testUnsolvedPassword.c_str(), testUnsolvedPassword.size(), hash);
        sha1::toHexString(hash, hex_str);
        if(hex_str == unsolvedPasswordString)
        {
            std::get<2>(mDecryptedInformation[mUnsolvedPassword[vectorIndex].first]) = testUnsolvedPassword;
            break;
        }
    }
}