#ifndef HEADER
    #define HEADER
    #define FLIPBIT(x, y) x ^ (1 << y)

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <ctype.h>
    #include <stdbool.h>

    union Matrix {
        char data[3];
        short int num;
    };

    #define matrix union Matrix

    void pprintBinary16(matrix data);
    char* RemoveFileExtension(char* fileName, char pathSeperator, char extensionSeperator);
    char* GetFileExtension(char* fileName, char pathSeperator, char extensionSeperator);
    void Encrypt(char* fileName, char* key);
    void RunKey(char* storage, char* key, FILE* inFile, FILE* outFile);
    void unRunKey(char* storage, char* key, FILE* inFile, FILE* outFile);
    void flipAllBits(matrix* storage);
    void flipRow(matrix* storage, int num);
    void flipColumn(matrix* storage, int num);
    void swapRows(matrix *storage, int row1, int row2);
    void swapColumns(matrix* storage, int column1, int column2);
    void runInstruction(matrix* thing, char currentChar);
    void Decrypt(char* fileName, char* key);
#endif