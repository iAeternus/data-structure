#pragma once

#define POSITIVE_NUM true // ����
#define NEGATIVE_NUM false // ����

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

	// ��������
	Integer& operator+();
	// ��������
	Integer& operator-();
	// ����ֵ����
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
	bool positive;				// ������
	std::vector<int> digits;    // �洢���ֵĶ�̬����
};