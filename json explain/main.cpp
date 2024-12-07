#include<iostream>
#include<fstream>
#include "Val.h"

int main() {
    std::ifstream fin("input.txt");
    std::stringstream ss;
    ss << fin.rdbuf();
    Val x = parser(ss.str());
    std::cout << x << std::endl;
}
