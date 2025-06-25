#include "header.h"

#define CHECK(x, y) x & (1 << y)

char* RemoveFileExtension(char* fileName, char pathSeperator, char extensionSeperator){
    if(fileName == NULL){
        printf("Did not pass a file name into RemoveFileExtension");
        return NULL;
    }
    int stringLength = strlen(fileName);
    char *returnString, *lastPath, *lastExtension;
    returnString = (char*)malloc(sizeof(char) * (stringLength + 9));
    if(returnString == NULL){
        printf("Failed to allocate memory in RemoveFileExtension");
        return NULL;
    }

    strcpy(returnString, fileName);

    lastPath = returnString;
    while(strchr(lastPath, pathSeperator) != NULL){
        lastPath = strchr(lastPath, pathSeperator);
        lastPath++;
    }

    lastExtension = lastPath;
    if(strchr(lastExtension, extensionSeperator) == NULL) return returnString;

    while(strchr(lastExtension, extensionSeperator) != NULL){
        lastExtension = strchr(lastExtension, extensionSeperator);
        lastExtension++;
    }
    lastExtension--;
    lastExtension[0] = '\0';

    return returnString;
}

char* GetFileExtension(char* fileName, char pathSeperator, char extensionSeperator){
    if(fileName == NULL){
        printf("Did not pass a file name into RemoveFileExtension");
        return NULL;
    }
    int stringLength = strlen(fileName);
    char *returnString, *lastPath, *lastExtension;
    returnString = (char*)malloc(sizeof(char) * (stringLength + 1));
    if(returnString == NULL){
        printf("Failed to allocate memory in RemoveFileExtension");
        return NULL;
    }

    strcpy(returnString, fileName);

    lastPath = returnString;
    while(strchr(lastPath, pathSeperator) != NULL){
        lastPath = strchr(lastPath, pathSeperator);
        lastPath++;
    }

    lastExtension = lastPath;
    if(strchr(lastExtension, extensionSeperator) == NULL) return returnString;

    while(strchr(lastExtension, extensionSeperator) != NULL){
        lastExtension = strchr(lastExtension, extensionSeperator);
        lastExtension++;
    }
    lastExtension--;

    return lastExtension;
}

void pprintBinary16(matrix data){
    //swap the position of the two characters because I don't want to rewrite this code
    char temp = data.data[0];
    data.data[0] = data.data[1];
    data.data[1] = temp;

    int sizeInBits = 16;
    //sets count at nlsb since we know we will print at least that number of 0's and 1's
    int count = sizeInBits;
    //num of segments counts sets of 4's so that we know the necessary width of the hexadecimal print
    int numOfSegments = 0;
    //Offset helps make sure the sets of 4 start from the far right instead of left
    int offset = sizeInBits%4;

    for(int i = 0; i < sizeInBits; i++){
        /*
            check(storage, x), will check if the bit at x is 0 or 1.
            nlsb - i - 1 is necessary because the bit is flipped in storage so we need to go from the far left(nlsb) to the far right(nlsb- i - 1).
            The -1 makes sense because nlsb will always be bigger than i(because of the for loop conditions) and we need to check the position at bit shift left 0
        */
        int bitToCheck = (sizeInBits - i - 1);
        if(CHECK(data.num, bitToCheck)){
            printf("1\t");
        }
        else{  
            printf("0\t");
        }
        //prints out a space every fourth digit printed. subtract the offset so that if nlsb isn't a power of 4 it prints with the shorter section on the left
        bool needsNewLine = !((i-offset+1)%4);
        if(needsNewLine){
            printf("\n");
            numOfSegments++;
            count++;
        }
    }

    //Prints out the value in hexadecimal
    count += printf("(0x%.*X)\n", numOfSegments, data.num);
    
    return;
}