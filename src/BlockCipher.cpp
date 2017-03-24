#include "BlockCipher.h"

#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

void BlockCipher::Encrypt() {
	// Create output buffer of currect size
	// (round up to the nearest multiple of 8 bytes)
	outputDataSize = (int)( ceil((float)inputDataSize / 8.0f) * 8.0f );
	outputData = new char[outputDataSize];
	
	// how much the input data needs to be padded
	int padding = outputDataSize - inputDataSize;
	
	char *paddedBuffer = new char[outputDataSize];
	memcpy(paddedBuffer, inputData, inputDataSize);
	memset(paddedBuffer+inputDataSize, '\x80', padding);
	
	// XOR all blocks with the key
	for (int i=0; i<outputDataSize; i++)
		outputData[i] = paddedBuffer[i] ^ key[i%8]; // TODO do each block all at once like mod2 below
	
	delete paddedBuffer;
	
	
	// Now swap indivudual bytes based on the key
	
	// mod every byte in the key by 2
	((long long *)key)[0] = 0x0101010101010101 & ((long long *)key)[0];
	
	char *curByte = outputData;
	char *endByte = outputData + outputDataSize - 1;
	int curByteInKey = 0;
	while (curByte < endByte) {
		if (key[curByteInKey]) {
			// swap bytes
			int tmp = *curByte;
			*curByte = *endByte;
			*endByte = tmp;
			endByte--;
		}
		curByteInKey++;
		if (curByteInKey >= keySize) curByteInKey = 0;
		curByte++;
	}
}

void BlockCipher::Decrypt() {
	// swap bytes back
	char *tmpkey = new char[keySize];
	((long long *)tmpkey)[0] = 0x0101010101010101 & ((long long *)key)[0];
	
	outputData = new char[inputDataSize];
	memcpy(outputData,inputData,inputDataSize);
	
	char *curByte = outputData;
	char *endByte = outputData + inputDataSize - 1;
	int curByteInKey = 0;
	while (curByte < endByte) {
		if (tmpkey[curByteInKey]) {
			// swap bytes
			int tmp = *curByte;
			*curByte = *endByte;
			*endByte = tmp;
			endByte--;
		}
		curByteInKey++;
		if (curByteInKey >= keySize) curByteInKey = 0;
		curByte++;
	}
	
	// XOR all blocks with the key
	for (int i=0; i<inputDataSize; i++)
		outputData[i] = outputData[i] ^ key[i%8];
	
	// find out how long the padding is to get the true size
	char *cur = outputData + inputDataSize - 1;
	outputDataSize = inputDataSize;
	while (*cur == '\x80') {
		outputDataSize--;
		cur--;
	}
}