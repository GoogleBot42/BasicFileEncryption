# Compiler options
CC=g++
CFLAGS= -c -Wall
LDFLAGS=
EXECUTABLE_NAME=PA1

# Folders
SRC=src
BIN=bin
OBJ=$(BIN)/obj

# Misc files that also need to be packaged
MISC_PACKAGE_FILES = doc testfiles README

# Files
SOURCE_FILES = main.cpp Cipher.cpp BlockCipher.cpp StreamCipher.cpp


#### Don't touch #####

# Main executable needs to be in the root directory for this assignment
EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=%)
# EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)

OBJECT_FILES     = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
	rm -rf $(BIN) $(EXECUTABLE_FILES) $(EXECUTABLE_NAME).tar

package: clean
	tar -cvf $(EXECUTABLE_NAME).tar Makefile $(SRC) $(MISC_PACKAGE_FILES)

.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<


### Tests ###
test: test-blockcipher test-streamcipher
	@echo "Tests completed Successfully"

test-blockcipher: $(EXECUTABLE_FILES)
	@./$(EXECUTABLE_FILES) B testfiles/blockPlainText blockCipherText testfiles/blockKey E
	@diff blockCipherText testfiles/blockCipherText
	@./$(EXECUTABLE_FILES) B blockCipherText blockPlainText testfiles/blockKey D
	@diff blockPlainText testfiles/blockPlainText
	@rm blockCipherText blockPlainText
	@echo "Blockcipher test successful"

test-streamcipher: $(EXECUTABLE_FILES)
	@./$(EXECUTABLE_FILES) S testfiles/streamPlainText streamCipherText testfiles/streamKey E
	@diff streamCipherText testfiles/streamCipherText
	@./$(EXECUTABLE_FILES) S streamCipherText streamPlainText testfiles/streamKey D
	@diff streamPlainText testfiles/streamPlainText
	@rm streamCipherText streamPlainText
	@echo "Streamcipher test successful"
