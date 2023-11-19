#include <iostream>
#include <vector>

#include "Integer.h"

Integer::Integer() :
	positive(POSITIVE_NUM)
{
	digits.push_back(0);
}

Integer::Integer(const std::string& number) :
	positive(number[0] == '-' ? NEGATIVE_NUM : POSITIVE_NUM)
{
	for (int i = number.size() - 1; i >= positive ? 0 : 1; --i)
	{
		digits.push_back(number[i] - '0');
	}
}

Integer::~Integer()
{}

void Integer::set(long long number)
{
	digits.clear();

	positive = number > 0;
	
	long long temp = number;
	while (temp > 0)
	{
		digits.push_back(number % 10);
		number /= 10;
	}
}

long long Integer::get() const
{
	if (digits.size() > 18)
	{
		throw std::runtime_error("Integer is too large");
	}

	long long number = 0;
	long long carry = 1;
	for (int i = 0; i < digits.size(); ++i)
	{
		number += digits[0] * carry;
		carry *= 10;
	}

	return number;
}

int Integer::length() const
{
	return digits.size();
}

bool Integer::sign() const
{
	return positive;
}

Integer& Integer::operator+()
{
	if (positive == NEGATIVE_NUM)
	{
		positive = POSITIVE_NUM;
	}
	return *this;
}

Integer& Integer::operator-()
{
	if (positive == POSITIVE_NUM)
	{
		positive = NEGATIVE_NUM;
	}
	return *this;
}

Integer& Integer::abs()
{
	if (!positive)
	{
		positive = POSITIVE_NUM;
	}
	return *this;
}

Integer Integer::abs(const Integer& number)
{
	Integer res = number;
	if (!number.positive)
	{
		res.positive = POSITIVE_NUM;
	}
	return res;
}

Integer Integer::operator+(const Integer& other) const
{
	if (positive && !other.positive) return *this - abs(other); // 正 + 负
	else if (!positive && other.positive) return other - abs(*this); // 负 + 正

	Integer result;
	result.positive = positive;
	int len1 = length();
	int len2 = other.length();
	int carry = 0; // 进位

	// 从最低位开始逐位相加
	for (int i = 0; i < std::max(len1, len2) || carry; i++)
	{
		int sum = (i < len1 ? digits[len1 - i - 1] : 0) +
			(i < len2 ? other.digits[len2 - i - 1] : 0) + carry;

		result.digits.push_back(sum % 10);
		carry = sum / 10;
	}

	std::reverse(result.digits.begin(), result.digits.end());

	// 移除结果高位的零
	while (result.digits.size() > 1 && result.digits.back() == 0)
	{
		result.digits.pop_back();
	}

	return result;
}

Integer Integer::operator-(const Integer& other) const
{
	if (positive && !other.positive) return *this + abs(other); // 正 - 负
	else if (!positive && other.positive) return -(abs(*this) + other); // 负 - 正
	else if (!positive && !other.positive) return abs(other) - abs(*this); // 负 - 负
	else if (positive && other.positive&&* this < other) return -(other - *this); // 小 - 大

	Integer zero;
	if (*this == other) return zero;

	Integer result;
	result.positive = *this > other;

	int len1 = length();
	int len2 = other.length();
	int diff = 0; // 借位

	result.digits.resize(std::max(len1, len2));

	for (int i = 0; i < std::max(len1, len2); i++)
	{
		int less = (i < len1 ? digits[len1 - 1 - i] : 0) -
			(i < len2 ? other.digits[len2 - 1 - i] : 0) - diff;

		if (less < 0)
		{
			less += 10;
			diff = 1;
		}
		else
		{
			diff = 0;
		}
		result.digits[result.digits.size() - 1 - i] = less; // 处理数字，直接赋值到目标位置
	}

	// 移除结果高位的零
	while (result.digits.size() > 1 && result.digits.back() == 0)
	{
		result.digits.pop_back();
	}

	return result;
}

Integer Integer::operator*(const Integer& other) const
{
	Integer result;
	result.digits.assign(digits.size() + other.digits.size(), 0);

	for (int i = 0; i < digits.size(); ++i)
	{
		int carry = 0;

		for (int j = 0; j < other.digits.size() || carry; ++j) 
		{
			long long product = result.digits[i + j] + carry +
				(long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0);
			result.digits[i + j] = product % 10;
			carry = product / 10;
		}
	}

	// 移除结果高位的零
	while (result.digits.size() > 1 && result.digits.back() == 0) 
	{
		result.digits.pop_back();
	}

	result.positive = !(positive ^ other.positive);
	return result;
}

Integer Integer::operator/(const Integer& other) const
{
	if (other.digits.size() == 1 && other.digits[0] == 0) 
	{
		throw std::runtime_error("Divide by zero");
	}

	Integer quotient;
	quotient.digits.assign(digits.size(), 0);

	Integer remainder;

	for (int i = digits.size() - 1; i >= 0; --i) 
	{
		remainder.digits.insert(remainder.digits.begin(), digits[i]);

		int digit = 0;

		while (remainder > other) 
		{
			remainder = remainder - other;
			++digit;
		}

		quotient.digits[i] = digit;
	}

	// 移除商的高位的零
	while (quotient.digits.size() > 1 && quotient.digits.back() == 0)
	{
		quotient.digits.pop_back();
	}

	quotient.positive = !(positive ^ other.positive);
	return quotient;
}

Integer Integer::operator%(const Integer& other) const
{
	if (other.digits.size() == 1 && other.digits[0] == 0)
	{
		throw std::runtime_error("Divide by zero");
	}

	Integer quotient;
	quotient.digits.assign(digits.size(), 0);

	Integer remainder;

	for (int i = digits.size() - 1; i >= 0; --i)
	{
		remainder.digits.insert(remainder.digits.begin(), digits[i]);

		int digit = 0;

		while (remainder > other) 
		{
			remainder = remainder - other;
			++digit;
		}

		quotient.digits[i] = digit;
	}

	// 移除商的高位的零
	while (quotient.digits.size() > 1 && quotient.digits.back() == 0) 
	{
		quotient.digits.pop_back();
	}

	remainder.positive = positive;
	return remainder;
}

Integer& Integer::operator+=(const Integer& other)
{
	return *this = *this + other;
}

Integer& Integer::operator-=(const Integer& other)
{
	return *this = *this - other;
}

Integer& Integer::operator*=(const Integer& other)
{
	return *this = *this * other;
}

Integer& Integer::operator/=(const Integer& other)
{
	return *this = *this / other;
}

Integer& Integer::operator%=(const Integer& other)
{
	return *this = *this % other;
}

Integer Integer::operator<<(int number) const
{
	std::string temp;
	for (int i = 0; i < number; ++i)
	{
		temp += '0';
	}

	Integer result(temp);

	for (int i = number; i < digits.size(); ++i)
	{
		result.digits[i] = digits[i];
	}

	return result;
}

Integer Integer::operator>>(int number) const
{
	if (number > digits.size())
	{
		throw std::runtime_error("The number of right shifts must be smaller than digits");
	}

	Integer result;

	for (int i = number; i < digits.size(); ++i)
	{
		result.digits.push_back(digits[i]);
	}

	return result;
}

Integer& Integer::operator<<=(int number)
{
	return *this = *this << number;
}

Integer& Integer::operator>>=(int number)
{
	return *this = *this >> number;
}

std::istream& operator>>(std::istream& in, Integer& number)
{
	std::string input;
	in >> input;

	number.digits.clear();
	number.positive = true;

	if (input[0] == '-') 
	{
		number.positive = false;
	}

	for (int i = input.length() - 1; i >= (number.positive ? 0 : 1); --i)
	{
		int digit = input[i] - '0';
		number.digits.push_back(digit);
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Integer& number)
{
	if (!number.positive)
	{
		out << "-";
	}

	for (int i = number.digits.size() - 1; i >= 0; --i)
	{
		out << number.digits[i];
	}

	return out;
}

bool operator>(const Integer& left, const Integer& right)
{
	if (left.digits.size() != right.digits.size())
	{
		return left.digits.size() > right.digits.size();
	}

	if (left.positive == POSITIVE_NUM && right.positive == NEGATIVE_NUM) return true;

	for (int i = left.digits.size() - 1; i >= 0; --i)
	{
		if (left.digits[i] != right.digits[i])
		{
			return left.digits[i] > right.digits[i];
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
	if (left.digits.size() != right.digits.size())
	{
		return left.digits.size() < right.digits.size();
	}

	if (left.positive == NEGATIVE_NUM && right.positive == POSITIVE_NUM) return true;

	for (int i = left.digits.size() - 1; i >= 0; --i)
	{
		if (left.digits[i] != right.digits[i])
		{
			return left.digits[i] < right.digits[i];
		}
	}

	return false;
}

bool operator<=(const Integer& left, const Integer& right)
{
	return left < right || left == right;
}

bool operator==(const Integer& left, const Integer& right)
{
	bool tag = left.length() == right.length();

	for (int i = 0; tag && i < left.length(); ++i)
	{
		if (left.digits[i] != right.digits[i])
		{
			tag = false;
		}
	}

	return tag;
}

bool operator!=(const Integer& left, const Integer& right)
{
	return !(left == right);
}
