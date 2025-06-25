#include "header.h"

void flipAllBits(matrix* storage){
    for(int i = 0; i < 16; i++){
        storage->num = FLIPBIT(storage->num, i);
    }
}

//num is the row you want to flip(1, 2, 3, or 4)
void flipRow(matrix* storage, int num){
    if(num == 1 || num == 2) storage->num = storage->num ^ (0xF0 >> 4*(num - 1));
    if(num == 3) storage->num = storage->num ^ (0xF << 12);
    if(num == 4) storage->num = storage->num ^ (0xF << 8);
}

//num is the column you want to flip(1, 2, 3, or 4)
void flipColumn(matrix* storage, int num){
    for(int i = 0; i < 4; i++){
        storage->num = FLIPBIT(storage->num, 4*i + 4 - num);
    }
}

//Access numbers for row 1 & 3 are swapped, and 2 & 4
//i.e. if you wanted to swap rows 3 and 4, you would type swapRows(storage, 1, 2)
void swapRows(matrix *storage, int row1, int row2){
    matrix copy;
    copy.num = storage->num;
    matrix storage1, storage2;
    storage1.num = 0;
    storage2.num = 0;
    for(int i = 0; i < 4; i++){
        if(storage->num & 1 << (i + (4 * (4-row1)))) storage1.num = storage1.num ^ (1 << i);
        if(storage->num & 1 << (i + (4 * (4-row2)))) storage2.num = storage2.num ^ (1 << i);
    }
    /*printf("------------------------------------------\nPrinting the stored rows\n");
    pprintBinary16(storage1);
    pprintBinary16(storage2);
    printf("------------------------------------------\nAttempting to put stored rows into storage\n");*/
    for(int i = 0; i < 4; i++){
        if(storage1.num & 1 << i) storage->num = storage->num | (1 << (i + (4 * (4-row2))));
        else storage->num = storage->num & ~(1 << (i + (4 * (4-row2))));
        if(storage2.num & 1 << i) storage->num = storage->num | (1 << (i + (4 * (4-row1))));
        else storage->num = storage->num & ~(1 << (i + (4 * (4-row1))));
    }

}

void swapColumns(matrix* storage, int column1, int column2){
    matrix copy;
    copy.num = storage->num;
    matrix storage1, storage2;
    storage1.num = 0;
    storage2.num = 0;
    for(int i = 0; i < 4; i++){
        if(storage->num & 1 << (i*4 + (4 - column1))) storage1.num = storage1.num ^ (1 << i);
        if(storage->num & 1 << (i*4 + (4 - column2))) storage2.num = storage2.num ^ (1 << i);
    }
    for(int i = 0; i < 4; i++){
         if(storage1.num & 1 << i) storage->num = storage->num | (1 << (i*4 + (4 - column2)));
        else storage->num = storage->num & ~(1 << (i*4 + (4 - column2)));
        if(storage2.num & 1 << i) storage->num = storage->num | (1 << (i*4 + (4 - column1)));
        else storage->num = storage->num & ~(1 << (i*4 + (4 - column1)));
    }

    return;
}