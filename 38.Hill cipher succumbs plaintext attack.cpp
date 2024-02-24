#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int modInverse(int a, int m) {
    a = a % m;

    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void encrypt(int keyMatrix[MAX_SIZE][MAX_SIZE], int plaintextMatrix[MAX_SIZE], int resultMatrix[MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        resultMatrix[i] = 0;

        for (int j = 0; j < size; j++) {
            resultMatrix[i] += keyMatrix[i][j] * plaintextMatrix[j];
        }

        resultMatrix[i] %= 26; 
    }
}
void decrypt(int keyMatrix[MAX_SIZE][MAX_SIZE], int ciphertextMatrix[MAX_SIZE], int resultMatrix[MAX_SIZE], int size) {
    int determinant = 0;
    int adjointMatrix[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; i++) {
        determinant += (keyMatrix[0][i] * (keyMatrix[1][(i + 1) % size] * keyMatrix[2][(i + 2) % size] - keyMatrix[1][(i + 2) % size] * keyMatrix[2][(i + 1) % size]));
    }

    determinant %= 26;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adjointMatrix[j][i] = (((keyMatrix[(i + 1) % size][(j + 1) % size] * keyMatrix[(i + 2) % size][(j + 2) % size]) - (keyMatrix[(i + 1) % size][(j + 2) % size] * keyMatrix[(i + 2) % size][(j + 1) % size])) % 26);

            if (adjointMatrix[j][i] < 0) {
                adjointMatrix[j][i] += 26;
            }
        }
    }

    int inverse = modInverse(determinant, 26);

    if (inverse == -1) {
        printf("Invalid key. Determinant has no modular inverse.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        resultMatrix[i] = 0;

        for (int j = 0; j < size; j++) {
            resultMatrix[i] += (adjointMatrix[i][j] * inverse * ciphertextMatrix[j]);
        }

        resultMatrix[i] = (resultMatrix[i] % 26 + 26) % 26; 
    }
}
void displayMatrix(int matrix[MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c", (matrix[i] + 'A')); 
    }
    printf("\n");
}

int main() {
    int keyMatrix[MAX_SIZE][MAX_SIZE];
    int plaintextMatrix[MAX_SIZE];
    int encryptedMatrix[MAX_SIZE];
    int decryptedMatrix[MAX_SIZE];
    int size;

    printf("Enter the size of the key matrix: ");
    scanf("%d", &size);

    printf("Enter the key matrix elements:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }

    printf("Enter the plaintext matrix elements: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &plaintextMatrix[i]);
    }

    encrypt(keyMatrix, plaintextMatrix, encryptedMatrix, size);
    printf("Encrypted text: ");
    displayMatrix(encryptedMatrix, size);

    decrypt(keyMatrix, encryptedMatrix, decryptedMatrix, size);
    printf("Decrypted text: ");
    displayMatrix(decryptedMatrix, size);

    return 0;
}
