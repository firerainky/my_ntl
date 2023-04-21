#include <iostream>
#include <vector>

class UBigInt {
 public:
  UBigInt();
  UBigInt(std::uint64_t val);
  UBigInt(std::vector<std::uint64_t> vals);
  UBigInt(std::string strval);

  UBigInt add(UBigInt num) const;
  UBigInt sub(UBigInt num) const;
  UBigInt multiply(UBigInt num) const;

  std::size_t length() const;
  std::string toString();
  std::uint64_t toUInt64();

 private:
  std::vector<uint64_t> m_value;
};

inline uint8_t addWithCarry(uint64_t operand1, uint64_t operand2, uint8_t carry,
                            uint64_t *result) {
  operand1 += operand2;
  *result = operand1 + carry;
  return (operand1 < operand2) || (~operand1 < carry);
}

inline uint8_t subWithBorrow(uint64_t operand1, uint64_t operand2,
                             uint8_t borrow, uint64_t *result) {
  auto diff = operand1 - operand2;
  *result = diff - (borrow != 0);
  return (diff > operand1) || (diff < borrow);
}

/**
 * @brief Karatsuba 算法计算 uint64_t * uint64_t, 结果为一个 128 位的数
 *
 * (a * 2^n + b) * (c * 2^n + d) = ac*2^2n + (ad + bc)*2^n + bd
 * 这里 n = 32，下面的计算时由于进位的原因，做了多次平移。
 */
inline void multiplyWithKaratsuba(uint64_t operand1, uint64_t operand2,
                                  uint64_t *result128) {
  uint64_t a = operand1 >> 32;
  uint64_t b = operand1 & 0x00000000FFFFFFFF;
  uint64_t c = operand2 >> 32;
  uint64_t d = operand2 & 0x00000000FFFFFFFF;

  uint64_t right = b * d;
  uint64_t middle;
  uint64_t left =
      a * c +
      (static_cast<uint64_t>(addWithCarry(a * d, b * c, 0, &middle)) << 32);
  uint64_t temp_sum = (right >> 32) + (middle & 0x000000000FFFFFFFF);

  result128[1] = left + (middle >> 32) + (temp_sum >> 32);
  result128[0] = (temp_sum << 32) | (right & 0x00000000FFFFFFFF);
}