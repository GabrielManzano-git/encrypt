#include "header.h"

void Decrypt(char* fileName, char* key){
    if(fileName == NULL || key == NULL){
        printf("trying to encrypt with NULL fileName or key");
        return;
    }
    char* temp = GetFileExtension(fileName, '/', '.');
    char* outFileName = RemoveFileExtension(fileName, '/', '.');
    strcat(outFileName, "_decoded");
    strcat(outFileName, temp);
    FILE* outFile = fopen(outFileName, "wb");
    FILE* inFile = fopen(fileName, "rb");

    unsigned char storage[2];
    unsigned int bytesRead = fread(storage, 1, 2, inFile);
    while(bytesRead == 2){
        unRunKey(storage, key, inFile, outFile);
        bytesRead = fread(storage, 1, 2, inFile);
    }
    if(bytesRead == 1){
        storage[1] = 0;
        unRunKey(storage, key, inFile, outFile);
    }
    else if(bytesRead == 0);
    else{
        printf("Unexpected error happened when reading file\n");
        fclose(inFile);
        return;
    }

    fclose(inFile);
    fclose(outFile);
    return;
}

void unRunKey(char* storage, char* key, FILE* inFile, FILE* outFile){
    matrix thing;
    thing.data[0] = storage[0];
    thing.data[1] = storage[1];
    //strncpy(thing.data, storage, 2);
    thing.data[2] = '\0';
    int keyLength = strlen(key);
    char* keyPointer = key+keyLength - 1;
    for(keyPointer; keyPointer >= key; keyPointer--){
        unsigned char secondInstruction = *keyPointer;
        secondInstruction = secondInstruction << 4;
        secondInstruction = secondInstruction >> 4;
        runInstruction(&thing, secondInstruction);
        unsigned char firstInstruction = *keyPointer;
        firstInstruction = firstInstruction >> 4;
        runInstruction(&thing, firstInstruction);
    }

    fwrite(thing.data, 1, 2, outFile);
}