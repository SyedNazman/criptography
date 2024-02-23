#include <stdio.h>

void encrypt_SDES(unsigned char plaintext[], unsigned char key[], unsigned char ciphertext[]) {
    unsigned char k[2][8], subkeys[16][8], temp[8], temp2[8], left[4], right[4];
    int i, j;

    // Generating 2 subkeys
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            k[i][j] = key[j];
        }
    }

    // Generate 16 subkeys
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 8; j++) {
            subkeys[i][j] = k[i % 2][j];
        }
        // Circular left shift on k[0]
        for (j = 0; j < 7; j++) {
            temp[j] = k[0][j + 1];
        }
        temp[7] = k[0][0];
        for (j = 0; j < 8; j++) {
            k[0][j] = temp[j];
        }
        // Circular right shift on k[1]
        for (j = 7; j > 0; j--) {
            temp2[j] = k[1][j - 1];
        }
        temp2[0] = k[1][7];
        for (j = 0; j < 8; j++) {
            k[1][j] = temp2[j];
        }
    }

    // Initial permutation
    for (j = 0; j < 4; j++) {
        left[j] = plaintext[j];
        right[j] = plaintext[j + 4];
    }

    // 16 rounds of encryption
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 4; j++) {
            temp[j] = right[j];
        }
        // Expansion permutation
        right[0] = temp[3];
        right[1] = temp[0];
        right[2] = temp[1];
        right[3] = temp[2];
        for (j = 0; j < 4; j++) {
            right[j] = right[j] ^ subkeys[i][j];
        }
        // Substitution using S-Box
        temp[0] = ((right[0] & 0x08) >> 2) | ((right[0] & 0x04) >> 1) | ((right[0] & 0x02) << 1) | ((right[0] & 0x01) << 2);
        temp[1] = ((right[1] & 0x08) >> 2) | ((right[1] & 0x04) >> 1) | ((right[1] & 0x02) << 1) | ((right[1] & 0x01) << 2);
        temp[2] = ((right[2] & 0x08) >> 2) | ((right[2] & 0x04) >> 1) | ((right[2] & 0x02) << 1) | ((right[2] & 0x01) << 2);
        temp[3] = ((right[3] & 0x08) >> 2) | ((right[3] & 0x04) >> 1) | ((right[3] & 0x02) << 1) | ((right[3] & 0x01) << 2);
        // Permutation P4
        right[0] = temp[1];
        right[1] = temp[3];
        right[2] = temp[2];
        right[3] = temp[0];
        // XOR operation with left half
        for (j = 0; j < 4; j++) {
            right[j] = right[j] ^ left[j];
        }
        // Swap left and right
        for (j = 0; j < 4; j++) {
            left[j] = temp[j];
        }
    }

    // Final permutation
    for (j = 0; j < 4; j++) {
        temp[j] = left[j];
        left[j] = right[j];
        right[j] = temp[j];
    }

    // Combine left and right
    for (j = 0; j < 4; j++) {
        ciphertext[j] = left[j];
        ciphertext[j + 4] = right[j];
    }
}

void decrypt_SDES(unsigned char ciphertext[], unsigned char key[], unsigned char plaintext[]) {
    encrypt_SDES(ciphertext, key, plaintext);
}

void printBinary(unsigned char binary[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%d", (binary[i / 8] >> (7 - (i % 8))) & 1);
    }
}

int main() {
    unsigned char plaintext[8] = {0b00000001, 0b00000010, 0b00000100, 0};
    unsigned char key[8] = {0b01111111, 0b1101};
    unsigned char ciphertext[8], decrypted_plaintext[8];

    encrypt_SDES(plaintext, key, ciphertext);
    printf("Encrypted: ");
    printBinary(ciphertext, 48); // Prints the binary ciphertext

    decrypt_SDES(ciphertext, key, decrypted_plaintext);
    printf("\nDecrypted: ");
    printBinary(decrypted_plaintext, 48); // Prints the binary decrypted plaintext

    return 0;
}

