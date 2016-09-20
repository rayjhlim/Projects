//
//  CountingMachine.cpp
//  password-mac
//
//  Created by Jungho Lim on 9/15/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "CountingMachine.h"

CountingMachine::CountingMachine()
{
    mFirstDigitArray[0] = 0;
    mSecondDigitArray[0] = 0;
    mSecondDigitArray[1] = 0;
    mThirdDigitArray[0] = 0;
    mThirdDigitArray[1] = 0;
    mThirdDigitArray[2] = 0;
    mFourthDigitArray[0] = 0;
    mFourthDigitArray[1] = 0;
    mFourthDigitArray[2] = 0;
    mFourthDigitArray[3] = 0;
    
    mReturnCounter = 0;
}

CountingMachine::~CountingMachine()
{

}

void CountingMachine::ClearCountingMachine()
{
    mFirstDigitArray[0] = 0;
    mSecondDigitArray[0] = 0;
    mSecondDigitArray[1] = 0;
    mThirdDigitArray[0] = 0;
    mThirdDigitArray[1] = 0;
    mThirdDigitArray[2] = 0;
    mFourthDigitArray[0] = 0;
    mFourthDigitArray[1] = 0;
    mFourthDigitArray[2] = 0;
    mFourthDigitArray[3] = 0;
    
    mReturnCounter = 0;
}

//Set the member Arrays accordingly given beginIndex
void CountingMachine::InitializeCountingMachine(const unsigned int beginIndex)
{
    if(beginIndex == 0)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 0;
        mFourthDigitArray[1] = 0;
        mFourthDigitArray[2] = 0;
        mFourthDigitArray[3] = 0;
    }
    else if(beginIndex == 191957)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 5;
        mFourthDigitArray[1] = 3;
        mFourthDigitArray[2] = 3;
        mFourthDigitArray[3] = 3;
    }
    else if(beginIndex == 383913)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 9;
        mFourthDigitArray[1] = 7;
        mFourthDigitArray[2] = 7;
        mFourthDigitArray[3] = 7;
    }
    else if(beginIndex == 575871)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 15;
        mFourthDigitArray[1] = 11;
        mFourthDigitArray[2] = 11;
        mFourthDigitArray[3] = 11;
    }
    else if(beginIndex == 767828)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 20;
        mFourthDigitArray[1] = 15;
        mFourthDigitArray[2] = 15;
        mFourthDigitArray[3] = 15;
    }
    else if(beginIndex == 959786)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 26;
        mFourthDigitArray[1] = 19;
        mFourthDigitArray[2] = 19;
        mFourthDigitArray[3] = 19;
    }
    else if(beginIndex == 1151702)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 26;
        mFourthDigitArray[1] = 22;
        mFourthDigitArray[2] = 23;
        mFourthDigitArray[3] = 23;
    }
    else if(beginIndex == 1343659)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 31;
        mFourthDigitArray[1] = 26;
        mFourthDigitArray[2] = 27;
        mFourthDigitArray[3] = 27;
    }
    else if(beginIndex == 1535616)
    {
        mFirstDigitArray[0] = 0;
        mSecondDigitArray[0] = 0;
        mSecondDigitArray[1] = 0;
        mThirdDigitArray[0] = 0;
        mThirdDigitArray[1] = 0;
        mThirdDigitArray[2] = 0;
        mFourthDigitArray[0] = 0;
        mFourthDigitArray[1] = 31;
        mFourthDigitArray[2] = 31;
        mFourthDigitArray[3] = 31;
    }
    mReturnCounter = beginIndex;
}


//Return the appropriate string value the member arrays signify.
//and increment the counter.
std::string CountingMachine::ReturnStringCountingMachine()
{
    if(mReturnCounter < 36)
    {
        if(mFirstDigitArray[0] < 26)
        {
            mToReturn = 'a' + mFirstDigitArray[0];
        }
        else
        {
            mToReturn = '0' + mFirstDigitArray[0] - 26;
        }
        mFirstDigitArray[0]++;
    }
    else if(mReturnCounter < 1332)
    {
        if(mSecondDigitArray[1] < 26)
        {
            mToReturn = 'a' + mSecondDigitArray[1];
        }
        else
        {
            mToReturn = '0' + mSecondDigitArray[1] - 26;
        }
    
        if(mSecondDigitArray[0] < 26)
        {
            mToReturn += 'a' + mSecondDigitArray[0];
        }
        else
        {
            mToReturn += '0' + mSecondDigitArray[0] - 26;
        }
        
        if(mSecondDigitArray[0] == 35)
        {
            mSecondDigitArray[0] = 0;
            mSecondDigitArray[1]++;
        }
        else
        {
            mSecondDigitArray[0]++;
        }
    }
    else if(mReturnCounter < 47988)
    {
        if(mThirdDigitArray[2] < 26)
        {
            mToReturn = 'a' + mThirdDigitArray[2];
        }
        else
        {
            mToReturn = '0' + mThirdDigitArray[2] - 26;
        }
        
        if(mThirdDigitArray[1] < 26)
        {
            mToReturn += 'a' + mThirdDigitArray[1];
        }
        else
        {
            mToReturn += '0' + mThirdDigitArray[1] - 26;
        }
        
        if(mThirdDigitArray[0] < 26)
        {
            mToReturn += 'a' + mThirdDigitArray[0];
        }
        else
        {
            mToReturn += '0' + mThirdDigitArray[0] - 26;
        }
        
        if(mThirdDigitArray[0] == 35)
        {
            if(mThirdDigitArray[1] == 35)
            {
                mThirdDigitArray[0] = 0;
                mThirdDigitArray[1] = 0;
                mThirdDigitArray[2]++;
            }
            else
            {
                mThirdDigitArray[0] = 0;
                mThirdDigitArray[1]++;
            }
        }
        else
        {
            mThirdDigitArray[0]++;
        }
    }
    else if(mReturnCounter < 1727604)
    {
        if(mFourthDigitArray[3] < 26)
        {
            mToReturn = 'a' + mFourthDigitArray[3];
        }
        else
        {
            mToReturn = '0' + mFourthDigitArray[3] - 26;
        }
        
        if(mFourthDigitArray[2] < 26)
        {
            mToReturn += 'a' + mFourthDigitArray[2];
        }
        else
        {
            mToReturn += '0' + mFourthDigitArray[2] - 26;
        }

        if(mFourthDigitArray[1] < 26)
        {
            mToReturn += 'a' + mFourthDigitArray[1];
        }
        else
        {
            mToReturn += '0' + mFourthDigitArray[1] - 26;
        }
        
        if(mFourthDigitArray[0] < 26)
        {
            mToReturn += 'a' + mFourthDigitArray[0];
        }
        else
        {
            mToReturn += '0' + mFourthDigitArray[0] - 26;
        }
        
        if(mFourthDigitArray[0] == 35)
        {
            if(mFourthDigitArray[1] == 35)
            {
                if(mFourthDigitArray[2] == 35)
                {
                    mFourthDigitArray[0] = 0;
                    mFourthDigitArray[1] = 0;
                    mFourthDigitArray[2] = 0;
                    mFourthDigitArray[3]++;
                }
                else
                {
                    mFourthDigitArray[0] = 0;
                    mFourthDigitArray[1] = 0;
                    mFourthDigitArray[2]++;
                }
            }
            else
            {
                mFourthDigitArray[0] = 0;
                mFourthDigitArray[1]++;
            }
        }
        else
        {
            mFourthDigitArray[0]++;
        }
    }
    mReturnCounter++;
    return mToReturn;
}


