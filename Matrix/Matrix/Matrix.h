#pragma once
#include <functional>
#include <exception>

// �����쳣��
class MatrixException : public std::exception
{
public:
	MatrixException(const std::string& message) : message(message) {}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string message;
};

template<typename T>
class Matrix
{
public:
	explicit Matrix();
	explicit Matrix(int row, int col);
	explicit Matrix(int row, int col, const T& value);
	explicit Matrix(int row, int col, T&& value);
	explicit Matrix(int row, int col, const T* values, int size);
	explicit Matrix(int row, int col, const std::vector<T>& values);
	virtual ~Matrix();
	Matrix(const Matrix<T>& other);
	Matrix<T>& operator=(const Matrix<T>& other);
	Matrix(Matrix<T>&& other) noexcept;
	Matrix<T>& operator=(Matrix<T>&& other) noexcept;

	int getRow() const;
	int getCol() const;
	T get(int row, int col) const;
	int getSize() const;

	T*& operator[](int row);
	const T*& operator[](int row) const;
	void set(int row, int col, const T& value);
	void set(int row, int col, T&& value);

	// ����ָ���е�Ԫ��
	bool for_each_elemOfTheRow(int row, const std::function<bool(T&)>& func);
	bool for_each_elemOfTheRow(int row, const std::function<bool(const T&)>& func) const;
	// ����ָ���е�Ԫ��
	bool for_each_elemOfTheCol(int col, const std::function<bool(T&)>& func);
	bool for_each_elemOfTheCol(int col, const std::function<bool(const T&)>& func) const;
	// ���������е�����Ԫ��
	bool for_each_elemOfTheMatrix(const std::function<bool(T&)>& func);
	bool for_each_elemOfTheMatrix(const std::function<bool(const T&)>& func) const;

	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

	Matrix<T>& operator-(); // ��������
	Matrix<T> operator+(const Matrix<T>& other) const; // ����ӷ�
	Matrix<T> operator-(const Matrix<T>& other) const; // �������
	Matrix<T> operator*(T value) const; // ���˾���
	template<typename T>
	friend Matrix<T> operator*(T value, const Matrix<T>& matrix); // num * Matrix
	Matrix<T> operator*(const Matrix<T>& other) const; // ����˷�
	static Matrix<T> pow(const Matrix<T>& matrix, int index); // ��������

	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator-=(const Matrix<T>& other);
	Matrix<T>& operator*=(T value);
	Matrix<T>& operator*=(const Matrix<T>& other);

	// �����ת��
	Matrix<T> transpose();
	Matrix<T> operator~();

	template<typename T>
	friend bool operator==(const Matrix<T>& left, const Matrix<T>& right);
	template<typename T>
	friend bool operator!=(const Matrix<T>& left, const Matrix<T>& right);

	// �ó���Ϊsize�������滻��i��
	void replaseRow(int row, const T* values, int size);
	void replaseRow(int row, const std::vector<T>& values);
	// �ó���Ϊsize�������滻��j��
	void replaseCol(int col, const T* values, int size);
	void replaseCol(int col, const std::vector<T>& values);

	// ��ȡ��λ����
	static Matrix<T> identity(int n);

	// ������i�к͵�j��
	void rSwap(int i, int j);
	// ����i�г���ʵ��k
	void rMul(int i, const T& k);
	// ����i�г���ʵ��k�ӵ���j��
	void rAdd(int i, const T& k, int j);

	// �õ��������
	int rank() const;
	// �õ������
	Matrix<T> inverse() const;
	// ��������ʽ
	T det() const;

	// �ⷽ���麯��
	void solve() const;

protected:
	int row; // ����
	int col; // ����
	T** coef; // ����

	// �ж������Ƿ�Ϸ�
	bool isValidRow(int row) const;
	bool isValidCol(int col) const;
	bool isValidPosition(int row, int col) const;

	// �Ƿ�����������
	static bool canLinearly(const Matrix<T>& left, const Matrix<T>& right);
	// �Ƿ��ܾ�������
	static bool canMatrixOperations(const Matrix<T>& left, const Matrix<T>& right);
	// �Ƿ��Ƿ���
	static bool isPhalanx(const Matrix<T>& matrix);
};

template<typename T>
inline Matrix<T>::Matrix() :
	row(0), col(0), coef(nullptr)
{}

template<typename T>
inline Matrix<T>::Matrix(int row, int col) :
	row(row), col(col), coef(new T* [row])
{
	for (int i = 0; i < this->row; ++i)
	{
		coef[i] = new T[this->col];
		for (int j = 0; j < this->col; ++j)
		{
			coef[i][j] = 0;
		}
	}
}

template<typename T>
inline Matrix<T>::Matrix(int row, int col, const T& value) :
	row(row), col(col), coef(new T* [row])
{
	for (int i = 0; i < this->row; ++i)
	{
		coef[i] = new T[this->col];
		for (int j = 0; j < this->col; ++j)
		{
			coef[i][j] = value;
		}
	}
}

template<typename T>
inline Matrix<T>::Matrix(int row, int col, T&& value) :
	row(row), col(col), coef(new T* [row])
{
	for (int i = 0; i < this->row; ++i)
	{
		coef[i] = new T[this->col];
		for (int j = 0; j < this->col; ++j)
		{
			coef[i][j] = std::move(value);
		}
	}
}

template<typename T>
inline Matrix<T>::Matrix(int row, int col, const T* values, int size) :
	row(row), col(col), coef(new T* [row])
{
	int index = 0;
	for (int i = 0; i < this->row; ++i)
	{
		coef[i] = new T[this->col];
		for (int j = 0; j < this->col; ++j)
		{
			coef[i][j] = values[index++];
		}
	}
}

template<typename T>
inline Matrix<T>::Matrix(int row, int col, const std::vector<T>& values) :
	row(row), col(col), coef(new T* [row])
{
	int index = 0;
	for (int i = 0; i < this->row; ++i)
	{
		coef[i] = new T[this->col];
		for (int j = 0; j < this->col; ++j)
		{
			coef[i][j] = values.at(index++);
		}
	}
}

template<typename T>
inline Matrix<T>::~Matrix()
{
	for (int i = 0; i < this->row; ++i)
	{
		delete[] coef[i];
		coef[i] = nullptr;
	}
	delete[] coef;
	coef = nullptr;
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix<T>& other) :
	row(other.row), col(other.col), coef(new T* [row])
{
	for (int i = 0; i < row; ++i)
	{
		coef[i] = new T[this->col];
		for (int j = 0; j < col; ++j)
		{
			coef[i][j] = other.get(i, j);
		}
	}
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	if(this != &other)
	{
		this->row = other.row;
		this->col = other.col;
		this->coef = new T * [this->row];

		for (int i = 0; i < this->row; ++i)
		{
			coef[i] = new T[this->col];
			for (int j = 0; j < this->col; ++j)
			{
				coef[i][j] = other.get(i, j);
			}
		}
	}
	return *this;
}

template<typename T>
inline Matrix<T>::Matrix(Matrix<T>&& other) noexcept :
	row(other.row), col(other.col), coef(std::move(other.coef))
{}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
	if (this != &other)
	{
		this->row = other.row;
		this->col = other.col;
		this->coef = std::move(other.coef);
	}
	return *this;
}

template<typename T>
inline int Matrix<T>::getRow() const
{
	return this->row;
}

template<typename T>
inline int Matrix<T>::getCol() const
{
	return this->col;
}

template<typename T>
inline T Matrix<T>::get(int row, int col) const
{
	if (!isValidRow(row) || !isValidCol(col))
	{
		throw MatrixException("Invalid row or column index");
	}
	return this->coef[row][col];
}

template<typename T>
inline int Matrix<T>::getSize() const
{
	return this->row * this->col;
}

template<typename T>
inline T*& Matrix<T>::operator[](int row)
{
	if (!isValidRow(row))
	{
		throw MatrixException("Invalid row idnex");
	}
	return this->coef[row];
}

template<typename T>
inline const T*& Matrix<T>::operator[](int row) const
{
	if (!isValidRow(row))
	{
		throw MatrixException("Invalid row idnex");
	}
	return this->coef[row];
}

template<typename T>
inline void Matrix<T>::set(int row, int col, const T& value)
{
	if (!isValidRow(row) || !isValidCol(col))
	{
		throw MatrixException("Invalid row or column index");
	}
	this->coef[row][col] = value;
}

template<typename T>
inline void Matrix<T>::set(int row, int col, T&& value)
{
	if (!isValidRow(row) || !isValidCol(col))
	{
		throw MatrixException("Invalid row or column index");
	}
	this->coef[row][col] = std::move(value);
}

template<typename T>
inline bool Matrix<T>::for_each_elemOfTheRow(int row, const std::function<bool(T&)>& func)
{
	for (int j = 0; j < this->col; ++j)
	{
		if (!func(this->coef[row][j])) // �ص��������� false����ֹ����
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool Matrix<T>::for_each_elemOfTheRow(int row, const std::function<bool(const T&)>& func) const
{
	for (int j = 0; j < this->col; ++j)
	{
		if (!func(this->get(row, j))) // �ص��������� false����ֹ����
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool Matrix<T>::for_each_elemOfTheCol(int col, const std::function<bool(T&)>& func)
{
	for (int i = 0; i < this->col; ++i)
	{
		if (!func(this->get(i, col))) // �ص��������� false����ֹ����
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool Matrix<T>::for_each_elemOfTheCol(int col, const std::function<bool(const T&)>& func) const
{
	for (int i = 0; i < this->col; ++i)
	{
		if (!func(this->get(i, col))) // �ص��������� false����ֹ����
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool Matrix<T>::for_each_elemOfTheMatrix(const std::function<bool(T&)>& func)
{
	int size = getSize();
	for (int i = 0; i < size; ++i)
	{
		if (!func(this->values[i])) // �ص��������� false����ֹ����
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool Matrix<T>::for_each_elemOfTheMatrix(const std::function<bool(const T&)>& func) const
{
	int size = getSize();
	for (int i = 0; i < size; ++i)
	{
		if (!func(this->values[i])) // �ص��������� false����ֹ����
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator-()
{
	for_each_elemOfTheMatrix([](T& value)->bool {
		value = -value;
		return true;
	});
	return *this;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	if (!canLinearly(*this, other))
	{
		throw MatrixException("Matrix dimensions are not compatible for addition");
	}

	Matrix<T> result(row, col);

	for (int i = 0; i < result.row; ++i)
	{
		for (int j = 0; j < result.col; ++j)
		{
			result.set(i, j, this->get(i, j) + other.get(i, j));
		}
	}

	return result;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
	if (!canLinearly(*this, other))
	{
		throw MatrixException("Matrix dimensions are not compatible for subtraction");
	}

	Matrix<T> result(row, col);

	for (int i = 0; i < result.row; ++i)
	{
		for (int j = 0; j < result.col; ++j)
		{
			result.set(i, j, this->get(i, j) - other.get(i, j));
		}
	}

	return result;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator*(T value) const
{
	Matrix<T> result(row, col);

	for (int i = 0; i < result.row; ++i)
	{
		for (int j = 0; j < result.col; ++j)
		{
			result.set(i, j, value * this->get(i, j));
		}
	}

	return result;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
	for (int i = 0; i < matrix.row; ++i)
	{
		for (int j = 0; j < matrix.col; ++j)
		{
			out << matrix.get(i, j) << '\t';
		}
		out << '\n';
	}
	return out;
}

template<typename T>
Matrix<T> operator*(T value, const Matrix<T>& matrix)
{
	Matrix<T> result(matrix.row, matrix.col);

	for (int i = 0; i < result.row; ++i)
	{
		for (int j = 0; j < result.col; ++j)
		{
			result.set(i, j, value * matrix.get(i, j));
		}
	}

	return result;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	if (!canMatrixOperations(*this, other))
	{
		throw MatrixException("Matrix dimensions are not compatible for multiplication");
	}

	Matrix<T> result(this->row, other.col);

	for (int i = 0; i < this->row; i++) // ������һ���������
	{
		for (int j = 0; j < other.col; j++) // �����ڶ����������
		{
			result.set(i, j, 0); // ��ʼ���������Ԫ��Ϊ 0
			for (int k = 0; k < this->col; k++)
			{
				result.set(i, j, result.get(i, j) + this->get(i, k) * other.get(k, j));
			}
		}
	}

	return result;
}

template<typename T>
inline Matrix<T> Matrix<T>::pow(const Matrix<T>& matrix, int index)
{
	if (!isPhalanx(matrix))
	{
		throw MatrixException("Matrix must be a square matrix for matrix exponentiation.");
	}

	int n = matrix.row;
	Matrix<T> result = Matrix<T>::identity(n); // ��ʼ���������Ϊ��λ����

	Matrix<T> base = matrix;

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

template<typename T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
	return *this = *this + other;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
	return *this = *this - other;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(T value)
{
	return *this = *this * value;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
{
	return *this = *this * other;
}

template<typename T>
inline Matrix<T> Matrix<T>::transpose() // TODO
{
	Matrix<T> result(row, col);

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			result.set(j, i, this->get(i, j));
		}
	}
	return result;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator~()
{
	return transpose();
}

template<typename T>
bool operator==(const Matrix<T>& left, const Matrix<T>& right)
{
	int size = left.getSize();
	bool tag = left.getSize() == right.getSize();
	for (int i = 0; tag && i < size; ++i)
	{
		if (left.values[i] != right.values[i])
		{
			tag = false;
		}
	}
	return tag;
}

template<typename T>
bool operator!=(const Matrix<T>& left, const Matrix<T>& right)
{
	return !(left == right);
}

template<typename T>
inline void Matrix<T>::replaseRow(int row, const T* values, int size)
{
	if (!isValidRow(row))
	{
		throw MatrixException("Invalid row index");
	}

	if (size != this->col)
	{
		throw MatrixException("Size of 'values' array does not match the number of columns in the matrix");
	}

	for (int j = 0; j < size; ++j)
	{
		this->set(row, j, values[j]);
	}
}

template<typename T>
inline void Matrix<T>::replaseRow(int row, const std::vector<T>& values)
{
	if (!isValidRow(row))
	{
		throw MatrixException("Invalid row index");
	}

	if (values.size() != this->col)
	{
		throw MatrixException("Size of 'values' array does not match the number of columns in the matrix");
	}

	for (int j = 0; j < values.size(); ++j)
	{
		this->get(row, j) = values.at(j);
	}
}

template<typename T>
inline void Matrix<T>::replaseCol(int col, const T* values, int size)
{
	if (!isValidRow(col))
	{
		throw MatrixException("Invalid column index");
	}

	if (size != this->row)
	{
		throw MatrixException("Size of 'values' array does not match the number of rows in the matrix");
	}

	for (int i = 0; i < size; ++i)
	{
		this->get(i, col) = values.at(i);
	}
}

template<typename T>
inline void Matrix<T>::replaseCol(int col, const std::vector<T>& values)
{
	if (!isValidRow(col))
	{
		throw MatrixException("Invalid column index");
	}

	if (values.size() != this->row)
	{
		throw MatrixException("Size of 'values' array does not match the number of rows in the matrix");
	}

	for (int i = 0; i < values.size(); ++i)
	{
		this->get(i, col) = values.at(i);
	}
}

template<typename T>
inline Matrix<T> Matrix<T>::identity(int n)
{
	if (n <= 0)
	{
		throw MatrixException("The size of the matrix must be positive");
	}

	Matrix<T> result(n, n, 0);

	for (int i = 0; i < n; ++i)
	{
		result.set(i, i, 1);
	}

	return result;
}

template<typename T>
inline void Matrix<T>::rSwap(int i, int j)
{
	if (!isValidRow(i) || !isValidRow(j))
	{
		throw MatrixException("Invalid row or column index");
	}

	if (i == j)	return;

	for (int index_j = 0; index_j < col; ++index_j)
	{
		std::swap(get(i, index_j), get(j, index_j));
	}
}

template<typename T>
inline void Matrix<T>::rMul(int i, const T& k)
{
	if (!isValidRow(i))
	{
		throw MatrixException("Invalid row index");
	}

	for_each_elemOfTheRow(i, [&](T& value)->bool {
		value *= k;
		return true;
	});
}

template<typename T>
inline void Matrix<T>::rAdd(int i, const T& k, int j)
{
	if (!isValidRow(i) || !isValidRow(j))
	{
		throw MatrixException("Invalid row or column index");
	}

	for (int index_j = 0; index_j < col; ++index_j)
	{
		set(j, index_j, get(i, index_j) * k + get(j, index_j));
	}
}

template<typename T>
inline int Matrix<T>::rank() const // TODO
{
	return 0;
}

// ��ȡ����
template<typename T>
T getReciprocal(const T& value)
{
	if (value == 0) return 0;
	return 1.0 / value;
}

template<typename T>
inline Matrix<T> Matrix<T>::inverse() const // TODO����������������������������������������
{
	Matrix<T> temp(row, row + col);

	// ��ʼ��
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			temp.set(i, j, this->get(i, j));
		}
		temp.set(i, i + col, 1); // ׷�ӵ�λ����
	}

	std::cout << temp << std::endl;

	// �����Խ����·�����0
	for (int i = 0; i < col - 1; ++i)
	{
		for (int j = i + 1; j < row; ++j)
		{
			T k = -temp.get(j, i) / temp.get(i, i);
			temp.rAdd(i, k, j);
		}
	}

	std::cout << temp << std::endl;

	// �����Խ��߻��� 1
	for (int i = 0; i < row; ++i)
	{
		temp.rMul(i, getReciprocal(temp.get(i, i)));
	}
	
	std::cout << temp << std::endl;

	Matrix<T> result;
	return result;
}

template<typename T>
inline T Matrix<T>::det() const // TODO
{
	return T();
}

template<typename T>
inline void Matrix<T>::solve() const // TODO
{
}

template<typename T>
inline bool Matrix<T>::isValidRow(int row) const
{
	return row >= 0 && row < this->row;
}

template<typename T>
inline bool Matrix<T>::isValidCol(int col) const
{
	return col >= 0 && col < this->col;
}

template<typename T>
inline bool Matrix<T>::isValidPosition(int row, int col) const
{
	return row >= 0 && row < this->row && col >= 0 && col < this->col;
}

template<typename T>
inline bool Matrix<T>::canLinearly(const Matrix<T>& left, const Matrix<T>& right)
{
	return left.row == right.row && left.col == right.col;
}

template<typename T>
inline bool Matrix<T>::canMatrixOperations(const Matrix<T>& left, const Matrix<T>& right)
{
	return left.col == right.row;
}

template<typename T>
inline bool Matrix<T>::isPhalanx(const Matrix<T>& matrix)
{
	return matrix.row == matrix.col;
}
