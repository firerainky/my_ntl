#include <iostream>
#include <vector>

class UBigInt {
  public:
    UBigInt();
    UBigInt(std::string strval);
    std::size_t length();
    std::string toString();
  private:
    std::vector<uint64_t> m_value;
};