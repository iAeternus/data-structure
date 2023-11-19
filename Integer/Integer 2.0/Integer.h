#pragma once

#define POSITIVE_NUM true // 正数
#define NEGATIVE_NUM false // 负数

class Integer
{
public:
	Integer();
	explicit Integer(const std::string& number);
	virtual ~Integer();

	void set(long long number);
	long long get() const;
	int length() const;
	bool sign() const;

	friend std::istream& operator>>(std::istream& in, Integer& number);
	friend std::ostream& operator<<(std::ostream& out, const Integer& number);

	// 正号运算
	Integer& operator+();
	// 负号运算
	Integer& operator-();
	// 绝对值运算
	Integer& abs();
	static Integer abs(const Integer& number);

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
	bool positive;				// 正负号
	std::vector<int> digits;    // 存储数字的动态数组
};