#include <stdio.h>
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
void generateNewKeys(int *e, int *d, int *n) {
    int q = 53;
    int p = 26;
    *n = p * q;
    int phi_n = (p - 1) * (q - 1);
    *e = 17;
    *d = modInverse(*e, phi_n);
}

int main() {
    int original_e = 17;
    int original_d = 2853;
    int original_n = 3233; 
    printf("Original Public Key: (e=%d, n=%d)\n", original_e, original_n);
    printf("Original Private Key: (d=%d, n=%d)\n", original_d, original_n);
    int new_e, new_d, new_n;
    generateNewKeys(&new_e, &new_d, &new_n);
    printf("\nNew Public Key: (e=%d, n=%d)\n", new_e, new_n);
    printf("New Private Key: (d=%d, n=%d)\n", new_d, new_n);

    return 0;
}
