#include "cyclotomic-poly.h"

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

std::vector<int> CyclotomicPoly(int n) {
    if (n == 0) {
        return {1};
    } else if (n == 1) {
        return {1, -1};
    } else {
        std::vector<int> prevPoly = CyclotomicPoly(n - 1);
        std::vector<int> currPoly(prevPoly.size() + 1, 0);
        currPoly[0] = -prevPoly.back();
        for (int i = 1; i < prevPoly.size(); ++i) {
            currPoly[i] = prevPoly[i - 1] - prevPoly.back() * prevPoly[prevPoly.size() - i];
        }
        currPoly.back() = prevPoly.back();
        return currPoly;
    }
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