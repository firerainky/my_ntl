#include "gtest/gtest.h"
#include "my-ftt.h"
#include "my-ntt.h"
#include <cmath>

TEST(FftTests, fft) {
    Complex coeffs[4] = {Complex(-1.0, 2.0), Complex(0.0, -1.0), Complex(2.0, -1.0), Complex(1.0)};
    Complex expectedResult[4] = {Complex(2.0), Complex(-2.0, 2.0), Complex(0.0, 2.0), Complex(-4.0, 4.0)};

    MyFft(coeffs, 4);

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*(coeffs + i), *(expectedResult + i));
    }
}

TEST(FftTests, fftVec) {
    ComplexVec coeffs = {Complex(-1.0, 2.0), Complex(0.0, -1.0), Complex(2.0, -1.0), Complex(1.0)};
    ComplexVec expectedResult = {Complex(2.0), Complex(-2.0, 2.0), Complex(0.0, 2.0), Complex(-4.0, 4.0)};

    MyFftVec(coeffs);

    EXPECT_EQ(coeffs, expectedResult);
}

TEST(FftTests, ifftVec) {
    ComplexVec values = {Complex(2.0), Complex(-2.0, 2.0), Complex(0.0, 2.0), Complex(-4.0, 4.0)};
    ComplexVec expectedResult = {Complex(-1.0, 2.0), Complex(0.0, -1.0), Complex(2.0, -1.0), Complex(1.0)};

    MyFftVec(values, true);
    const double eps = 1e-6;

    for (size_t i = 0; i < values.size(); ++i) {
        values[i] /= values.size();
        if (abs(values[i].real()) < eps) {
            values[i].real(0);
        }
    }

    EXPECT_EQ(values, expectedResult);
}

TEST(FftTests, fftVecOptimize) {
    ComplexVec coeffs = {Complex(-1.0, 2.0), Complex(0.0, -1.0), Complex(2.0, -1.0), Complex(1.0)};
    ComplexVec values = {Complex(2.0), Complex(-2.0, 2.0), Complex(0.0, 2.0), Complex(-4.0, 4.0)};

    ComplexVec vec = coeffs;
    MyFftVecOptimize(vec);
    EXPECT_EQ(vec, values);

    vec = values;
    MyFftVecOptimize(vec, true);
    EXPECT_EQ(vec, coeffs);
}

TEST(NttTests, ntt) {
    int64_t g = 3, gi = 332748118, mod = 998244353;

    size_t m = 2, n = 3;
    int len = 1 << std::max((int)ceil(log2(m + n)), 1);

    int64_t poly1[len] = {1, 2, 0, 0, 0, 0, 0, 0};
    int64_t poly2[len] = {1, 2, 1, 0, 0, 0, 0, 0};

    MyNtt(poly1, len, g, gi, mod);
    MyNtt(poly2, len, g, gi, mod);

    for (int i = 0; i < len; ++i) {
        poly1[i] = poly1[i] * poly2[i] % mod;
    }

    MyNtt(poly1, len, g, gi, mod, true);

    // 求 len 在 mod 下的逆元（根据费马小定理？）
    int64_t inverse = FastPower(len, mod - 2, mod);
    int64_t expectedResult[len] = {1, 4, 5, 2, 0, 0, 0, 0};

    for (size_t i = 0; i < len; ++i) {
        EXPECT_EQ(poly1[i], expectedResult[i]) << "At index " << i << " got wrong number.";
    }
}

TEST(NttTests, nttWithMoreSpecificData) {
    int64_t g = 132170, mod = 4194353;
    int64_t gi = FastPower(g, mod - 2, mod);

    size_t len = 4;
    int64_t poly[len] = {4127, 9647, 1987, 5410};
    int64_t expectedResult[len] = {885632, 1936918, 2107494, 3475170};
    MyNtt(poly, len, g, gi, mod);

    // for (size_t i = 0; i < len; ++i) {
    //     EXPECT_EQ(poly[i], expectedResult[i]) << "At index " << i << " got wrong number.";
    // }
    MyNtt(poly, len, g, gi, mod, true);
    std::cout << "duedue: ";
    for (size_t i = 0; i < len; ++i) {
        std::cout << poly[i] << ", ";
    }
    std::cout << "\n";
}
