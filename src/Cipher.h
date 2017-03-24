#pragma once

class Cipher {
protected:
	int inputDataSize;
	char *inputData;
	
	int keySize;
	char *key;
	
	int outputDataSize;
	char *outputData;
	
	Cipher(int inputDataSize, char *inputData, int keySize, char *key) 
		: inputDataSize(inputDataSize),
		  inputData(inputData),
		  keySize(keySize),
		  key(key),
		  outputDataSize(0),
		  outputData(0)
	{}
	
public:
	static Cipher* MakeCipher(int type, int inputDataSize, char *inputData, int keySize, char *key);
	
	virtual void Encrypt() = 0;
	virtual void Decrypt() = 0;
	
	char* GetOutputData() { return outputData; }
	int GetOutputDataSize() { return outputDataSize; }
};