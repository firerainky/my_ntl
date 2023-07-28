#include "cyclotomic-poly.h"

#include <iostream>
#include <vector>
#include <array>

UInt FastPowerMod(UInt n, UInt power, UInt mod) {
    if (n <= 1) return n;

    UInt res = 1;
    while (power) {
        if (power & 1) {
            res = res * n % mod;
        }
        n = n * n % mod;
        power >>= 1;
    }
    return res;
}

void RecursiveNtt(UIntVec &vec, UInt g, UInt mod) {
    size_t n = vec.size();
    if (n <= 1) return;
    size_t h = n / 2;

    UIntVec even, odd;
    for (size_t i = 0; i < h; ++i) {
        even.push_back(vec[2 * i]);
        odd.push_back(vec[2 * i + 1]);
    }

    RecursiveNtt(even, g, mod);
    RecursiveNtt(odd, g, mod);

    UInt w = 1;
    UInt gn = FastPowerMod(g, (mod - 1) / n, mod);
    for (size_t i = 0; i < h; ++i) {
        UInt t = (w * odd[i]) % mod;
        vec[i] = (even[i] + t) % mod;
        vec[i + h] = (even[i] + mod - t) % mod;
        w = w * gn % mod;
    }
}

void RecursiveINtt(UIntVec &vec, UInt gi, UInt mod) {
    size_t n = vec.size();
    if (n <= 1) return;
    size_t h = n / 2;

    UIntVec even, odd;
    for (size_t i = 0; i < h; ++i) {
        even.push_back(vec[2 * i]);
        odd.push_back(vec[2 * i + 1]);
    }

    RecursiveINtt(even, gi, mod);
    RecursiveINtt(odd, gi, mod);

    UInt w = 1;
    UInt gn = FastPowerMod(gi, (mod - 1) / n, mod);
    for (size_t i = 0; i < h; ++i) {
        UInt t = (w * odd[i]) % mod;
        vec[i] = (even[i] + t) % mod;
        vec[i + h] = (even[i] + mod - t) % mod;
        w = w * gn % mod;
    }
}

void InverseNtt(UIntVec &vec, UInt gi, UInt mod) {
    RecursiveINtt(vec, gi, mod);

    UInt inv = FastPowerMod(vec.size(), mod - 2, mod);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = vec[i] * inv % mod;
    }
}
