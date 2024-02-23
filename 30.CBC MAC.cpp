#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define BLOCK_SIZE 16

void xorBlocks(unsigned char *result, const unsigned char *block1, const unsigned char *block2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void aesEncrypt(const unsigned char *input, const unsigned char *key, unsigned char *output) {
}

void cbcMac(const unsigned char *message, const unsigned char *key, unsigned char *mac, size_t messageSize) {
    unsigned char iv[BLOCK_SIZE] = {0}; 
    unsigned char ciphertext[BLOCK_SIZE];
    aesEncrypt(message, key, ciphertext);
    xorBlocks(mac, message, ciphertext);
    unsigned char twoBlockMessage[2 * BLOCK_SIZE];
    memcpy(twoBlockMessage, message, BLOCK_SIZE);
    xorBlocks(twoBlockMessage + BLOCK_SIZE, message, mac);
    aesEncrypt(twoBlockMessage, key, mac);
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x7b, 0xab, 0xf7, 0x97, 0x7b};
    FILE *file = fopen("message.txt", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char *message = (unsigned char *)malloc(fileSize); 
    if (message == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }
    fread(message, 1, fileSize, file);
    fclose(file);
    unsigned char mac[BLOCK_SIZE];
    cbcMac(message, key, mac, fileSize);
    printf("CBC-MAC for the message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");
    free(message); 
    return 0;
}
