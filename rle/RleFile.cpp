#include "RLEFile.h"
#include "RleData.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "FileSystem.h"


void RleFile::CreateArchive(const std::string& source)
{
    std::ifstream::pos_type size;
    char* memblock; // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        // File data has now been loaded into memblock array
        
        //Call cmpress on the mData member variable.
        mData.Compress(memblock, static_cast<unsigned int>(size));
        
        // Make sure to clean up!
        delete[] memblock;
    }
    // Open the file for output, in binary mode, and overwrite an existing file
    
    mHeader.fileName = source;
    mHeader.sig[0] = 'R';
    mHeader.sig[1] = 'L';
    mHeader.sig[2] = 'E';
    mHeader.sig[3] = 1;
    mHeader.fileSize = static_cast<unsigned int>(size);
    mHeader.fileNameLength = source.length();
    
    
    std::string filename = mHeader.fileName + ".rl1";
    std::ofstream arc(filename, std::ios::out|std::ios::binary|std::ios::trunc);
    if (arc.is_open())
    {
        // Use arc.write function to write data here

        //Writes the file signature
        arc.write(mHeader.sig, 4);

        //Writes the file size
        arc.write(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
        
        //Write the filenameLength
        arc.write(reinterpret_cast<char*>(&(mHeader.fileNameLength)), 1);
        
        //Write the filename
        arc.write(mHeader.fileName.c_str(), mHeader.fileNameLength);
        
        //Write the compressed RLE data
        arc.write(mData.mData, mData.mSize);
    }
}

void RleFile::ExtractArchive(const std::string& source)
{
    //grab the file signature, copy it to mHeader structure.
    //Must check for file signature before further processing.
    //If file signature is not Rl1, reject with an error message saying "it's not a valid archive"
    
    std::ifstream::pos_type size;
    char* memblock; // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        // File data has now been loaded into memblock array
        
        
        //Grabs the file size element.
        mHeader.fileSize = *(reinterpret_cast<int*>(&memblock[4]));

        //Grabs the file name length.
        mHeader.fileNameLength = memblock[8];
        
        int offset = 9  + mHeader.fileNameLength;
        
        //Call cmpress on the mData member variable.
        mData.Decompress(&memblock[offset], static_cast<unsigned int>(size) - offset, mHeader.fileSize);
        
        char* inputFileName = new char[mHeader.fileNameLength + 4];
        for (int i = 0; i < mHeader.fileNameLength; i++) {
            inputFileName[i] = memblock[i + 9];
        }
        mHeader.fileName = inputFileName;
        delete[] memblock;
        delete[] inputFileName;
    }
    
    std::string filename = mHeader.fileName;
    std::ofstream arc(filename, std::ios::out | std::ios::binary | std::ios::trunc); 
    if (arc.is_open())
    {
        arc.write(mData.mData, mData.mSize);
    }


}
