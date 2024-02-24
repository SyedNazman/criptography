#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define ALPHABET_SIZE 26
void generateRandomKey(int *key, int length) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < length; ++i) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}
void encryptVigenere(const char *plaintext, int *key, char *ciphertext) {
    int keyIndex = 0;
    for (size_t i = 0; plaintext[i] != '\0'; ++i) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[keyIndex]) % ALPHABET_SIZE + base;
            keyIndex = (keyIndex + 1) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
}
int main() {
    const char *plaintext = "Hello, World!";
    int keyLength = 12;
    int key[keyLength];
    char ciphertext[256];
    generateRandomKey(key, keyLength);
    encryptVigenere(plaintext, key, ciphertext);
    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (int i = 0; i < keyLength; ++i) {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
