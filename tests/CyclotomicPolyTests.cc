#include "gtest/gtest.h"
#include "cyclotomic-poly.h"

TEST(CyclotomicPolyTests, GetPhyco) {
    for (int n = 1; n <= 8; ++n) {
        std::vector<int> poly = CyclotomicPoly(n);
        std::cout << "Cyclotomic polynomial of degree " << n << ": ";
        for (int i = 0; i < poly.size(); ++i) {
            std::cout << poly[i] << " ";
        }
        std::cout << std::endl;
    }
}

TEST(CyclotomicPolyTests, MyOwnNttRecursiveImpl) {
    UInt g = 132170, mod = 4194353;
    UInt gi = 1;
    UIntVec vec = {431, 3414, 1234, 7845, 2145, 7415, 5471, 8452};
    UIntVec expectedVec = {36407, 944774, 3788830, 3608793, 4176508, 1366094, 397265, 2462189};

    RecursiveNtt(vec, g, mod);

    EXPECT_EQ(vec, expectedVec);
}

TEST(CyclotomicPolyTests, MyOwnNttRecursiveImpl2) {
    UInt g = 11, mod = 769;
    UInt gi = 1;
    UIntVec vec = {15, 21, 13, 44};
    UIntVec expectedVec = {93, 114, 732, 659};

    RecursiveNtt(vec, g, mod);

    EXPECT_EQ(vec, expectedVec);
}

// TEST(CyclotomicPolyTests, MyOwnNttRecursiveImpl3) {
//     UInt g = 11, mod = 769;
//     UInt gi = 1;
//     UIntVec vec = {1, 2, 3, 4};
//     UIntVec expectedVec = {93, 114, 732, 659};

//     RecursiveNtt(vec, g, mod);

//     EXPECT_EQ(vec, expectedVec);
// }
