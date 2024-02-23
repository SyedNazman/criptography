#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int modExp(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}
int diffieHellman(int a, int q, int x) {
    return modExp(a, x, q);
}

int main() {
    int a = 5;  
    int q = 21; 
    int aliceSecret = 6;
    int bobSecret = 8;
    int alicePublic = diffieHellman(a, q, aliceSecret);
    int bobPublic = diffieHellman(a, q, bobSecret);
    int sharedSecretAlice = diffieHellman(bobPublic, q, aliceSecret);
    int sharedSecretBob = diffieHellman(alicePublic, q, bobSecret);
    printf("Shared Secret (Alice): %d\n", sharedSecretAlice);
    printf("Shared Secret (Bob): %d\n", sharedSecretBob);

    return 0;
}
