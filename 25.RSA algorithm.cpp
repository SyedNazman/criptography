#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
void factorize(int n, int factor) {
    int p = factor;
    int q = n / factor;

    printf("Factorization of n: p = %d, q = %d\n", p, q);
}

int main() {
    int p = 60;
    int q = 53;
    int n = p * q;
    int e = 17;
    int ciphertext = 123;
    if (gcd(ciphertext, n) != 1) {
        printf("The ciphertext has a common factor with n.\n");
        factorize(n, gcd(ciphertext, n));
    } else {
        printf("The ciphertext does not have a common factor with n.\n");
    }

    return 0;
}
