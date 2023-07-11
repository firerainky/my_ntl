#include "gtest/gtest.h"
#include "my-ftt.h"

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
