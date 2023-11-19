#include <iostream>

#include "Matrix.h"

Matrix::Matrix(int row, int col, double value) :
	row(row), col(col), coef(new double* [row])
{
#ifdef TEST
	std::cout << RED_COLOR_CODE << "构造函数" << DEFAULT_COLOR_CODE << std::endl;
#endif
	for (int i = 0; i < row; i++)
	{
		coef[i] = new double[col];

		if (value != 0)
		{
			for (int j = 0; j < col; j++)
			{
				coef[i][j] = value;
			}
		}
	}
}

Matrix::~Matrix()
{
#ifdef TEST
	std::cout << GREEN_COLOR_CODE << "析构函数" << DEFAULT_COLOR_CODE << std::endl;
#endif
	for (int i = 0; i < row; i++)
	{
		delete[] coef[i];
	}
	delete[] coef;
	coef = nullptr;
}

Matrix::Matrix(const Matrix& other) :
	row(other.row), col(other.col), coef(new double* [row])
{
#ifdef TEST
	std::cout << BLUE_COLOR_CODE << "拷贝构造函数" << DEFAULT_COLOR_CODE << std::endl;
#endif
	for (int i = 0; i < row; i++)
	{
		coef[i] = new double[col];

		for (int j = 0; j < col; j++)
		{
			coef[i][j] = other.coef[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& other)
{
#ifdef TEST
	std::cout << MAGENTA_COLOR_CODE << "拷贝赋值函数" << DEFAULT_COLOR_CODE << std::endl;
#endif
	if (this != &other)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] coef[i];
		}
		delete[] coef;

		this->row = other.row;
		this->col = other.col;

		double** new_matrix = new double* [row];
		for (int i = 0; i < row; i++)
		{
			new_matrix[i] = new double[col];

			for (int j = 0; j < col; j++)
			{
				new_matrix[i][j] = other.coef[i][j];
			}
		}

		this->coef = new_matrix;
	}
	return *this;
}

Matrix::Matrix(Matrix&& other) noexcept :
	row(other.row), col(other.col), coef(other.coef)
{
#ifdef TEST
	std::cout << YELLOW_COLOR_CODE << "移动构造函数" << DEFAULT_COLOR_CODE << std::endl;
#endif
	other.row = 0;
	other.col = 0;
	other.coef = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
#ifdef TEST
	std::cout << CYAN_COLOR_CODE << "移动赋值函数" << DEFAULT_COLOR_CODE << std::endl;
#endif
	if (this != &other)
	{
		this->row = other.row;
		this->col = other.col;
		this->coef = other.coef;

		other.row = 0;
		other.col = 0;
		other.coef = nullptr;
	}
	return *this;
}

int Matrix::getRow() const
{
	return this->row;
}

int Matrix::getCol() const
{
	return this->col;
}

void Matrix::clear()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->coef[i][j] = 0;
		}
	}
}

void Matrix::resize(int new_row, int new_col, double value)
{
	// 处理无效的行列大小
	if (new_row <= 0 || new_col <= 0) throw std::invalid_argument("Invalid matrix dimensions.");

	// 如果新大小与当前大小相同，无需调整
	if (new_row == this->row && new_col == this->col) return;

	// 创建新矩阵
	double** new_matrix = new double* [new_row];
	for (int i = 0; i < new_row; i++)
	{
		new_matrix[i] = new double[new_col];
		for (int j = 0; j < new_col; j++)
		{
			if (i < this->row && j < this->col)
			{
				// 复制现有元素
				new_matrix[i][j] = this->coef[i][j];
			}
			else
			{
				// 使用默认值填充新元素
				new_matrix[i][j] = value;
			}
		}
	}

	for (int i = 0; i < this->row; i++)
	{
		delete[] this->coef[i];
	}
	delete[] this->coef;

	// 更新行列大小和矩阵指针
	this->row = new_row;
	this->col = new_col;
	this->coef = new_matrix;
}

double& Matrix::get(int i, int j) const
{
	if (i < 0 || i >= this->row || j < 0 || j >= this->col)
	{
		throw std::invalid_argument("Invalid matrix dimensions.");
	}
	return this->coef[i][j];
}

double* Matrix::operator[](int i) const
{
	if (i < 0 || i >= this->row)
	{
		throw std::invalid_argument("Invalid matrix dimensions.");
	}
	return this->coef[i];
}

double& Matrix::operator[](const std::pair<int, int>& indices) const
{
	int i = indices.first;
	int j = indices.second;
	if (i < 0 || i >= this->row || j < 0 || j >= this->col)
	{
		throw std::invalid_argument("Invalid matrix dimensions.");
	}
	return this->coef[i][j];
}

void Matrix::set(int i, int j, double value)
{
	if (i < 0 || i >= this->row || j < 0 || j >= this->col)
	{
		throw std::invalid_argument("Invalid matrix dimensions.");
	}
	this->coef[i][j] = value;
}

std::istream& operator>>(std::istream& in, Matrix& matrix)
{
	int row, col;
	std::cout << "输入矩阵的行数和列数 > ";
	in >> row >> col;
	matrix.resize(row, col);

	std::cout << "输入矩阵元素 > \n";
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.col; j++)
		{
			in >> matrix.coef[i][j];
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.col; j++)
		{
			out << matrix.coef[i][j] << '\t';
		}
		if (i != matrix.row - 1)
		{
			out << '\n';
		}
	}
	return out;
}

Matrix& Matrix::operator-()
{
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			this->coef[i][j] = -this->coef[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
	// 两矩阵不能相加
	if (!can_be_linear(other)) throw std::invalid_argument("Matrix addition is not possible.");

	Matrix result(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result.coef[i][j] = this->coef[i][j] + other.coef[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
	// 两矩阵不能相减
	if (!can_be_linear(other)) throw std::invalid_argument("Matrix subtraction is not possible.");

	Matrix result(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result.coef[i][j] = this->coef[i][j] - other.coef[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator*(double value) const
{
	Matrix result(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result.coef[i][j] = value * this->coef[i][j];
		}
	}

	return result;
}

Matrix operator*(double value, const Matrix& matrix)
{
	Matrix result(matrix.row, matrix.col);

	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.col; j++)
		{
			result.coef[i][j] = value * matrix.coef[i][j];
		}
	}

	return result;
}

bool operator==(const Matrix& left, const Matrix& right)
{
	bool tag = left.row == right.row && left.col == right.col;

	for (int i = 0; tag && i < left.row; i++)
	{
		for (int j = 0; tag && j < left.col; j++)
		{
			tag = left.coef[i][j] == right.coef[i][j];
		}
	}

	return tag;
}

bool operator!=(const Matrix& left, const Matrix& right)
{
	return !(left == right);
}

Matrix Matrix::operator*(const Matrix& other) const
{
	if (!can_matrix_operations(other)) throw std::invalid_argument("Matrix multiplication is not possible.");

	Matrix result(this->row, other.col);

	for (int i = 0; i < this->row; i++) // 遍历第一个矩阵的行
	{
		for (int j = 0; j < other.col; j++) // 遍历第二个矩阵的列
		{
			result.coef[i][j] = 0; // 初始化结果矩阵元素为 0
			for (int k = 0; k < this->col; k++)
			{
				result.coef[i][j] += this->coef[i][k] * other.coef[k][j]; // 矩阵乘法
			}
		}
	}

	return result;
}

Matrix Matrix::pow(const Matrix& matrix, int index)
{
	if (!matrix.isPhalanx())
	{
		throw std::invalid_argument("Matrix must be a square matrix for matrix exponentiation.");
	}

	int n = matrix.row;
	Matrix result = Matrix::identity(n); // 初始化结果矩阵为单位矩阵

	Matrix base = matrix;

	while (index > 0)
	{
		if (index & 1) // 奇数次幂
		{
			result = result * base;
		}

		base = base * base; // 计算矩阵的平方
		index >>= 1; // 右移一位，相当于除以2
	}

	return result;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	*this = std::move(*this + other);
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	*this = std::move(*this - other);
	return *this;
}

Matrix& Matrix::operator*=(double value)
{
	*this = std::move(*this * value);
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	*this = std::move(*this * other);
	return *this;
}


Matrix Matrix::T()
{
	Matrix result(this->col, this->row);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result.coef[j][i] = this->coef[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator~()
{
	return this->T();
}

void Matrix::rSwap(int i, int j)
{
	if (i < 0 || i >= this->row || j < 0 || j >= this->row)
	{
		throw std::out_of_range("Invalid row index. The specified row does not exist.");
	}

	if (i == j) // i j 相等，无需交换
	{
		return;
	}

	for (int index_j = 0; index_j < this->col; index_j++)
	{
		std::swap(this->coef[i][index_j], this->coef[j][index_j]);
	}
}

void Matrix::rMul(int i, const double& k)
{
	if (i < 0 || i >= this->row)
	{
		throw std::out_of_range("Invalid row index. The specified row does not exist.");
	}
	for (int index_j = 0; index_j < this->col; index_j++)
	{
		this->coef[i][index_j] *= k;
	}
}

void Matrix::rAdd(int i, const double& k, int j)
{
	if (i < 0 || i >= this->row || j < 0 || j >= this->row)
	{
		throw std::out_of_range("Invalid row index. The specified row does not exist.");
	}
	for (int index_j = 0; index_j < this->col; index_j++)
	{
		this->coef[j][index_j] += this->coef[i][index_j] * k;
	}
}

Matrix Matrix::identity(int n)
{
	Matrix result(n, n, 0);

	for (int i = 0; i < n; ++i)
	{
		result.set(i, i, 1.0);
	}

	return result;
}

int Matrix::rank() const
{
	Matrix temp(*this);
	int rowCount = temp.row;
	int colCount = temp.col;
	int rank = 0;

	for (int i = 0; i < rowCount; i++)
	{
		int pivot = -1;

		// 找到当前行第一个非零元素的位置（主元素）
		for (int j = 0; j < colCount; j++)
		{
			if (temp.coef[i][j] != 0)
			{
				pivot = j;
				break;
			}
		}

		if (pivot != -1)
		{
			rank++;

			// 将主元素所在行归一化
			double pivotValue = temp.coef[i][pivot];
			for (int j = 0; j < colCount; j++)
			{
				temp.coef[i][j] /= pivotValue;
			}

			// 使用主元素的行消除其他行中的相应元素
			for (int k = 0; k < rowCount; k++)
			{
				if (k != i)
				{
					double factor = -temp.coef[k][pivot];
					for (int j = 0; j < colCount; j++)
					{
						temp.coef[k][j] += factor * temp.coef[i][j];
					}
				}
			}
		}
	}

	return rank;
}

Matrix Matrix::inverse() const // TODO
{
	int n = this->row;
	if (n != this->col)
	{
		throw std::invalid_argument("Matrix is not square, so it doesn't have an inverse.");
	}

	Matrix result(n, n);
	Matrix temp(*this);

	// 高斯-约当消元法
	for (int i = 0; i < n; i++)
	{
		// 找到主元素的位置
		int pivot = i;
		for (int j = i + 1; j < n; j++)
		{
			if (std::abs(temp.coef[j][i]) > std::abs(temp.coef[pivot][i]))
			{
				pivot = j;
			}
		}

		if (temp.coef[pivot][i] == 0)
		{
			throw std::invalid_argument("Matrix is singular, so it doesn't have an inverse.");
		}

		// 交换当前行和主元素所在行
		if (pivot != i)
		{
			temp.rSwap(i, pivot);
			result.rSwap(i, pivot);
		}

		// 将主元素所在行归一化
		double pivotValue = temp.coef[i][i];
		for (int j = 0; j < n; j++)
		{
			temp.coef[i][j] /= pivotValue;
			result.coef[i][j] /= pivotValue;
		}

		// 使用主元素的行消除其他行中的相应元素
		for (int k = 0; k < n; k++)
		{
			if (k != i)
			{
				double factor = temp.coef[k][i];
				for (int j = 0; j < n; j++)
				{
					temp.coef[k][j] -= factor * temp.coef[i][j];
					result.coef[k][j] -= factor * result.coef[i][j];
				}
			}
		}
	}

	return result;
}

double Matrix::det() const
{
	if (!isPhalanx())
	{
		throw std::invalid_argument("Matrix is not square, so it doesn't have a determinant.");
	}

	int n = row;
	Matrix temp(*this); // 创建临时矩阵，以免修改原始矩阵
	double determinant = 1;

	// 高斯消元法计算行列式  
	for (int i = 0; i < n; i++)
	{
		int pivot = i;
		for (int j = i + 1; j < n; j++)
		{
			if (std::abs(temp.coef[i][j]) > std::abs(temp.coef[pivot][i]))
			{
				pivot = i; // 找到列中绝对值最大的元素所在的行
			}
		}

		if (temp.coef[pivot][i] == 0)
		{
			return 0; // 如果主元素为零，矩阵的行列式也为零  
		}

		if (pivot != i)
		{
			temp.rSwap(i, pivot); // 交换当前行和主元素所在的行
			determinant = -determinant; // 行交换改变行列式的符号
		}

		determinant *= temp.coef[i][i]; // 累积主元素

		for (int k = i + 1; k < n; k++)
		{
			double factor = temp.coef[k][i] / temp.coef[i][i]; // 计算要消除的系数
			temp.rAdd(i, -factor, k); // 将第i行的-factor倍加到第k行
		}
	}

	return determinant; // 返回计算得到的行列式值  
}

void Matrix::solve() const // TODO
{
}

bool Matrix::can_be_linear(const Matrix& other) const
{
	return this->row == other.row && this->col == other.col;
}

bool Matrix::can_matrix_operations(const Matrix& other) const
{
	return this->col == other.row;
}

bool Matrix::isPhalanx() const
{
	return this->row == this->col;
}

