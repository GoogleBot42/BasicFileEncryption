#include <iostream>
// #include <fstream>
#include <cstring>
#include <cstdio>

#include "Cipher.h"

using namespace std;

char *ReadFile(const char *filename, int &size) {
	FILE *f = fopen(filename,"rb");
	
	if (!f) return NULL;
	
	fseek(f,0,SEEK_END);
	long fsize = ftell(f);
	fseek(f,0,SEEK_SET);
	
	char *str = new char[fsize + 1];
	fread(str,fsize,1,f);
	fclose(f);
	
	str[fsize] = 0;
	
	size = (int)fsize; // Not expecting a big file
	return str;
}

bool WriteFile(const char *filename, char *data, int size) {
	FILE *f = fopen(filename,"wb");
	if (!f) return false;
	fwrite(data, sizeof(char), size, f);
	fclose(f);
	return true;
}

int main(int argc, const char* argv[]) {
	
	if (argc != 6) {
		cout << "Usage: ./PA1 <\"B\" or \"S\"> <input file> <output file> <keyfile> <\"E\" or \"D\">" << endl;
		return -1;
	}
	
	// parse args
	
	// if B then mode == 1.  if S then mode == 2 otherwise 0
	int mode = (strcmp(argv[1],"B") == 0) ? 1 : 0;
	mode = (strcmp(argv[1],"S") == 0) ? 2 : mode;
	
	// if E then dir == 1.  if D then dir == 2 otherwise 0
	int dir = (strcmp(argv[5],"E") == 0) ? 1 : 0;
	dir = (strcmp(argv[5],"D") == 0) ? 2 : dir;
	
	if (!mode) {
		cout << "The mode must be B(lock) or S(tream)" << endl;
		return -1;
	}
	
	if (!dir) {
		cout << "The direction must be E(ncrypt) or D(ecrypt)" << endl;
		return -1;
	}
	
	// attempt to open and read the files
	int inSize;
	int keySize;
	char *in = ReadFile(argv[2], inSize);
	char *key = ReadFile(argv[4], keySize);
	
	if (!in) {
		cout << "Could not open input file for reading" << endl;
		return -1;
	}
	
	if (!key) {
		cout << "Could not open key file for reading" << endl;
		return -1;
	}
	
	// Now time to do what the user asked
	
	Cipher *cipher = Cipher::MakeCipher(mode, inSize, in, keySize, key);
	
	if (dir == 1) cipher->Encrypt();
	if (dir == 2) cipher->Decrypt();
	
	if ( !WriteFile(argv[3], cipher->GetOutputData(), cipher->GetOutputDataSize()) ) {
		cout << "Could not open output file for writing" << endl;
		return -1;
	}
	
	return 0;
}