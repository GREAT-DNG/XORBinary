#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void XORBinary(unsigned char* Binary, size_t BinarySize, char* Key, size_t KeySize, unsigned char* Result) {
    for (size_t i = 0; i < BinarySize; i++)
        Result[i] = Binary[i] ^ Key[i % KeySize];
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("XOR binary encryptor/decryptor\n");
        printf("Usage: %s <File> <Key>\n", argv[0]);
        return 1;
    }

    char* Key = argv[2];
    size_t KeySize = strlen(Key);

    FILE* BinaryFile = fopen(argv[1], "rb+");

    fseek(BinaryFile, 0, SEEK_END);
    long BinarySize = ftell(BinaryFile);
    rewind(BinaryFile);

    unsigned char* Binary = malloc(BinarySize);
    fread(Binary, 1, BinarySize, BinaryFile);

    unsigned char* Result = malloc(BinarySize);

    XORBinary(Binary, BinarySize, Key, KeySize, Result);

    rewind(BinaryFile);
    fwrite(Result, 1, BinarySize, BinaryFile);

    fclose(BinaryFile);
    free(Binary);
    free(Result);

    return 0;
}
