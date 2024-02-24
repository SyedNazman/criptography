#include <stdio.h>
#include <ctype.h>
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
char encryptChar(int a, int b, char plaintext) {
    if (isalpha(plaintext)) {
        char base = isupper(plaintext) ? 'A' : 'a';
        return (a * (plaintext - base) + b) % 26 + base;
    }
    return plaintext; 
}
void encryptAffineCaesar(int a, int b, const char *plaintext, char *ciphertext) {
    for (size_t i = 0; plaintext[i] != '\0'; ++i) {
        ciphertext[i] = encryptChar(a, b, plaintext[i]);
    }
}
int main() {
    int a = 5;
    int b = 8; 
    const char *plaintext = "Hello, World!";
    char ciphertext[256];
    encryptAffineCaesar(a, b, plaintext, ciphertext);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
