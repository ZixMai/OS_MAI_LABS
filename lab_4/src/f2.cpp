#include "f2.h"

int Gcd(int a, int b) {
    for (int i = 2; i <= a && i <= b; i++) {
        if (a % i == 0 && b % i == 0) {
            return i;
        }
    }
    return 1;
}

float PiVallis(int k) {
    float result = 1;

    for (auto n = 1; n <= k; ++n){
        result *= (4.0f * n * n) / (4.0f * n * n - 1.0f);
    }

    return 2 * result;
}
