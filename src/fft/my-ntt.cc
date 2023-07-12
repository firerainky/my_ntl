#include "my-ntt.h"

int64_t FastPower(int64_t n, int64_t power, int64_t mod) {
    int64_t res = 1;
    while (power) {
        if (power & 1) {
            res = res * n % mod;
        }
        n = n * n % mod;
        power >>= 1;
    }
    return res;
}

void change(int64_t *vec, size_t len) {
    size_t i, j, k;

    for (int i = 1, j = len / 2; i < len - 1;) {
        if (i < j) {
            int64_t temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
        // i++, j 变成新的 i 对应的值，保证 i 与 j 始终是反转的
        ++i;
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
}

void MyNtt(int64_t *vec, size_t len, int64_t g, int64_t gi, int64_t mod, bool inv) {
    change(vec, len);
    int64_t inversion = inv ? -1 : 1;

    for (size_t h = 2; h <= len; h <<= 1) {
        int64_t gn = FastPower(inv ? gi : g, (mod - 1) / h, mod);

        for (size_t j = 0; j < len; j+= h) {
            int64_t g = 1;
            for (size_t k = j; k < j + h/2; ++k) {
                int64_t u = vec[k];
                int64_t t = g * vec[k + h/2] % mod;
                vec[k] = (u + t) % mod;
                vec[k + h/2] = (u - t + mod) % mod;
                g = g * gn % mod;
            }
        }
    }

    if (inv) {
        int64_t inverse = FastPower(len, mod - 2, mod);
        for (size_t i = 0; i < len; ++i) {
            vec[i] = vec[i] * inverse % mod;
        }
    }
}
