#pragma once

#include "Cipher.h"

#include <iostream>

class BlockCipher : public Cipher {
public:
	BlockCipher(int inputDataSize, char *inputData, int keySize, char *key) 
		: Cipher(inputDataSize, inputData, keySize, key) {
		if (keySize != 8) {
			std::cout << "Key size must be 64 bits for this cipher" << std::endl;
			exit(-1);
		}
	}
	
	void Encrypt();
	void Decrypt();
};