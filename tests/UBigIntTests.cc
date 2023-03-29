#include <gtest/gtest.h>

#include "UBigInt.h"

TEST(UBigIntTests, EmptyConstructorCreatesZero) {
  UBigInt bigInt;
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toString(), "0");
}

TEST(UBigIntTests, CreatesBigUnsignedIntegerWithStringRepresentation) {
  UBigInt bigInt("123");
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toUInt64(), 123);
}

