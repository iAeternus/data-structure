#include <iostream>
#include <string>

#include "Integer.h"

Integer::Integer() :
	sign(POSITIVE_NUM), digit()
{
#ifdef _STUDY_
    std::cout << "���캯��-Ĭ��\n";
#endif
}

Integer::Integer(long long number)
{
	set(number);
#ifdef _STUDY_
    std::cout << "���캯��-long long ����\n";
#endif
}

Integer::Integer(const char* number)
{
    set(number);
#ifdef _STUDY_
    std::cout << "���캯��-const char* ����\n";
#endif
}

Integer::Integer(const std::string& digit)
{
    set(digit);
#ifdef _STUDY_
    std::cout << "���캯��-const std::string& ����\n";
#endif
}

Integer::~Integer()
{
#ifdef _STUDY_
    std::cout << "��������\n";
#endif
}

Integer::Integer(const Integer& other) :
	sign(other.sign), digit(other.digit)
{
#ifdef _STUDY_
    std::cout << "��������\n";
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
    std::cout << "������ֵ\n";
#endif
	return *this;
}

Integer::Integer(Integer&& other) noexcept :
    sign(other.sign), digit(std::move(other.digit))
{
#ifdef _STUDY_
    std::cout << "�ƶ�����\n";
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
    std::cout << "�ƶ���ֵ\n";
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
    // ����ָ�������
    if (index < 0)
    {
        throw std::runtime_error("The index requirement is positive");
    }
    else if (index == 0) return Integer(1); // �κ�����0�η���Ϊ1
    else if (index == 1) return const_cast<Integer&>(base); // �κ�����1�η�����������

    Integer result = "1";
    Integer number = base;

    while (index > 0)
    {
        if (index & 1) // �����ݣ�������������
        {
            result *= number; 
        }
        number *= number; // ����ƽ��
        index >>= 1; // ָ������ 2
    }

    return result;
}

Integer Integer::operator+(const Integer& other) const
{
    if (sign && !other.sign) return *this - abs(other); // �� + ��
    else if (!sign && other.sign) return other - abs(*this); // �� + ��
    else if (!sign && !other.sign) return -(abs(*this) + abs(other)); // �� + ��
    else return addPositive(other);
}

Integer Integer::operator-(const Integer& other) const
{
    if (sign && !other.sign) return *this + abs(other); // �� - ��
    else if (!sign && other.sign) return -(abs(*this) + other); // �� - ��
    else if (!sign && !other.sign) return abs(other) - abs(*this); // �� - ��
    else if (sign && other.sign && *this < other) return -(other - *this); // С - ��
    else return subPositive(other);
}

Integer Integer::operator*(const Integer& other) const
{
    Integer temp(abs(*this));
    if (!sign) return -temp.mulPositive(other);
    else if (!other.sign) return -mulPositive(abs(other));
    else return mulPositive(other);
}

Integer Integer::operator/(const Integer& other) const // TODO ��ѭ��
{
    Integer temp(abs(*this));
    if (sign && !other.sign) return -divPositive(abs(other)); // �� / ��
    else if (!sign && other.sign) return -temp.divPositive(other); // �� / ��
    else if (!sign && !other.sign) return temp.divPositive(abs(other)); // �� / ��
    else return divPositive(other);
}

Integer Integer::operator%(const Integer& other) const
{
    Integer temp(abs(*this));
    if (sign && !other.sign) return modPositive(abs(other)); // �� % ��
    else if (!sign && other.sign) return -temp.modPositive(other); // �� % ��
    else if (!sign && !other.sign) return -temp.modPositive(abs(other)); // �� % ��
    else if (sign && other.sign && *this < other) return *this; // С % ��
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
    // Ѱ�ҵ�һ�������ַ�������
    size_t nonZeroIndex = digit.find_first_not_of('0');
    // ����ҵ������ַ������ȡ�Ӹ��ַ���ʼ��ĩβ���Ӵ���Ϊ�µ����ֱ�ʾ
    digit = nonZeroIndex != std::string::npos ? digit.substr(nonZeroIndex) : "0";
}

Integer Integer::addPositive(const Integer& other) const
{
    Integer result;
    result.sign = POSITIVE_NUM;
    int len1 = length();
    int len2 = other.length();
    int carry = 0; // ��λ

    // �����λ��ʼ��λ���
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
    int diff = 0; // ��λ

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
        result.digit[result.digit.size() - 1 - i] = less + '0'; // �������֣�ֱ�Ӹ�ֵ��Ŀ��λ��
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
        int carry = 0; // ��λ
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
        // ������������ڳ��������Ϊ1
        return Integer(1);
    }

    Integer result = "0";
    result.sign = POSITIVE_NUM;

    // ��ʼ��һ����ֵ�ı�����
    Integer tmpDividend = "0";

    for (int i = 0; i < len1; i++)
    {
        // ����ǰλ���뵽����������
        tmpDividend = tmpDividend * 10 + Integer(digit.substr(i, 1));
        tmpDividend.sign = true;

        // ��ÿһλ�ϳ���ȡ��
        int quotient = 0;
        while (tmpDividend >= other)
        {
            tmpDividend -= other;
            quotient++;
        }

        // ���̵�λ�����뵽�����
        result = result * 10 + Integer(std::to_string(quotient));
    }

    return result;
}

Integer Integer::modPositive(const Integer& other) const
{
    return *this - (*this / other) * other;
}

