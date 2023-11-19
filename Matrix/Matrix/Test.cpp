#include <iostream>
#include <vector>

#include "Matrix.h"

int main()
{
	Matrix<double> m(3, 3, { 1, 2, 3, 2, 2, 1, 4, 3, 5 });
	/*std::cout << ~m << std::endl;*/
	m.inverse();
	return 0;
}
