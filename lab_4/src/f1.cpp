#include "f1.h"

int GcdEuclid(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

float PiLeibniz(int k) {
    float res = 0.0f;
    float one = 1.0f;

    for (int i = 0; i < k; i++) {
        res += one / (2.0f * i + 1.0f);
        one *= -1;
    }

    return res * 4.0f;
}
