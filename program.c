#include "header.h"

int main(){
    char choice;
    printf("Select program option\n Type \"E\" to encrypt a file\n Type \"D\" to decrypt a file\n >");
    scanf("%c", &choice);
    choice = tolower(choice);
    if(!(choice == 'd' || choice == 'e')){
        printf("Invalid choice, aborting program");
        return 1;
    }
    char fileName[100];
    printf("Type the name of the file you'd like to encrypt or decrypt\n >");
    scanf("%s", fileName);

    char key[50];
    printf("Type the key for the encryption or decryption\n >");
    scanf("%s", key);

    if(choice == 'e'){
        printf("Encrypting %s with key %s\n", fileName, key);
        Encrypt(fileName, key);
        return 0;
    }
    else if(choice == 'd'){
        printf("Encrypting %s with key %s\n", fileName, key);
        Decrypt(fileName, key);
        return 0;
    }
    /*else if(choice == 'p'){
        printf("Printing binary of input\n");
        matrix thing;
        strncpy(thing.data, fileName, 2);
        thing.data[2] = '\0';
        pprintBinary16(thing);
        return 0;
    }*/
    else{
        printf("Something unexpected occured in main");
        return 1;
    }
}