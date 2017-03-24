#pragma once

#include "Cipher.h"

class StreamCipher : public Cipher {
public:
	StreamCipher(int inputDataSize, char *inputData, int keySize, char *key) 
		: Cipher(inputDataSize, inputData, keySize, key) {}
	
	void Encrypt();
	void Decrypt() { Encrypt(); } // Encrypt and Decrypt are the same for this algorithm
};