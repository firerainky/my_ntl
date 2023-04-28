#include "gtest/gtest.h"

// uint32_t ceiIntByUInt(const uint32_t number) {
//     uint32_t mask =
// }

TEST(CeilIntTests, Uint64Constructor) {
    auto v = uint64_t(123);
    ASSERT_EQ(v, 123);
}
