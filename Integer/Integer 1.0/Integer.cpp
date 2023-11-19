#include <iostream>
#include <string>

#include "Integer.h"

Integer::Integer() :
	sign(POSITIVE_NUM), digit()
{
#ifdef _STUDY_
    std::cout << "构造函数-默认\n";
#endif
}

Integer::Integer(long long number)
{
	set(number);
#ifdef _STUDY_
    std::cout << "构造函数-long long 重载\n";
#endif
}

Integer::Integer(const char* number)
{
    set(number);
#ifdef _STUDY_
    std::cout << "构造函数-const char* 重载\n";
#endif
}

Integer::Integer(const std::string& digit)
{
    set(digit);
#ifdef _STUDY_
    std::cout << "构造函数-const std::string& 重载\n";
#endif
}

Integer::~Integer()
{
#ifdef _STUDY_
    std::cout << "析构函数\n";
#endif
}

Integer::Integer(const Integer& other) :
	sign(other.sign), digit(other.digit)
{
#ifdef _STUDY_
    std::cout << "拷贝构造\n";
#endif
}

Integer& Integer::operator=(const Integer& other)
{
	if (this != &other)
	{
		sign = other.sign;
        digit = other.digit;
	}
#ifdef _STUDY_
    std::cout << "拷贝赋值\n";
#endif
	return *this;
}

Integer::Integer(Integer&& other) noexcept :
    sign(other.sign), digit(std::move(other.digit))
{
#ifdef _STUDY_
    std::cout << "移动构造\n";
#endif
}

Integer& Integer::operator=(Integer&& other) noexcept
{
    if (this != &other)
    {
        sign = other.sign;
        digit = std::move(other.digit);
    }
#ifdef _STUDY_
    std::cout << "移动赋值\n";
#endif
    return *this;
}

void Integer::set(long long number)
{
    sign = number >= 0;
    digit = std::to_string(std::abs(number));
}

void Integer::set(const char* number)
{
    set(std::string(number));
}

void Integer::set(const std::string& number)
{
    sign = number[0] == '-' ? NEGATIVE_NUM : POSITIVE_NUM;
    digit.resize(sign ? number.size() : number.size() - 1);

    for (int i = 0; i < digit.size(); i++)
    {
        int index = sign ? i : i + 1;
        if (index < number.size())
        {
            if (number[index] >= '0' && number[index] <= '9')
            {
                digit[i] = number[index];
            }
            else
            {
                throw std::runtime_error("Incorrect integer");
                break;
            }
        }
    }
}

long long Integer::get() const
{
	long long number = 0;
	long long carry = 1;
	for (int i = digit.size() - 1; i >= 0; i--)
	{
		number += static_cast<long long>(digit[i]) * carry;
		carry *= 10;
	}
	return number;
}

int Integer::length() const
{
    return digit.size();
}

bool Integer::isPositive() const
{
    return sign;
}

int Integer::getBit(int bit) const
{
    return digit[digit.size() - bit] - '0';
}

Integer& Integer::operator+()
{
    if (!sign)
    {
        sign = POSITIVE_NUM;
    }
    return *this;
}

Integer& Integer::operator-()
{
	if (sign)
	{
		sign = NEGATIVE_NUM;
	}
    return *this;
}

Integer& Integer::abs()
{
    if (!sign)
    {
        sign = POSITIVE_NUM;
    }
	return *this;
}

Integer Integer::abs(const Integer& number)
{
    Integer res = number;
    if (!number.sign)
    {
        res.sign = POSITIVE_NUM;
    }
    return res;
}

Integer Integer::pow(const Integer& base, long long index)
{ 
    // 处理负指数的情况
    if (index < 0)
    {
        throw std::runtime_error("The index requirement is positive");
    }
    else if (index == 0) return Integer(1); // 任何数的0次方都为1
    else if (index == 1) return const_cast<Integer&>(base); // 任何数的1次方都等于自身

    Integer result = "1";
    Integer number = base;

    while (index > 0)
    {
        if (index & 1) // 奇数幂，将基数乘入结果
        {
            result *= number; 
        }
        number *= number; // 基数平方
        index >>= 1; // 指数除以 2
    }

    return result;
}

Integer Integer::operator+(const Integer& other) const
{
    if (sign && !other.sign) return *this - abs(other); // 正 + 负
    else if (!sign && other.sign) return other - abs(*this); // 负 + 正
    else if (!sign && !other.sign) return -(abs(*this) + abs(other)); // 负 + 负
    else return addPositive(other);
}

Integer Integer::operator-(const Integer& other) const
{
    if (sign && !other.sign) return *this + abs(other); // 正 - 负
    else if (!sign && other.sign) return -(abs(*this) + other); // 负 - 正
    else if (!sign && !other.sign) return abs(other) - abs(*this); // 负 - 负
    else if (sign && other.sign && *this < other) return -(other - *this); // 小 - 大
    else return subPositive(other);
}

Integer Integer::operator*(const Integer& other) const
{
    Integer temp(abs(*this));
    if (!sign) return -temp.mulPositive(other);
    else if (!other.sign) return -mulPositive(abs(other));
    else return mulPositive(other);
}

Integer Integer::operator/(const Integer& other) const // TODO 死循环
{
    Integer temp(abs(*this));
    if (sign && !other.sign) return -divPositive(abs(other)); // 正 / 负
    else if (!sign && other.sign) return -temp.divPositive(other); // 负 / 正
    else if (!sign && !other.sign) return temp.divPositive(abs(other)); // 负 / 负
    else return divPositive(other);
}

Integer Integer::operator%(const Integer& other) const
{
    Integer temp(abs(*this));
    if (sign && !other.sign) return modPositive(abs(other)); // 正 % 负
    else if (!sign && other.sign) return -temp.modPositive(other); // 负 % 正
    else if (!sign && !other.sign) return -temp.modPositive(abs(other)); // 负 % 负
    else if (sign && other.sign && *this < other) return *this; // 小 % 大
    else return modPositive(other);
}

Integer& Integer::operator+=(const Integer& other)
{
    *this = *this + other;
	return *this;
}

Integer& Integer::operator-=(const Integer& other)
{
    *this = *this - other;
	return *this;
}

Integer& Integer::operator*=(const Integer& other)
{
    *this = *this * other;
	return *this;
}

Integer& Integer::operator/=(const Integer& other)
{
    *this = *this / other;
	return *this;
}

Integer& Integer::operator%=(const Integer& other)
{
    *this = *this % other;
	return *this;
}

Integer Integer::operator<<(int number) const
{
    return (*this) * pow(2, number);
}

Integer Integer::operator>>(int number) const
{
    return (*this) / pow(2, number);
}

Integer& Integer::operator<<=(int number)
{
    *this = *this << number;
	return *this;
}

Integer& Integer::operator>>=(int number)
{
    *this = *this >> number;
	return *this;
}

std::istream& operator>>(std::istream& in, Integer& number)
{
    std::string temp;
    number.digit.clear();
    in >> temp;
    if (temp == "-0")
    {
        throw std::runtime_error("Incorrect integer");
    }
    else
    {
        number.set(temp);
    }
	return in;
}

std::ostream& operator<<(std::ostream& out, const Integer& number)
{
	if (!number.sign) out << '-';
	for (int i = 0; i < number.digit.size(); i++)
	{
		out << number.digit[i];
	}
	return out;
}

bool operator>(const Integer& left, const Integer& right)
{
    if (left.digit.size() != right.digit.size())
    {
        return left.digit.size() > right.digit.size();
    }

    if (left.sign == POSITIVE_NUM && right.sign == NEGATIVE_NUM) return true;

    for (int i = left.digit.size() - 1; i >= 0; --i)
    {
        if (left.digit[i] != right.digit[i])
        {
            return left.digit[i] > right.digit[i];
        }
    }

    return false;
}

bool operator>=(const Integer& left, const Integer& right)
{
    return left > right || left == right;
}

bool operator<(const Integer& left, const Integer& right)
{
    if (left.digit.size() != right.digit.size())
    {
        return left.digit.size() < right.digit.size();
    }

    if (left.sign == NEGATIVE_NUM && right.sign == POSITIVE_NUM) return true;

    for (int i = left.digit.size() - 1; i >= 0; --i)
    {
        if (left.digit[i] != right.digit[i])
        {
            return left.digit[i] < right.digit[i];
        }
    }

    return false;
}

bool operator<=(const Integer& left, const Integer& right)
{
    return left.digit < right.digit || left == right;
}

bool operator==(const Integer& left, const Integer& right)
{
    return left.digit == right.digit;
}

bool operator!=(const Integer& left, const Integer& right)
{
    return left.digit != right.digit;
}

void Integer::removeLeadingZeros()
{
    // 寻找第一个非零字符的索引
    size_t nonZeroIndex = digit.find_first_not_of('0');
    // 如果找到非零字符，则截取从该字符开始到末尾的子串作为新的数字表示
    digit = nonZeroIndex != std::string::npos ? digit.substr(nonZeroIndex) : "0";
}

Integer Integer::addPositive(const Integer& other) const
{
    Integer result;
    result.sign = POSITIVE_NUM;
    int len1 = length();
    int len2 = other.length();
    int carry = 0; // 进位

    // 从最低位开始逐位相加
    for (int i = 0; i < std::max(len1, len2) || carry; i++)
    {
        int sum = (i < len1 ? digit[len1 - i - 1] - '0' : 0) +
            (i < len2 ? other.digit[len2 - i - 1] - '0' : 0) + carry;

        result.digit += sum % 10 + '0';
        carry = sum / 10;
    }

    std::reverse(result.digit.begin(), result.digit.end());
    return result;
}

Integer Integer::subPositive(const Integer& other) const
{
    if (*this == other) return Integer("0");

    Integer result;
    result.sign = POSITIVE_NUM;

    int len1 = length();
    int len2 = other.length();
    int diff = 0; // 借位

    result.digit.resize(len1);

    for (int i = 0; i < len1; i++)
    {
        int less = (i < len1 ? digit[len1 - 1 - i] - '0' : 0) -
            (i < len2 ? other.digit[len2 - 1 - i] - '0' : 0) - diff;

        if (less < 0)
        {
            less += 10;
            diff = 1;
        }
        else
        {
            diff = 0;
        }
        result.digit[result.digit.size() - 1 - i] = less + '0'; // 处理数字，直接赋值到目标位置
    }

    result.removeLeadingZeros();
    return result;
}

Integer Integer::mulPositive(const Integer& other) const
{
    int len1 = digit.size();
    int len2 = other.digit.size();

    if (*this == "0" || other == "0") return Integer("0");

    Integer result;
    result.sign = POSITIVE_NUM;
    result.digit.resize(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0; // 进位
        for (int j = len2 - 1; j >= 0; j--)
        {
            int product = (digit[i] - '0') * (other.digit[j] - '0') +
                (result.digit[i + j + 1] - '0') + carry;

            carry = product / 10;
            result.digit[i + j + 1] = (product % 10) + '0';
        }
        result.digit[i] = carry + '0';
    }

    result.removeLeadingZeros();
    return result;
}

Integer Integer::divPositive(const Integer& other) const
{
    int len1 = digit.size();
    int len2 = other.digit.size();

    if (other.digit[0] == '0')
    {
        throw std::runtime_error("Divide by zero");
    }
    else if (*this < other)
    {
        throw std::runtime_error("The divisor cannot be less than the divisor");
    }
    else if (*this == other)
    {
        // 如果被除数等于除数，结果为1
        return Integer(1);
    }

    Integer result = "0";
    result.sign = POSITIVE_NUM;

    // 初始化一个零值的被除数
    Integer tmpDividend = "0";

    for (int i = 0; i < len1; i++)
    {
        // 将当前位加入到被除数后面
        tmpDividend = tmpDividend * 10 + Integer(digit.substr(i, 1));
        tmpDividend.sign = true;

        // 在每一位上尝试取商
        int quotient = 0;
        while (tmpDividend >= other)
        {
            tmpDividend -= other;
            quotient++;
        }

        // 将商的位数加入到结果中
        result = result * 10 + Integer(std::to_string(quotient));
    }

    return result;
}

Integer Integer::modPositive(const Integer& other) const
{
    return *this - (*this / other) * other;
}

