#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
typedef struct {
    char letter;
    int frequency;
} LetterFrequency;
void countFrequency(const char *text, int freq[]) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            freq[c - 'a']++;
        }
    }
}
int compareFrequency(const void *a, const void *b) {
    const LetterFrequency *freqA = (const LetterFrequency *)a;
    const LetterFrequency *freqB = (const LetterFrequency *)b;
    return freqB->frequency - freqA->frequency;
}
void decrypt(const char *cipher, const char *key) {
    char decrypted[strlen(cipher) + 1];
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            char c = tolower(cipher[i]);
            decrypted[i] = islower(c) ? key[c - 'a'] : toupper(key[c - 'a']);
        } else {
            decrypted[i] = cipher[i];
        }
    }
    decrypted[i] = '\0';
    printf("Decrypted text with key %s:\n%s\n\n", key, decrypted);
}

int main() {
    char ciphertext[1000]; 
    int freq[ALPHABET_SIZE] = {0};
    LetterFrequency letterFreq[ALPHABET_SIZE];
    int i, j;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    countFrequency(ciphertext, freq);
    for (i = 0; i < ALPHABET_SIZE; i++) {
        letterFreq[i].letter = 'a' + i;
        letterFreq[i].frequency = freq[i];
    }
    qsort(letterFreq, ALPHABET_SIZE, sizeof(LetterFrequency), compareFrequency);
    for (i = 0; i < ALPHABET_SIZE; i++) {
        char key[ALPHABET_SIZE + 1];
        for (j = 0; j < ALPHABET_SIZE; j++) {
            key[letterFreq[j].letter - 'a'] = 'a' + (j + i) % ALPHABET_SIZE;
        }
        key[ALPHABET_SIZE] = '\0';
        decrypt(ciphertext, key);
    }

    return 0;
}

