RLE

-Implemented RLE compression / decompression with C++ for ITP-435 (Professional C++) under Sanjay Madhav

-Created the compress and decompress method in RleData.cpp, archive and extract method in RleFile.cpp and
test cases in RleTests.h.

-Compresses file to .rl1 format and decompresses any .rl1 file into it's precompressed form

SHA-1 Password Cracker

-Implemented a Password Cracker with C++ for ITP-435 (Professional C++) under Sanjay Madhav
-The program takes in two command line arguments: d8.txt and pass.txt.
-d8.txt is a list of commonly used strings and the hashed passwords that need to be cracked are in pass.txt
-The program first hashes d8.txt and compares the hash values in pass.txt.
-The program brute forces unsolved passwords in pass.txt using Intel Thread Building Blocks to speed up the process.
-Created dictionary.cpp, dictionary.h, CountingMachine.cpp and CountingMachine.h
