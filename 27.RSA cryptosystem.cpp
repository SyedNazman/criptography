#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;

        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}
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

int main() {
    int e = 65537;
    int n = 309485009;  
    int plaintext[] = {3, 2, 11, 18, 4};
    int ciphertext[5];
    for (int i = 0; i < 5; ++i) {
        ciphertext[i] = modExp(plaintext[i], e, n);
    }
    printf("Encrypted Message: ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
