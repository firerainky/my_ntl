#include <gtest/gtest.h>

#include "UBigInt.h"

TEST(UBigIntTests, EmptyConstructorCreatesZero) {
  UBigInt bigInt;
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toString(), "0");
}

TEST(UBigIntTests, CreatesBigUnsignedIntegerWithStringRepresentation) {
  UBigInt bigInt("0");
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toUInt64(), 0ULL);
  ASSERT_EQ(bigInt.toString(), "0");

  bigInt = UBigInt("10");
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toUInt64(), 10ULL);
  ASSERT_EQ(bigInt.toString(), "10");

  bigInt = UBigInt("275");
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toUInt64(), 275ULL);
  ASSERT_EQ(bigInt.toString(), "275");
  
  bigInt = UBigInt("12345678901234567890");
  ASSERT_EQ(bigInt.length(), 1);
  ASSERT_EQ(bigInt.toUInt64(), 12345678901234567890ULL);
  ASSERT_EQ(bigInt.toString(), "12345678901234567890");

  bigInt = UBigInt("123456789012345678901");
  ASSERT_EQ(bigInt.length(), 2);
  ASSERT_EQ(bigInt.toString(), "123456789012345678901");

  bigInt = UBigInt("1234567890123456789012345678901234567890");
  ASSERT_EQ(bigInt.length(), 3);
  ASSERT_EQ(bigInt.toString(), "1234567890123456789012345678901234567890");

  bigInt = UBigInt("123456789012345678901234567890123456789012345678901234567890");
  ASSERT_EQ(bigInt.length(), 4);
  ASSERT_EQ(bigInt.toString(), "123456789012345678901234567890123456789012345678901234567890");
}

TEST(UBigIntTests, AddTwoUnsignedBigIntegers) {
  ASSERT_EQ(UBigInt("3").add(UBigInt("4")).toString(), "7");
}

