#include "UBigInt.h"

UBigInt::UBigInt() {
  m_value.push_back(0);
}

UBigInt::UBigInt(uint64_t val) {
  m_value.push_back(val);
}

UBigInt::UBigInt(std::vector<std::uint64_t> vals) {
  m_value = vals;
}

UBigInt::UBigInt(std::string strval) {
  // strip off leading zeros from the input string
  strval.erase(0, strval.find_first_not_of('0'));
  // strip off leading spaces from the input string
  strval.erase(0, strval.find_first_not_of(' '));

  if (strval.size() <= 0) {
    m_value.push_back(0);
    return;
  }

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

    if (bitIndex == 64) {
      uint64_t value = 0;
      for (int i = bitIndex - 1; i >= 0; --i) {
        value += bitArr[i] * 1;
        if (i != 0) { value <<= 1; }
      }
      m_value.push_back(value);
      bitIndex = 0;
      bitArr = new uint8_t[64]();
    }
  }

  uint64_t value = 0;
  for (int i = bitIndex - 1; i >= 0; --i) {
    value += bitArr[i] * 1;
    if (i != 0) { value <<= 1; }
  }
  if (value > 0) { m_value.push_back(value); }
}

UBigInt UBigInt::add(UBigInt num) const {
  uint64_t carry = 0;
  for (int i = 0; i < m_value.size(); ++i) {

  }
  return UBigInt(m_value[0] + num.m_value[0]);
}

std::size_t UBigInt::length() {
  return m_value.size();
}

std::string UBigInt::toString() {

  std::vector<uint8_t> decimalArr;
  decimalArr.push_back(0);

  for (int i = m_value.size() - 1; i >= 0; --i) {
    int maxBitIdx = 63;
    // if (i == m_value.size() - 1) {
    //   maxBitIdx = __builtin_ctzll(m_value[i]) + 1;
    // }
    for (int j = maxBitIdx; j >= 0; --j) {
      uint8_t carry = 0;
      for (int m = 0; m < decimalArr.size(); ++m) {
        decimalArr[m] *= 2;
        decimalArr[m] += carry;
        carry = 0;
        if (decimalArr[m] > 9) {
          decimalArr[m] -= 10;
          carry = 1;
        }
      }

      if (carry == 1) {
        decimalArr.push_back(1);
        carry = 0;
      }

      uint64_t bMask = 1;
      for (int k = 0; k < j; ++k) {
        bMask <<= 1;
      }
      if ((m_value[i] & bMask) != 0) {
        decimalArr[0] += 1;
      }
    }
  }

  std::string printValue;
  for (int i = decimalArr.size() - 1; i >= 0; --i) {
    printValue.push_back(decimalArr[i] + '0');
  }

  // std::cout << printValue << "\n";
  return printValue;
}

std::uint64_t UBigInt::toUInt64() {
  return m_value[0];
}