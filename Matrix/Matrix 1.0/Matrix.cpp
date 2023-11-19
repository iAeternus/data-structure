#include <iostream>

#include "Matrix.h"

Matrix::Matrix(int row, int col, double value) :
	row(row), col(col), coef(new double* [row])
{
#ifdef TEST
	std::cout << RED_COLOR_CODE << "���캯��" << DEFAULT_COLOR_CODE << std::endl;
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
	std::cout << GREEN_COLOR_CODE << "��������" << DEFAULT_COLOR_CODE << std::endl;
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
	std::cout << BLUE_COLOR_CODE << "�������캯��" << DEFAULT_COLOR_CODE << std::endl;
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
	std::cout << MAGENTA_COLOR_CODE << "������ֵ����" << DEFAULT_COLOR_CODE << std::endl;
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
	std::cout << YELLOW_COLOR_CODE << "�ƶ����캯��" << DEFAULT_COLOR_CODE << std::endl;
#endif
	other.row = 0;
	other.col = 0;
	other.coef = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
#ifdef TEST
	std::cout << CYAN_COLOR_CODE << "�ƶ���ֵ����" << DEFAULT_COLOR_CODE << std::endl;
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
	// ������Ч�����д�С
	if (new_row <= 0 || new_col <= 0) throw std::invalid_argument("Invalid matrix dimensions.");

	// ����´�С�뵱ǰ��С��ͬ���������
	if (new_row == this->row && new_col == this->col) return;

	// �����¾���
	double** new_matrix = new double* [new_row];
	for (int i = 0; i < new_row; i++)
	{
		new_matrix[i] = new double[new_col];
		for (int j = 0; j < new_col; j++)
		{
			if (i < this->row && j < this->col)
			{
				// ��������Ԫ��
				new_matrix[i][j] = this->coef[i][j];
			}
			else
			{
				// ʹ��Ĭ��ֵ�����Ԫ��
				new_matrix[i][j] = value;
			}
		}
	}

	for (int i = 0; i < this->row; i++)
	{
		delete[] this->coef[i];
	}
	delete[] this->coef;

	// �������д�С�;���ָ��
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
	std::cout << "������������������ > ";
	in >> row >> col;
	matrix.resize(row, col);

	std::cout << "�������Ԫ�� > \n";
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
	// �����������
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
	// �����������
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

	for (int i = 0; i < this->row; i++) // ������һ���������
	{
		for (int j = 0; j < other.col; j++) // �����ڶ����������
		{
			result.coef[i][j] = 0; // ��ʼ���������Ԫ��Ϊ 0
			for (int k = 0; k < this->col; k++)
			{
				result.coef[i][j] += this->coef[i][k] * other.coef[k][j]; // ����˷�
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
	Matrix result = Matrix::identity(n); // ��ʼ���������Ϊ��λ����

	Matrix base = matrix;

	while (index > 0)
	{
		if (index & 1) // ��������
		{
			result = result * base;
		}

		base = base * base; // ��������ƽ��
		index >>= 1; // ����һλ���൱�ڳ���2
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

	if (i == j) // i j ��ȣ����轻��
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

		// �ҵ���ǰ�е�һ������Ԫ�ص�λ�ã���Ԫ�أ�
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

			// ����Ԫ�������й�һ��
			double pivotValue = temp.coef[i][pivot];
			for (int j = 0; j < colCount; j++)
			{
				temp.coef[i][j] /= pivotValue;
			}

			// ʹ����Ԫ�ص��������������е���ӦԪ��
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

	// ��˹-Լ����Ԫ��
	for (int i = 0; i < n; i++)
	{
		// �ҵ���Ԫ�ص�λ��
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

		// ������ǰ�к���Ԫ��������
		if (pivot != i)
		{
			temp.rSwap(i, pivot);
			result.rSwap(i, pivot);
		}

		// ����Ԫ�������й�һ��
		double pivotValue = temp.coef[i][i];
		for (int j = 0; j < n; j++)
		{
			temp.coef[i][j] /= pivotValue;
			result.coef[i][j] /= pivotValue;
		}

		// ʹ����Ԫ�ص��������������е���ӦԪ��
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
	Matrix temp(*this); // ������ʱ���������޸�ԭʼ����
	double determinant = 1;

	// ��˹��Ԫ����������ʽ  
	for (int i = 0; i < n; i++)
	{
		int pivot = i;
		for (int j = i + 1; j < n; j++)
		{
			if (std::abs(temp.coef[i][j]) > std::abs(temp.coef[pivot][i]))
			{
				pivot = i; // �ҵ����о���ֵ����Ԫ�����ڵ���
			}
		}

		if (temp.coef[pivot][i] == 0)
		{
			return 0; // �����Ԫ��Ϊ�㣬���������ʽҲΪ��  
		}

		if (pivot != i)
		{
			temp.rSwap(i, pivot); // ������ǰ�к���Ԫ�����ڵ���
			determinant = -determinant; // �н����ı�����ʽ�ķ���
		}

		determinant *= temp.coef[i][i]; // �ۻ���Ԫ��

		for (int k = i + 1; k < n; k++)
		{
			double factor = temp.coef[k][i] / temp.coef[i][i]; // ����Ҫ������ϵ��
			temp.rAdd(i, -factor, k); // ����i�е�-factor���ӵ���k��
		}
	}

	return determinant; // ���ؼ���õ�������ʽֵ  
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

