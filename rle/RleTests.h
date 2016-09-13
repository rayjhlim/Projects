#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
        
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test");
        TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic negative runs test");
        TEST_CASE_DESCRIBE(testSinglePositiveRun, "Single positive run test");
        TEST_CASE_DESCRIBE(testLongPositiveRuns, "Long positive runs test");
        TEST_CASE_DESCRIBE(testSingleCharacterRun, "Single character run test");
        TEST_CASE_DESCRIBE(testEdgeSingleCharacterRun, "Edge single character run test");
        TEST_CASE_DESCRIBE(testSandwichSinglePositiveRun, "Sandwiched single positive character run test");
        TEST_CASE_DESCRIBE(testLongNegativeRuns, "Long negative runs test");
        TEST_CASE_DESCRIBE(testAlternatingPositiveNegativeRuns, "Alternating positive negative runs test");
        TEST_CASE_DESCRIBE(testReallyLongPositiveRuns, "Really long positive runs test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRuns, "Really long negative runs test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRunSinglePositiveRun, "Really long negative with single positive at the end run test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRunThenPositiveRun, "Really long negative then positive run test");
         
        
	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    // TODO
    void testBasicNegativeRuns()
    {
        char test[] = "abababababab";
        
        char expected[] = "\xf4" "abababababab";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testSinglePositiveRun()
    {
        char test[] = "abbbcddde";
        
        char expected[] = "\x01" "a" "\x03" "b" "\x01" "c" "\x03" "d" "\x01" "e";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testLongPositiveRuns()
    {
        char test[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
        "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddd"
        "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
        
        char expected[] = "\x5c" "a" "\x58" "b" "\x5d" "c" "\x65" "d";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testSingleCharacterRun() {
        char test[] = "a";
        
        char expected[] = "\x01" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testEdgeSingleCharacterRun() {
        char test[] = "abbbbbc";
        
        char expected[] = "\x01" "a" "\x05" "b" "\x01" "c";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
 
    void testSandwichSinglePositiveRun() {
        char test[] = "aaaaabccccc";
        
        char expected[] = "\x05" "a" "\x01" "b" "\x05" "c";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testLongNegativeRuns()
    {
        char test[] = "ababababawqkljdabababababqweopiabababababababababababababaxbababa"
        "bawqkljdabababababqweopiabababababababababababababxabababababa";
        
        char expected[] = "\x81" "ababababawqkljdabababababqweopiabababababababababababababaxbababab"
        "awqkljdabababababqweopiabababababababababababababxabababababa";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternatingPositiveNegativeRuns()
    {
        char test[] = "xyzaaaaxyzbbbxyz";
        
        char expected[] = "\xfd" "xyz" "\x04" "a" "\xfd" "xyz" "\x03" "b" "\xfd" "xyz";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongPositiveRuns()
    {
        char test[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        
        char expected[] = "\x7F" "a" "\x73" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testReallyLongNegativeRuns()
    {
        char test[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstu"
        "vwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmno";
        
        char expected[] = "\x81" "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghij"
        "klmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
        "\xee" "xyzabcdefghijklmno";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongNegativeRunSinglePositiveRun() {
        char test[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr"
        "stuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwx";
        
        char expected[] = "\x81" "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzab"
        "cdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
        "\x01" "x";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongNegativeRunThenPositiveRun() {
        char test[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr"
        "stuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxaa";
        
        char expected[] = "\x81" "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd"
        "efghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
        "\x01" "x" "\x02" "a";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive run test");
		// TODO: Add more Decompression test  cases
        TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic negative runs test");
        TEST_CASE_DESCRIBE(testSinglePositiveRun, "Single positive run test");
        TEST_CASE_DESCRIBE(testSingleCharacterRun, "Single character run test");
        TEST_CASE_DESCRIBE(testEdgeSingleCharacterRun, "Edge single character run test");
        TEST_CASE_DESCRIBE(testSandwichSinglePositiveRun, "Sandwiched single positive character run test");
        TEST_CASE_DESCRIBE(testLongPositiveRuns, "Long positive runs test");
        TEST_CASE_DESCRIBE(testLongNegativeRuns, "Long negative runs test");
        TEST_CASE_DESCRIBE(testAlternatingPositiveNegativeRuns, "Alternating positive negative runs test");
        TEST_CASE_DESCRIBE(testReallyLongPositiveRuns, "Really long positive runs test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRuns, "Really long negative runs test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRunSinglePositiveRun, "Really long negative with single positive at the end run test");
        TEST_CASE_DESCRIBE(testReallyLongNegativeRunThenPositiveRun, "Really long negative then positive run test");
	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "\x28" "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testBasicNegativeRuns()
    {
        char test[] = "\xf4" "abababababab";
        char expected[] = "abababababab";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testSinglePositiveRun()
    {
        char test[] = "\x01" "a" "\x03" "b" "\x01" "c" "\x03" "d" "\x01" "e";
        char expected[] = "abbbcddde";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testLongPositiveRuns()
    {
        char test[] = "\x5c" "a" "\x58" "b" "\x5d" "c" "\x65" "d";
        char expected[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
        "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddd"
        "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testSingleCharacterRun()
    {
        char test[] = "\x01" "a";
        char expected[] = "a";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testEdgeSingleCharacterRun()
    {
        char test[] = "\x01" "a" "\x05" "b" "\x01" "c";
        char expected[] = "abbbbbc";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testSandwichSinglePositiveRun()
    {
        char test[] = "\x05" "a" "\x01" "b" "\x05" "c";
        char expected[] = "aaaaabccccc";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testLongNegativeRuns()
    {
        char test[] = "\x81" "ababababawqkljdabababababqweopiabababababababababababababaxbababab"
        "awqkljdabababababqweopiabababababababababababababxabababababa";
        char expected[] = "ababababawqkljdabababababqweopiabababababababababababababaxbababa"
        "bawqkljdabababababqweopiabababababababababababababxabababababa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testAlternatingPositiveNegativeRuns()
    {
        char test[] = "\xfd" "xyz" "\x04" "a" "\xfd" "xyz" "\x03" "b" "\xfd" "xyz";
        char expected[] = "xyzaaaaxyzbbbxyz";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongPositiveRuns()
    {
        char test[] = "\x7F" "a" "\x73" "a";
        char expected[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testReallyLongNegativeRuns()
    {
        char test[] = "\x81" "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr"
        "stuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
        "\xee" "xyzabcdefghijklmno";
        char expected[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstu"
        "vwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmno";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }

    void testReallyLongNegativeRunSinglePositiveRun()
    {
        char test[] = "\x81" "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzab"
        "cdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
        "\x01" "x";
        char expected[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr"
        "stuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwx";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
    void testReallyLongNegativeRunThenPositiveRun()
    {
        char test[] = "\x81" "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd"
        "efghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
        "\x01" "x" "\x02" "a";
        char expected[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr"
        "stuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxaa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }


};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			break;
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
