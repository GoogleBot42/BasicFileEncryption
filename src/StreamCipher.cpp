#include "StreamCipher.h"

void StreamCipher::Encrypt() {
	outputDataSize = inputDataSize;
	outputData = new char[outputDataSize];
	
	int keyIndex = 0;
	for (int i=0; i<outputDataSize; i++) {
		outputData[i] = inputData[i] ^ key[keyIndex];
		keyIndex++;
		if (keyIndex >= keySize) keyIndex = 0;
	}
}