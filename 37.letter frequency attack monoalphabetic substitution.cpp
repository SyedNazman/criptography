#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
const float englishFreq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094,
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929,
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};
float calculateChiSquared(const int *observedFreq) {
    float chiSquared = 0.0;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        chiSquared += ((observedFreq[i] - englishFreq[i]) * (observedFreq[i] - englishFreq[i])) / englishFreq[i];
    }

    return chiSquared;
}
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    for (size_t i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - key[ciphertext[i] - base] + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}
void letterFrequencyAttack(const char *ciphertext, int topPlaintexts) {
    int observedFreq[ALPHABET_SIZE] = {0};
    int totalLetters = 0;
    for (size_t i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            observedFreq[ciphertext[i] - base]++;
            totalLetters++;
        }
    }
    for (int shift = 0; shift < ALPHABET_SIZE; ++shift) {
        char key[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            key[i] = (i + shift) % ALPHABET_SIZE;
        }
        char plaintext[256];
        decrypt(ciphertext, key, plaintext);
        float chiSquared = calculateChiSquared(observedFreq);
        printf("Key Shift: %d, Plaintext: %s, Chi-Squared: %.2f\n", shift, plaintext, chiSquared);
    }
}

int main() {
    const char *ciphertext = "Uifsf jt b tfdsfu djqifs xjuipvu uif mfuufs!";

    printf("Ciphertext: %s\n", ciphertext);

    int topPlaintexts;
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topPlaintexts);

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}
