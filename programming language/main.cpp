#pragma once
#include <iostream>
#include<iomanip>
#include <string>
#include<fstream>
#include<cmath>
#include "Token.h"
#include "TreeNode.h"
#include <algorithm>

int main() {
    Expression("x = 10 + 1*2*3+4");
    Expression("y = 2 * x");
    std::cout << Expression("x") << std::endl;
    std::cout << Expression("y + 5") << std::endl;
    std::cout << Expression("(y + 5) / (5 + 5) * 3.1415926") << std::endl;
    std::string s;
    while (getline(std::cin, s)) {
        if (std::ranges::count(s, '=') == 1) {
            Expression(s);
        } else {
            std::cout << "ans : " << Expression(s) << std::endl;
        }
    }
    return 0;
}
