#include <iostream>

#include "../include/HuffmanTree.h"

int main()
{
    mylib::HuffmanTree h;
    
    std::string code = h.encode("text.txt");
    std::cout << "code = \n" << code << std::endl;
    
    std::string text = h.decode("code.txt");
    std::cout << "text = \n" << text << std::endl;

    return 0;
}