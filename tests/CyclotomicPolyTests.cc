#include "gtest/gtest.h"
#include "cyclotomic-poly.h"
#include "cmath"

TEST(CyclotomicPolyTests, MyOwnNttRecursiveImpl) {
    UInt g = 132170, mod = 4194353;
    UInt gi = 1;
    UIntVec vec = {431, 3414, 1234, 7845, 2145, 7415, 5471, 8452};
    UIntVec expectedVec = {36407, 944774, 3788830, 3608793, 4176508, 1366094, 397265, 2462189};

    Ntt(vec, g, mod);

    EXPECT_EQ(vec, expectedVec);
}

TEST(CyclotomicPolyTests, NttAndINttRecursive) {
    UInt g = 11, mod = 769;
    UInt gi = 70;
    UIntVec coeffVec = {15, 21, 13, 44};
    UIntVec evalVec = {93, 114, 732, 659};
    UIntVec vec(coeffVec);

    Ntt(vec, g, mod);
    EXPECT_EQ(vec, evalVec);

    InvNtt(vec, gi, mod);
    EXPECT_EQ(vec, coeffVec);
}

TEST(CyclotomicPolyTests, NttAndINttRecursiveOverARing) {
    UInt g = 11, mod = 769;
    UInt gi = 70;
    UIntVec vec1 = {1, 2, 3, 4};
    UIntVec vec2 = {4, 3, 2, 1};
    UIntVec expectedVec = {753, 0, 16, 30};

    NttOverARing(vec1, g, mod);
    NttOverARing(vec2, g, mod);

    UIntVec resultVec;
    for (size_t i = 0; i < 4; ++i) {
        resultVec.push_back(vec1[i] * vec2[i]);
    }

    InvNttOverARing(resultVec, gi, mod);
    EXPECT_EQ(resultVec, expectedVec);
}
