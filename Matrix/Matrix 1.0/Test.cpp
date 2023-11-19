/*
����ʽ��������
31 2 4
29 1 2
10 -1 1
det = -81

2 -5 1 2
-3 7 -1 4
5 -9 2 7
4 -6 1 2
det = -9
-----------------------
1 0 0 0
0 1 0 0
-1 2 1 0
1 1 0 1

1 0 1 0
-1 2 0 1
1 0 4 1
-1 -1 2 0

a*b = 
1 0 1 0
-1 2 0 1
-2 4 3 3
-1 1 3 1
-----------------------
*/
#include <iostream>

#include "Matrix.h"

void Test()
{
	Matrix a, b, c;
	double elem;
	char choice;

	do
	{
		std::cout << "F-���� A-�ӷ� S-���� N-���� M-�˷� P-���� T-ת�� R-���� I-���� D-����ʽ C-������ Q-�˳� > ";
		std::cin >> choice;
		while (std::cin.get() != '\n');
		choice = toupper(choice);

		switch (choice)
		{
		case 'F':
			std::cin >> a;
			std::cout << -a << std::endl;
			break;
		case 'A':
			std::cin >> a >> b;
			std::cout << a + b << std::endl;
			break;
		case 'S':
			std::cin >> a >> b;
			std::cout << a - b << std::endl;
			break;
		case 'N':
			std::cout << "�������� > ";
			std::cin >> elem;
			std::cin >> a;
			std::cout << elem * a << std::endl;
			break;
		case 'M':
			std::cin >> a >> b;
			std::cout << a * b << std::endl;
			break;
		case 'P':
			std::cout << "�������� > ";
			std::cin >> elem;
			std::cin >> a;
			std::cout << Matrix::pow(a, elem) << std::endl;
			break;
		case 'T':
			std::cin >> a;
			std::cout << ~a << std::endl;
			break;
		case 'R':
			std::cin >> a;
			std::cout << a.rank() << std::endl;
			break;
		case 'I':
			std::cin >> a;
			std::cout << a.inverse() << std::endl;
			break;
		case 'D':
			std::cin >> a;
			std::cout << a.det() << std::endl;
			break;
		case 'C':
			std::cout << "TODO\n";
			break;
		case 'Q':
			std::cout << "�˳�\n";
			break;
		default:
			std::cout << "����ȷ��ѡ�\n";
			break;
		}

	} while (choice != 'Q');
}

int main()
{
	Test();
	return 0;
}
