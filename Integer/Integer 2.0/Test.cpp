#include <iostream>
#include <vector>

#include "Integer.h"

int main()
{
    Integer a, b;
    std::cout << "输入第一个大整数: ";
    std::cin >> a;
    std::cout << "输入第二个大整数: ";
    std::cin >> b;
    std::cout << "相加: " << a + b << std::endl;
    std::cout << "相减: " << a - b << std::endl;
    std::cout << "相乘: " << a * b << std::endl;

    try {
        std::cout << "相除 - 商: " << a / b << std::endl;
        std::cout << "相除 - 余数: " << a % b << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "除法错误: " << e.what() << std::endl;
    }

    return 0;
}
