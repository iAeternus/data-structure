#include <iostream>

#include "Integer.h"

int main()
{
	//Integer a = 1234567890;
	//Integer b("-324783465438904323458903458904539034890457894353453534067452358907890745645545689237233484353457876589597879");
	//std::cout << b.getBit(1) << std::endl;
	//std::cout << a << std::endl;
	//std::cout << b << std::endl;
	//b = Integer::abs(b);
	//std::cout << b << std::endl;

	//std::cout << std::endl;
	//a = 1;
	//for (int i = 0; i < 10; i++)
	//{
	//	std::cout << (a <<= 1) << std::endl;
	//}
	//std::cout << std::endl;

	//a = -10;
	//b = "0";
	//std::cout << a * b << std::endl;

	////a = 1000;
	////b = 100;
	////std::cout << a / b << std::endl;

	//a = std::string("9999999999999999999999999999");
	//b = std::string("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	//std::cout << a - b << std::endl;
	//a -= b;
	//std::cout << a << std::endl;

	////std::cin >> a;
	////std::cout << a << std::endl;
	 
	Integer a, b;
	std::cout << "输入第一个大整数: ";
	try {
		std::cin >> a;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "不能输入-0" << e.what() << std::endl;
	}
	std::cout << "输入第二个大整数: ";
	try {
		std::cin >> b;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "不能输入-0" << e.what() << std::endl;
	}

	std::cout << "相加: " << a + b << std::endl;
	std::cout << "相减: " << a - b << std::endl;
	std::cout << "相乘: " << a * b << std::endl;

	try {
		std::cout << "相除 - 商: " << a / b << std::endl;
		std::cout << "相除 - 余数: " << a % b << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "除法错误: " << e.what() << std::endl;
	}

	return 0;
}
