#include "UBigInt.h"

UBigInt::UBigInt() {
  m_value.push_back(0);
}

std::size_t UBigInt::length() {
  return m_value.size();
}

std::string UBigInt::toString() {
  return "0";
}