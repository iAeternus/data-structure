#include <iostream>
#include <vector>

#include "Integer.h"

int main()
{
    Integer a, b;
    std::cout << "�����һ��������: ";
    std::cin >> a;
    std::cout << "����ڶ���������: ";
    std::cin >> b;
    std::cout << "���: " << a + b << std::endl;
    std::cout << "���: " << a - b << std::endl;
    std::cout << "���: " << a * b << std::endl;

    try {
        std::cout << "��� - ��: " << a / b << std::endl;
        std::cout << "��� - ����: " << a % b << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "��������: " << e.what() << std::endl;
    }

    return 0;
}
