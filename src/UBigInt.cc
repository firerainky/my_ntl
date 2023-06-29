#include "UBigInt.h"


template<typename T>
constexpr bool get_value() { return T::value; }

template<typename T>
    requires (sizeof(T) > 1 && get_value<T>())
void f(T) {
    std::cout << "template version" << std::endl;
}

void f(int32_t) {
    std::cout << "int version" << std::endl;
}

void c15() {
    f('A');
}

UBigInt::UBigInt()
{
    m_value.push_back(0);
}

UBigInt::UBigInt(uint64_t val)
{
    m_value.push_back(val);
}

UBigInt::UBigInt(std::vector<std::uint64_t> vals)
{
    m_value = vals;
}

UBigInt::UBigInt(std::string strval)
{
    // strip off leading zeros from the input string
    strval.erase(0, strval.find_first_not_of('0'));
    // strip off leading spaces from the input string
    strval.erase(0, strval.find_first_not_of(' '));

    if (strval.size() <= 0)
    {
        m_value.push_back(0);
        return;
    }

    size_t decimalLength = strval.length();
    uint8_t *decimalArr = new uint8_t[decimalLength]();
    for (int i = 0; i < decimalLength; i++)
    {
        decimalArr[i] = strval[i] - '0';
    }
    uint8_t *bitArr = new uint8_t[64]();
    uint8_t bitIndex = 0;
    uint8_t decimalNonZeroIdx = 0;
    while (decimalNonZeroIdx < decimalLength)
    {
        bitArr[bitIndex++] = decimalArr[decimalLength - 1] % 2;

        for (int i = decimalNonZeroIdx; i < decimalLength - 1; i++)
        {
            decimalArr[i + 1] += (decimalArr[i] % 2) * 10;
            decimalArr[i] >>= 1;
        }
        decimalArr[decimalLength - 1] >>= 1;

        if (!decimalArr[decimalNonZeroIdx])
        {
            decimalNonZeroIdx++;
        }

        if (bitIndex == 64)
        {
            uint64_t value = 0;
            for (int i = bitIndex - 1; i >= 0; --i)
            {
                value += bitArr[i] * 1;
                if (i != 0)
                {
                    value <<= 1;
                }
            }
            m_value.push_back(value);
            bitIndex = 0;
            bitArr = new uint8_t[64]();
        }
    }

    uint64_t value = 0;
    for (int i = bitIndex - 1; i >= 0; --i)
    {
        value += bitArr[i] * 1;
        if (i != 0)
        {
            value <<= 1;
        }
    }
    if (value > 0)
    {
        m_value.push_back(value);
    }
}

UBigInt UBigInt::add(UBigInt num) const
{
    std::vector<uint64_t> resultVectors;

    uint8_t carry = 0;
    uint64_t currentLimb;
    int i = 0;
    while (i < length() && i < num.length())
    {
        carry = addWithCarry(m_value[i], num.m_value[i], carry, &currentLimb);
        resultVectors.push_back(currentLimb);
        ++i;
    }
    while (i < length())
    {
        carry = addWithCarry(m_value[i], 0, carry, &currentLimb);
        resultVectors.push_back(currentLimb);
        ++i;
    }
    while (i < num.length())
    {
        carry = addWithCarry(0, num.m_value[i], carry, &currentLimb);
        resultVectors.push_back(currentLimb);
        ++i;
    }

    return UBigInt(resultVectors);
}

UBigInt UBigInt::sub(UBigInt num) const
{
    std::vector<uint64_t> resultVectors;

    uint8_t borrow = 0;
    uint64_t currentLimb;

    for (int i = 0; i < length(); ++i)
    {
        if (i >= num.length())
        {
            borrow = subWithBorrow(m_value[i], 0, borrow, &currentLimb);
            resultVectors.push_back(currentLimb);
        }
        else
        {
            borrow = subWithBorrow(m_value[i], num.m_value[i], borrow, &currentLimb);
            resultVectors.push_back(currentLimb);
        }
    }

    return UBigInt(resultVectors);
}

UBigInt UBigInt::multiply(UBigInt num) const
{
    std::vector<uint64_t> value;
    for (int i = 0; i < length(); ++i)
    {
        for (int j = 0; j < num.length(); ++j)
        {
            uint64_t temp_result[2];
            multiplyWithKaratsuba(m_value[i], num.m_value[j], temp_result);
            uint8_t carry = 0;
            uint64_t sum;
            if (i + j + 1 > value.size())
            {
                value.push_back(temp_result[0]);
            }
            else
            {
                carry = addWithCarry(temp_result[0], value[i + j], carry, &sum);
                value[i + j] = sum;
                temp_result[1] += carry;
                carry = 0;
            }

            if (i + j + 2 > value.size())
            {
                value.push_back(temp_result[1]);
            }
            else
            {
                carry = addWithCarry(temp_result[1], value[i + j + 1], carry, &sum);
                value[i + j + 1] = sum;
                uint8_t currentIdx = i + j + 2;
                while (carry)
                {
                    if (currentIdx > value.size())
                    {
                        value.push_back(carry);
                    }
                    else
                    {
                        carry = addWithCarry(0, value[currentIdx], carry, &sum);
                        value[currentIdx] = sum;
                    }
                }
            }
        }
    }

    return UBigInt(value);
}

std::size_t UBigInt::length() const
{
    return m_value.size();
}

std::string UBigInt::toString()
{
    std::vector<uint8_t> decimalArr;
    decimalArr.push_back(0);

    for (int i = m_value.size() - 1; i >= 0; --i)
    {
        int maxBitIdx = 63;
        // if (i == m_value.size() - 1) {
        //   maxBitIdx = __builtin_ctzll(m_value[i]) + 1;
        // }
        for (int j = maxBitIdx; j >= 0; --j)
        {
            uint8_t carry = 0;
            for (int m = 0; m < decimalArr.size(); ++m)
            {
                decimalArr[m] *= 2;
                decimalArr[m] += carry;
                carry = 0;
                if (decimalArr[m] > 9)
                {
                    decimalArr[m] -= 10;
                    carry = 1;
                }
            }

            if (carry == 1)
            {
                decimalArr.push_back(1);
                carry = 0;
            }

            uint64_t bMask = 1;
            for (int k = 0; k < j; ++k)
            {
                bMask <<= 1;
            }
            if ((m_value[i] & bMask) != 0)
            {
                decimalArr[0] += 1;
            }
        }
    }

    std::string printValue;
    for (int i = decimalArr.size() - 1; i >= 0; --i)
    {
        printValue.push_back(decimalArr[i] + '0');
    }

    // std::cout << printValue << "\n";
    return printValue;
}

std::uint64_t UBigInt::toUInt64()
{
    return m_value[0];
}
