#include "gtest/gtest.h"

#include "UBigInt.h"

TEST(AddWithCarryTests, AddWithCarry)
{
    unsigned long long result;
    ASSERT_FALSE(addWithCarry(0ULL, 0ULL, 0, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_FALSE(addWithCarry(1ULL, 1ULL, 0, &result));
    ASSERT_EQ(2ULL, result);
    ASSERT_FALSE(addWithCarry(1ULL, 0ULL, 1, &result));
    ASSERT_EQ(2ULL, result);
    ASSERT_FALSE(addWithCarry(0ULL, 1ULL, 1, &result));
    ASSERT_EQ(2ULL, result);
    ASSERT_FALSE(addWithCarry(1ULL, 1ULL, 1, &result));
    ASSERT_EQ(3ULL, result);
    ASSERT_TRUE(addWithCarry(0xFFFFFFFFFFFFFFFFULL, 1ULL, 0, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_TRUE(addWithCarry(1ULL, 0xFFFFFFFFFFFFFFFFULL, 0, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_TRUE(addWithCarry(1ULL, 0xFFFFFFFFFFFFFFFFULL, 1, &result));
    ASSERT_EQ(1ULL, result);
    ASSERT_TRUE(addWithCarry(2ULL, 0xFFFFFFFFFFFFFFFEULL, 0, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_TRUE(addWithCarry(2ULL, 0xFFFFFFFFFFFFFFFEULL, 1, &result));
    ASSERT_EQ(1ULL, result);
    ASSERT_FALSE(addWithCarry(0xF00F00F00F00F00FULL, 0x0FF0FF0FF0FF0FF0ULL, 0, &result));
    ASSERT_EQ(0xFFFFFFFFFFFFFFFFULL, result);
    ASSERT_TRUE(addWithCarry(0xF00F00F00F00F00FULL, 0x0FF0FF0FF0FF0FF0ULL, 1, &result));
    ASSERT_EQ(0x0ULL, result);
}

TEST(SubWithBorrowTests, SubWithBorrow)
{
    unsigned long long result;
    ASSERT_FALSE(subWithBorrow(0ULL, 0ULL, 0, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_FALSE(subWithBorrow(1ULL, 1ULL, 0, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_FALSE(subWithBorrow(1ULL, 0ULL, 1, &result));
    ASSERT_EQ(0ULL, result);
    ASSERT_TRUE(subWithBorrow(0ULL, 1ULL, 1, &result));
    ASSERT_EQ(0xFFFFFFFFFFFFFFFEULL, result);
    ASSERT_TRUE(subWithBorrow(1ULL, 1ULL, 1, &result));
    ASSERT_EQ(0xFFFFFFFFFFFFFFFFULL, result);
    ASSERT_FALSE(subWithBorrow(0xFFFFFFFFFFFFFFFFULL, 1ULL, 0, &result));
    ASSERT_EQ(0xFFFFFFFFFFFFFFFEULL, result);
    ASSERT_TRUE(subWithBorrow(1ULL, 0xFFFFFFFFFFFFFFFFULL, 0, &result));
    ASSERT_EQ(2ULL, result);
    ASSERT_TRUE(subWithBorrow(1ULL, 0xFFFFFFFFFFFFFFFFULL, 1, &result));
    ASSERT_EQ(1ULL, result);
    ASSERT_TRUE(subWithBorrow(2ULL, 0xFFFFFFFFFFFFFFFEULL, 0, &result));
    ASSERT_EQ(4ULL, result);
    ASSERT_TRUE(subWithBorrow(2ULL, 0xFFFFFFFFFFFFFFFEULL, 1, &result));
    ASSERT_EQ(3ULL, result);
    ASSERT_FALSE(subWithBorrow(0xF00F00F00F00F00FULL, 0x0FF0FF0FF0FF0FF0ULL, 0, &result));
    ASSERT_EQ(0xE01E01E01E01E01FULL, result);
    ASSERT_FALSE(subWithBorrow(0xF00F00F00F00F00FULL, 0x0FF0FF0FF0FF0FF0ULL, 1, &result));
    ASSERT_EQ(0xE01E01E01E01E01EULL, result);
}