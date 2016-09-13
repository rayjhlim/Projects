#include "RleData.h"
#include <iostream>

void RleData::Compress(const char* input, size_t inSize)
{
    /** Delete mData and set mSize back to 0 because if
     *  compress is called multiple times, all previous data should be wiped.
     */
    delete[] this->mData;
    this->mSize = 0;
    
    /** Allocate memory for mData (where we store compressed data).
    *   It is allocated twice the size of inSize*/
    this->mData = new char[inSize * 2];
    
    
    /** A bool array that is true if the current element in the input char array
     *  equals the previous element
     */
    bool* consecutiveCharacterCheck = new bool [inSize];
    
    
    //Keeps track of number of consecutive elements encountered.
    int consecutiveCounter = 0;
    
    //Initialize the first element to false.
    consecutiveCharacterCheck[0] = false;
    //Loop through input char array and fill the consecutiveCharacterCheck array
    for(int i = 1; i < inSize; ++i) {
        if(input[i] == input[i -1]) {
            consecutiveCharacterCheck[i] = true;
        }
        else {
            consecutiveCharacterCheck[i] = false;
        }
    }
    
    /** Loops through the input array and the consecutiveCharacter check array
     *  and use bunch of if/else statements to appropriately fill the mData array
     */
     
    for(int i = 0; i < inSize; i++) {
        if(consecutiveCharacterCheck[i]) {
            if(!consecutiveCharacterCheck[i - 1]) {
                if(consecutiveCounter > 1) {
                    if(consecutiveCounter == 2) {
                        mData[mSize] = consecutiveCounter - 1;
                    }
                    else {
                        mData[mSize] = -(consecutiveCounter - 1);
                    }
                    mSize++;
                    for (int j = i - consecutiveCounter; j < i - 1; j++) {
                        mData[mSize] = input[j];
                        mSize++;
                    }
                }
                mData[mSize] = 2;
                mSize++;
                mData[mSize] = input[i];
                mSize++;
            }
            else if(mData[mSize - 2] < MaxRunSize()) {
                mData[mSize - 2] += 1;
            }
            else {
                mData[mSize] = 1;
                mSize++;
                mData[mSize] = input[i];
                mSize++;
            }
            consecutiveCounter = 0;
        }
        else {
            if(consecutiveCounter == MaxRunSize()) {
                mData[mSize] = -MaxRunSize();
                mSize++;
                for(unsigned long j = i - MaxRunSize(); j < i; j++) {
                    mData[mSize] = input[j];
                    mSize++;
                }
                
                if(i == inSize - 1) {
                    mData[mSize] = 1;
                    mSize++;
                    mData[mSize] = input[i];
                    mSize++;
                }
                consecutiveCounter = 1;
            }
            else if(i == inSize - 1) {
                if(consecutiveCounter > 1) {
                    mData[mSize] = -(consecutiveCounter + 1);
                    mSize++;
                    for(int j = i - consecutiveCounter; j < i + 1; j++) {
                        mData[mSize] = input[j];
                        mSize++;
                    }
                }
                else {
                        mData[mSize] = 1;
                        mSize++;
                        mData[mSize] = input[i];
                        mSize++;
                }
            }
            else {
                consecutiveCounter++;
            }
        }
    }
    
    //Outputs compression rate percentage
    std::cout << "COMPRESSION: " << ((double) mSize/inSize ) * 100 << "%" << std::endl;

    delete [] consecutiveCharacterCheck;
    
}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
    /** Delete mData and set mSize back to 0 because if
     *  compress is called multiple times, all previous data should be wiped.
     */
    delete[] this->mData;
    this->mSize = 0;
    
    /** Allocate memory for mData (where we store compressed data).
     *   It is allocated twice the size of inSize*/
    this->mData = new char[outSize];
        
    //Initialize variables to iterate the input and mData vector to 0
    unsigned long inputIterator = 0;

    while(inputIterator < inSize) {
        char elementCount = input[inputIterator];
        
        inputIterator++;
        //Positive run
        if(elementCount > 0) {
            for(int i = 0; i < elementCount; i++) {
                mData[mSize] = input[inputIterator];
                mSize++;
            }
            inputIterator++;
        }
        //Negative Run
        else {
            for(int i = 0; i < -(elementCount); i++) {
                mData[mSize] = input[inputIterator];
                mSize++;
                inputIterator++;
            }
        }
    }
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}