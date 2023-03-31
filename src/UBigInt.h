#include <iostream>
#include <vector>

class UBigInt {
  public:
    UBigInt();
    UBigInt(std::uint64_t val);
    UBigInt(std::vector<std::uint64_t> vals);
    UBigInt(std::string strval);

    UBigInt add(UBigInt num) const;

    std::size_t length() const;
    std::string toString();
    std::uint64_t toUInt64();
  private:
    std::vector<uint64_t> m_value;
};

inline uint8_t addWithCarry(uint64_t operand1, uint64_t operand2, uint8_t carry, uint64_t *result) {
  operand1 += operand2;
  *result = operand1 + carry;
  return (operand1 < operand2) || (~operand1 < carry);
}