//
//  CountingMachine.hpp
//  password-mac
//
//  Created by Jungho Lim on 9/15/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#ifndef CountingMachine_h
#define CountingMachine_h

#include <string>

class CountingMachine
{
public:
    CountingMachine();
    ~CountingMachine();
    std::string ReturnStringCountingMachine();
    void ClearCountingMachine();
    void InitializeCountingMachine(const unsigned int startIndex);
    
private:
    unsigned mFirstDigitArray[1];
    unsigned mSecondDigitArray[2];
    unsigned mThirdDigitArray[3];
    unsigned mFourthDigitArray[4];
    unsigned mReturnCounter;
    std::string mToReturn;
};

#endif /* CountingMachine_h */