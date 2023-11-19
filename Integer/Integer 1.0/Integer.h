/*****************************************************************//**
 * \file   Integer.h
 * \brief  十进制高精度数值计算
 * 
 * \author 吴子维
 * \date   September 2023
 *********************************************************************/
#pragma once

#define POSITIVE_NUM true // 正数
#define NEGATIVE_NUM false // 负数

//#define _STUDY_ // 测试

class Integer
{
public:
	Integer();
	Integer(long long number);
	Integer(const char* number);
	Integer(const std::string& digit);
	~Integer();
	Integer(const Integer& other);
	Integer& operator=(const Integer& other);
	Integer(Integer&& other) noexcept;
	Integer& operator=(Integer&& other) noexcept;

	void set(long long number);
	void set(const char* number);
	void set(const std::string& number);
	long long get() const;
	int length() const;
	bool isPositive() const;
	int getBit(int bit) const; // 获取从低位数起的第 bit 位

	friend std::istream& operator>>(std::istream& in, Integer& number);
	friend std::ostream& operator<<(std::ostream& out, const Integer& number);

	// 正号运算
	Integer& operator+();
	// 负号运算
	Integer& operator-();
	// 绝对值运算
	Integer& abs();
	static Integer abs(const Integer& number);
	// 整数指数运算
	static Integer pow(const Integer& base, long long index);

	Integer operator+(const Integer& other) const;
	Integer operator-(const Integer& other) const;
	Integer operator*(const Integer& other) const;
	Integer operator/(const Integer& other) const;
	Integer operator%(const Integer& other) const;

	Integer& operator+=(const Integer& other);
	Integer& operator-=(const Integer& other);
	Integer& operator*=(const Integer& other);
	Integer& operator/=(const Integer& other);
	Integer& operator%=(const Integer& other);

	// 左移
	Integer operator<<(int number) const;
	// 右移
	Integer operator>>(int number) const;

	Integer& operator<<=(int number);
	Integer& operator>>=(int number);

	friend bool operator>(const Integer& left, const Integer& right);
	friend bool operator>=(const Integer& left, const Integer& right);
	friend bool operator<(const Integer& left, const Integer& right);
	friend bool operator<=(const Integer& left, const Integer& right);
	friend bool operator==(const Integer& left, const Integer& right);
	friend bool operator!=(const Integer& left, const Integer& right);

protected:
	bool sign; // 符号标记 POSITIVE_NUM-正数 NEGATIVE_NUM-负数
	std::string digit; // 整数各位数字

private:
	void removeLeadingZeros(); // 去除前导 0

	Integer addPositive(const Integer& other) const;
	Integer subPositive(const Integer& other) const;
	Integer mulPositive(const Integer& other) const;
	Integer divPositive(const Integer& other) const;
	Integer modPositive(const Integer& other) const;
};
