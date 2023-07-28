#include "cyclotomic-poly.h"

#include <iostream>
#include <vector>
#include <array>

UInt fastPowerMod(UInt n, UInt power, UInt mod) {
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

void recursiveNtt(UIntVec &vec, UInt g, UInt mod) {
    size_t n = vec.size();
    if (n <= 1) return;
    size_t h = n / 2;

    UIntVec even, odd;
    for (size_t i = 0; i < h; ++i) {
        even.push_back(vec[2 * i]);
        odd.push_back(vec[2 * i + 1]);
    }

    recursiveNtt(even, g, mod);
    recursiveNtt(odd, g, mod);

    UInt w = 1;
    UInt gn = fastPowerMod(g, (mod - 1) / n, mod);
    for (size_t i = 0; i < h; ++i) {
        UInt t = (w * odd[i]) % mod;
        vec[i] = (even[i] + t) % mod;
        vec[i + h] = (even[i] + mod - t) % mod;
        w = w * gn % mod;
    }
}

void Ntt(UIntVec &vec, UInt g, UInt mod) {
    recursiveNtt(vec, g, mod);
}

void InvNtt(UIntVec &vec, UInt gi, UInt mod) {
    recursiveNtt(vec, gi, mod);

    UInt inv = fastPowerMod(vec.size(), mod - 2, mod);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = vec[i] * inv % mod;
    }
}

void NttOverARing(UIntVec &vec, UInt g, UInt mod) {
    // Times vec with (1, s, s^2, ..., s^n-1)
    size_t n = vec.size();
    UInt s = fastPowerMod(g, (mod - 1) / (2 * n), mod);

    UInt w = 1;
    for (size_t i = 0; i < n; ++i) {
        vec[i] = vec[i] * w % mod;
        w *= s;
    }

    recursiveNtt(vec, g, mod);
}

void InvNttOverARing(UIntVec &vec, UInt gi, UInt mod) {
    InvNtt(vec, gi, mod);

    size_t n = vec.size();
    UInt s = fastPowerMod(gi, (mod - 1) / (2 * n), mod);

    UInt w = 1;
    for (size_t i = 0; i < n; ++i) {
        vec[i] = vec[i] * w % mod;
        w *= s;
    }
}
