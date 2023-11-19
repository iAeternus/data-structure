/*****************************************************************//**
 * \file   Integer.h
 * \brief  ʮ���Ƹ߾�����ֵ����
 * 
 * \author ����ά
 * \date   September 2023
 *********************************************************************/
#pragma once

#define POSITIVE_NUM true // ����
#define NEGATIVE_NUM false // ����

//#define _STUDY_ // ����

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
	int getBit(int bit) const; // ��ȡ�ӵ�λ����ĵ� bit λ

	friend std::istream& operator>>(std::istream& in, Integer& number);
	friend std::ostream& operator<<(std::ostream& out, const Integer& number);

	// ��������
	Integer& operator+();
	// ��������
	Integer& operator-();
	// ����ֵ����
	Integer& abs();
	static Integer abs(const Integer& number);
	// ����ָ������
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

	// ����
	Integer operator<<(int number) const;
	// ����
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
	bool sign; // ���ű�� POSITIVE_NUM-���� NEGATIVE_NUM-����
	std::string digit; // ������λ����

private:
	void removeLeadingZeros(); // ȥ��ǰ�� 0

	Integer addPositive(const Integer& other) const;
	Integer subPositive(const Integer& other) const;
	Integer mulPositive(const Integer& other) const;
	Integer divPositive(const Integer& other) const;
	Integer modPositive(const Integer& other) const;
};
