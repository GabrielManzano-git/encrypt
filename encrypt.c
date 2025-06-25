#include "header.h"

/*
    THE DATA
    >the data, read from the file, is split up into 16 bit increments
    >the program visualizes this in a 4x4 array to shuffle around numbers or flip bits according to the key
    >the key's instructions are ran on each 16 bit section individually

    THE KEY
    >every 4 bits in the key correlates to a different instruction(every character is 2 instructions)
    >read as numbers, the instructions are as follows
        0:flip every bit
        1:flip row 1
        2:flip row 2
        3:flip row 3
        4:flip row 4
        5:flip column 1
        6:flip column 2
        7:flip column 3
        8:flip column 4
        9:swap column 1 and 2
        10(a):swap column 2 and 3
        11(b):swap column 3 and 4
        12(c):swap column 1 and 4
        13(d):swap row 1 and 3
        14(e):swap row 2 and 4
        15(f):swap row 2 and 3
*/

void Encrypt(char* fileName, char* key){
    if(fileName == NULL || key == NULL){
        printf("trying to encrypt with NULL fileName or key");
        return;
    }
    char* temp = GetFileExtension(fileName, '/', '.');
    char* outFileName = RemoveFileExtension(fileName, '/', '.');
    strcat(outFileName, "_encoded");
    strcat(outFileName, temp);
    FILE* outFile = fopen(outFileName, "wb");
    FILE* inFile = fopen(fileName, "rb");

    unsigned char storage[2];
    unsigned int bytesRead = fread(storage, 1, 2, inFile);
    while(bytesRead == 2){
        RunKey(storage, key, inFile, outFile);
        bytesRead = fread(storage, 1, 2, inFile);
    }
    if(bytesRead == 1){
        storage[1] = 0;
        RunKey(storage, key, inFile, outFile);
    }
    else if(bytesRead == 0);
    else{
        printf("Unexpected error happened when reading file");
        fclose(inFile);
        return;
    }

    fclose(inFile);
    fclose(outFile);
    return;
}

void RunKey(char* storage, char* key, FILE* inFile, FILE* outFile){
    matrix thing;
    thing.data[0] = storage[0];
    thing.data[1] = storage[1];
    //strncpy(thing.data, storage, 2);
    thing.data[2] = '\0';
    int keyLength = strlen(key);
    char* keyPointer = key;
    for(keyPointer; keyPointer < key+keyLength; keyPointer++){
        unsigned char firstInstruction = *keyPointer;
        firstInstruction = firstInstruction >> 4;
        runInstruction(&thing, firstInstruction);
        unsigned char secondInstruction = *keyPointer;
        secondInstruction = secondInstruction << 4;
        secondInstruction = secondInstruction >> 4;
        runInstruction(&thing, secondInstruction);
    }


    fwrite(thing.data, 1, 2, outFile);
}

void runInstruction(matrix* thing, char currentChar){
    switch(currentChar){
        case 0:
            flipAllBits(thing);
            break;
        case 1:       
        case 2:    
        case 3:
        case 4:
            flipRow(thing, currentChar);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            flipColumn(thing, currentChar - 4);
            break;
        case 9:
            swapColumns(thing, 1, 2);
            break;
        case 10:
            swapColumns(thing, 2, 3);
            break;
        case 11:
            swapColumns(thing, 3, 4);
            break;
        case 12:
            swapColumns(thing, 1, 4);
            break;
        case 13:
            swapRows(thing, 1, 3);
            break;
        case 14:
            swapRows(thing, 2, 4);
            break;
        case 15:
            swapRows(thing, 1, 4);
            break;
        default:
            printf("An unexpected behavior has occured\n");
            break;
        }
}