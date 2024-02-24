#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
void frequencyAttack(const char *ciphertext, int topPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    for (size_t i = 0; i < strlen(ciphertext); i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            frequency[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            frequency[c - 'a']++;
        }
    }
    int maxFrequencyIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > frequency[maxFrequencyIndex]) {
            maxFrequencyIndex = i;
        }
    }
    int key = (maxFrequencyIndex + ALPHABET_SIZE - ('E' - 'A')) % ALPHABET_SIZE;
    printf("Top %d possible plaintexts:\n", topPlaintexts);
    for (int i = 0; i < topPlaintexts; i++) {
        printf("%d. ", i + 1);
        for (size_t j = 0; j < strlen(ciphertext); j++) {
            char c = ciphertext[j];
            if (c >= 'A' && c <= 'Z') {
                printf("%c", 'A' + (c - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE);
            } else if (c >= 'a' && c <= 'z') {
                printf("%c", 'a' + (c - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE);
            } else {
                printf("%c", c);
            }
        }

        printf("\n");
    }
}
int main() {
    char ciphertext[1000];
    int topPlaintexts;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    strtok(ciphertext, "\n");
    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &topPlaintexts);
    frequencyAttack(ciphertext, topPlaintexts);
    return 0;
}
