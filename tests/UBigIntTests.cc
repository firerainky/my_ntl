#include <gtest/gtest.h>

#include "UBigInt.h"

TEST(UBigIntTests, EmptyConstructorCreatesZero)
{
    UBigInt bigInt;
    ASSERT_EQ(bigInt.length(), 1);
    ASSERT_EQ(bigInt.toString(), "0");
}

TEST(UBigIntTests, CreatesBigUnsignedIntegerWithStringRepresentation)
{
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

TEST(UBigIntTests, AddTwoUnsignedBigIntegers)
{
    ASSERT_EQ(UBigInt("3").add(UBigInt("4")).toString(), "7");
    ASSERT_EQ(UBigInt().add(UBigInt("1234567")).toString(), "1234567");
    ASSERT_EQ(UBigInt("0").add(UBigInt("123456789012345678901234567890")).toString(), "123456789012345678901234567890");
    ASSERT_EQ(UBigInt("123456789012345678901234567890").add(UBigInt("123456789012345678901234567890")).toString(),
              "246913578024691357802469135780");
    ASSERT_EQ(UBigInt("12345678901234567890123456789012345678901234567890")
                  .add(UBigInt("123456789012345678901234567890"))
                  .toString(),
              "12345678901234567890246913578024691357802469135780");
}

TEST(UBigIntTests, BiggerIntegerSubtractSmallerInteger)
{
    ASSERT_EQ(UBigInt("4").sub(UBigInt("3")).toString(), "1");
    ASSERT_EQ(UBigInt("1234567").add(UBigInt()).toString(), "1234567");
    ASSERT_EQ(UBigInt("123456789012345678901234567890").add(UBigInt("0")).toString(), "123456789012345678901234567890");
    ASSERT_EQ(UBigInt("123456789012345678901234567890").sub(UBigInt("123456789012345678901234567890")).toString(), "0");
    ASSERT_EQ(UBigInt("12345678901234567890246913578024691357802469135780")
                  .sub(UBigInt("123456789012345678901234567890"))
                  .toString(),
              "12345678901234567890123456789012345678901234567890");
    ASSERT_EQ(UBigInt("100000000000000000000000000000000000000000000000000")
                  .sub(UBigInt("99999999999999999999999999999999999999999999999999"))
                  .toString(),
              "1");
}

TEST(UBigIntTests, MultiplyTwoUnsignedBigInteger)
{
    ASSERT_EQ(UBigInt("4").multiply(UBigInt("0")).toString(), "0");
    ASSERT_EQ(UBigInt("3").multiply(UBigInt("4")).toString(), "12");
    ASSERT_EQ(UBigInt("1234567").multiply(UBigInt()).toString(), "0");
    ASSERT_EQ(UBigInt("1234567").multiply(UBigInt("1234567")).toString(), "1524155677489");
    ASSERT_EQ(UBigInt("123456789012345678901234567890").multiply(UBigInt("1")).toString(),
              "123456789012345678901234567890");
    ASSERT_EQ(UBigInt("123456789012345678901234567890").multiply(UBigInt("0")).toString(), "0");
    ASSERT_EQ(UBigInt("123456789012345678901234567890").multiply(UBigInt("123456789012345678901234567890")).toString(),
              "15241578753238836750495351562536198787501905199875019052100");
    ASSERT_EQ(UBigInt("999999999999999999999999999999").multiply(UBigInt("999999999999999999999999999999")).toString(),
              "999999999999999999999999999998000000000000000000000000000001");
}
