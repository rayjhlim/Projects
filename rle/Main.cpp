// Main.cpp : Defines the entry point for the console application.
//

#include "RleTests.h"
#include "RleData.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "RLEFile.h"

void Part1Tests()
{
	TestFixtureFactory::theInstance().runTests();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		// Just the tests
		Part1Tests();
	}
	else
	{
        RleFile inputRleFile;
        //If the file ends in .rl1, decompress. Else, compress.
        std::string filename = argv[1];
        std::size_t rl1Found = filename.find_last_of(".");
        if(filename.substr(rl1Found + 1) == "rl1") {
            inputRleFile.ExtractArchive(filename);
        }
        else {
            inputRleFile.CreateArchive(filename);
        }
	}
	return 0;
}

