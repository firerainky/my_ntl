#include "UBigInt.h"

UBigInt::UBigInt() {
  m_value.push_back(0);
}

UBigInt::UBigInt(std::string strval) {
  size_t decimalLength = strval.length();
  uint8_t *decimalArr = new uint8_t[decimalLength](); 
  for (int i = 0; i < decimalLength; i++) {
    decimalArr[i] = strval[i] - '0';
  }
  uint8_t *bitArr = new uint8_t[64]();
  uint8_t bitIndex = 0;
  uint8_t decimalNonZeroIdx = 0;
  while (decimalNonZeroIdx < decimalLength) {
    bitArr[bitIndex++] = decimalArr[decimalLength - 1] % 2;

    for (int i = decimalNonZeroIdx; i < decimalLength - 1; i++) {
      decimalArr[i + 1] += (decimalArr[i] % 2) * 10;
      decimalArr[i] >>= 1;
    }
    decimalArr[decimalLength - 1] >>= 1;

    if (!decimalArr[decimalNonZeroIdx]) {
      decimalNonZeroIdx++;
    }
  }
  
  uint64_t value = 0;
  for (int i = bitIndex - 1; i >= 0; --i) {
    value += bitArr[i] * 1;
    if (i != 0) { value <<= 1; }
  }
  
  m_value.push_back(value);
}

std::size_t UBigInt::length() {
  return m_value.size();
}

std::string UBigInt::toString() {
  return "0";
}

std::uint64_t UBigInt::toUInt64() {
  return m_value[0];
}