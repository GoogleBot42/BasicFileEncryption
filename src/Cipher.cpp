#include "Cipher.h"

#include "StreamCipher.h"
#include "BlockCipher.h"

Cipher* Cipher::MakeCipher(int type, int inputDataSize, char *inputData, int keySize, char *key) {
	Cipher *c;
	
	if (type == 1)
		c = new BlockCipher(inputDataSize, inputData, keySize, key);
	else
		c = new StreamCipher(inputDataSize, inputData, keySize, key);
	
	return c;
}