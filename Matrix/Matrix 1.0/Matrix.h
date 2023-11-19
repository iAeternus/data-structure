/*****************************************************************//**
 * \file   Matrix.h
 * \brief  ��������
 * 
 * \author ����ά
 * \date   September 2023
 *********************************************************************/
#pragma once

//#define TEST 1

const std::string RED_COLOR_CODE		= "\033[38;5;1m";   // �����ı���ɫΪ��ɫ�� ANSI ת����
const std::string GREEN_COLOR_CODE		= "\033[38;5;2m";   // �����ı���ɫΪ��ɫ�� ANSI ת����
const std::string YELLOW_COLOR_CODE		= "\033[38;5;3m";   // �����ı���ɫΪ��ɫ�� ANSI ת����
const std::string BLUE_COLOR_CODE		= "\033[38;5;4m";   // �����ı���ɫΪ��ɫ�� ANSI ת����
const std::string MAGENTA_COLOR_CODE	= "\033[38;5;5m";   // �����ı���ɫΪ���ɫ�� ANSI ת����
const std::string CYAN_COLOR_CODE		= "\033[38;5;6m";   // �����ı���ɫΪ��ɫ�� ANSI ת����
const std::string DEFAULT_COLOR_CODE	= "\033[0m";	    // �ָ�Ĭ���ı���ɫ��ANSIת����

class Matrix
{
public:
	Matrix(int row = 0, int col = 0, double value = 0);
	virtual ~Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	Matrix(Matrix&& other) noexcept;
	Matrix& operator=(Matrix&& other) noexcept;

	int getRow() const;
	int getCol() const;

	void clear(); // ��������ֵ
	void resize(int new_row, int new_col, double value = 0);

	double& get(int i, int j) const;
	double* operator[](int i) const;
	double& operator[](const std::pair<int, int>& indices) const;
	void set(int i, int j, double value);

	friend std::istream& operator>>(std::istream& in, Matrix& matrix);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

	Matrix& operator-(); // ��������
	Matrix operator+(const Matrix& other) const; // ����ӷ�
	Matrix operator-(const Matrix& other) const; // �������
	Matrix operator*(double value) const; // ���˾���
	friend Matrix operator*(double value, const Matrix& matrix); // num * Matrix
	Matrix operator*(const Matrix& other) const; // ����˷�
	static Matrix pow(const Matrix& matrix, int index); // ��������

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(double value);
	Matrix& operator*=(const Matrix& other);

	// �����ת��
	Matrix T();
	Matrix operator~();
	friend bool operator==(const Matrix& left, const Matrix& right);
	friend bool operator!=(const Matrix& left, const Matrix& right);

	// ������i�к͵�j��
	void rSwap(int i, int j);
	// ����i�г���ʵ��k
	void rMul(int i, const double& k);
	// ����i�г���ʵ��k�ӵ���j��
	void rAdd(int i, const double& k, int j);

	// ��ȡ��λ����
	static Matrix identity(int n);

	// �õ��������
	int rank() const;
	// �õ������
	Matrix inverse() const;
	// ��������ʽ
	double det() const;

	// �ⷽ���麯��
	void solve() const;

protected:
	int row; // ���� 
	int col; // ����
	double** coef; // ����

	// �ж��������ܷ���������
	bool can_be_linear(const Matrix& other) const;
	// �ж��������ܷ��������
	bool can_matrix_operations(const Matrix& other) const;
	// �жϷ���
	bool isPhalanx() const;
};
