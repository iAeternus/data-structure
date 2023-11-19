/*****************************************************************//**
 * \file   Matrix.h
 * \brief  矩阵类型
 * 
 * \author 吴子维
 * \date   September 2023
 *********************************************************************/
#pragma once

//#define TEST 1

const std::string RED_COLOR_CODE		= "\033[38;5;1m";   // 设置文本颜色为红色的 ANSI 转义码
const std::string GREEN_COLOR_CODE		= "\033[38;5;2m";   // 设置文本颜色为绿色的 ANSI 转义码
const std::string YELLOW_COLOR_CODE		= "\033[38;5;3m";   // 设置文本颜色为黄色的 ANSI 转义码
const std::string BLUE_COLOR_CODE		= "\033[38;5;4m";   // 设置文本颜色为蓝色的 ANSI 转义码
const std::string MAGENTA_COLOR_CODE	= "\033[38;5;5m";   // 设置文本颜色为洋红色的 ANSI 转义码
const std::string CYAN_COLOR_CODE		= "\033[38;5;6m";   // 设置文本颜色为青色的 ANSI 转义码
const std::string DEFAULT_COLOR_CODE	= "\033[0m";	    // 恢复默认文本颜色的ANSI转义码

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

	void clear(); // 给矩阵赋零值
	void resize(int new_row, int new_col, double value = 0);

	double& get(int i, int j) const;
	double* operator[](int i) const;
	double& operator[](const std::pair<int, int>& indices) const;
	void set(int i, int j, double value);

	friend std::istream& operator>>(std::istream& in, Matrix& matrix);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

	Matrix& operator-(); // 负号运算
	Matrix operator+(const Matrix& other) const; // 矩阵加法
	Matrix operator-(const Matrix& other) const; // 矩阵减法
	Matrix operator*(double value) const; // 数乘矩阵
	friend Matrix operator*(double value, const Matrix& matrix); // num * Matrix
	Matrix operator*(const Matrix& other) const; // 矩阵乘法
	static Matrix pow(const Matrix& matrix, int index); // 矩阵求幂

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(double value);
	Matrix& operator*=(const Matrix& other);

	// 矩阵的转置
	Matrix T();
	Matrix operator~();
	friend bool operator==(const Matrix& left, const Matrix& right);
	friend bool operator!=(const Matrix& left, const Matrix& right);

	// 交换第i行和第j行
	void rSwap(int i, int j);
	// 将第i行乘以实数k
	void rMul(int i, const double& k);
	// 将第i行乘以实数k加到第j行
	void rAdd(int i, const double& k, int j);

	// 获取单位矩阵
	static Matrix identity(int n);

	// 得到矩阵的秩
	int rank() const;
	// 得到逆矩阵
	Matrix inverse() const;
	// 方阵行列式
	double det() const;

	// 解方程组函数
	void solve() const;

protected:
	int row; // 行数 
	int col; // 列数
	double** coef; // 矩阵

	// 判断两矩阵能否线性运算
	bool can_be_linear(const Matrix& other) const;
	// 判断两矩阵能否矩阵运算
	bool can_matrix_operations(const Matrix& other) const;
	// 判断方阵
	bool isPhalanx() const;
};
