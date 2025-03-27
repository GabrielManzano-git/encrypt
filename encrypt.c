#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_PASSWORD_SIZE 15
#define MAX_KEY_SIZE 10

typedef enum Instructions{
    shuffleRow,
    shuffleColumn,
    bitSwapOddRows,
    bitSwapEvenRows,
    bitSwapOddColumns,
    bitSwapEvenColumns
}
typedef struct Instruction_Struct{
    uint8_t instruction;
    Instruction_List* nextInstruction;
} Instruction_List;

int main(int argc, char* argv[]){
    char password[MAX_PASSWORD_SIZE] = argv[1];
    char key[MAX_KEY_SIZE] = argv[2];
}