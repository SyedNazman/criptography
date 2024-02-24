#include <stdio.h>

#define BLOCK_SIZE 64
void leftShift(unsigned char *block, int size) {
    int i, carry = 0;

    for (i = 0; i < size; i++) {
        int nextCarry = (block[i] & 0x80) ? 1 : 0; 
        block[i] = (block[i] << 1) | carry;
        carry = nextCarry;
    }
} 
void xorWithConstant(unsigned char *block, int size, unsigned char constant) {
    block[size - 1] ^= constant;
} 
void generateCMACSubkeys(unsigned char *subkey1, unsigned char *subkey2) {
     
    unsigned char zeroBlock[BLOCK_SIZE / 8] = {0};  
    leftShift(zeroBlock, BLOCK_SIZE / 8);
    xorWithConstant(zeroBlock, BLOCK_SIZE / 8, 0x87);  
    for (int i = 0; i < BLOCK_SIZE / 8; i++) {
        subkey1[i] = zeroBlock[i];
    } 
    leftShift(subkey1, BLOCK_SIZE / 8);
    if (subkey1[0] & 0x80) {
        xorWithConstant(subkey1, BLOCK_SIZE / 8, 0x1B);  
    } 
    for (int i = 0; i < BLOCK_SIZE / 8; i++) {
        subkey2[i] = subkey1[i];
    }
}

int main() {
    unsigned char subkey1[BLOCK_SIZE / 8];
    unsigned char subkey2[BLOCK_SIZE / 8];

    generateCMACSubkeys(subkey1, subkey2); 
    printf("Subkey 1: ");
    for (int i = 1; i < BLOCK_SIZE / 8; i++) {
        printf("%02x ", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for (int i = 1; i < BLOCK_SIZE / 8; i++) {
        printf("%02x ", subkey2[i]);
    }
    printf("\n");

    return 0;
}
