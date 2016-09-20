// Main.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "Sha1.h"
#include <fstream>
#include "Dictionary.h"


int main(int argc, char* argv[])
{
	//If the user provides a single command argument (argc == 2),
    //program should return SHA-1 hash of the argument
    if(argc == 2)
    {
        unsigned char hash[20];
        char hex_str[41];
    
        //Get the hash value of argv[1]
        sha1::calc(argv[1], strlen(argv[1]), hash);
        //Convert the hash value to hex string
        sha1::toHexString(hash, hex_str);
        
        std::cout << hex_str << std::endl;
    }
    //Invoked if the user provides two command line arguments.
    //First argument: dictionaryFile, Second argument: passwordFile
    else if (argc == 3)
    {
        std::ifstream dictionaryFileInput(argv[1]);
        std::ifstream passwordFileInput(argv[2]);
        
        //Checks for valid input file
        if((!dictionaryFileInput.good()) || (!passwordFileInput.good())) {
            std::cerr << "Passed in arguments are not valid files" << std::endl;
            exit(1);
        }
        
        Dictionary* myDictionary = new Dictionary();
        
        myDictionary->ReadDictionaryFile(dictionaryFileInput);
        
        myDictionary->ReadPasswordFile(passwordFileInput);
        
        
        delete myDictionary;
        
    }
    return 0;
}

