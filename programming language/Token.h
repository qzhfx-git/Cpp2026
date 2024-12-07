//
// Created by ASUS on 24-12-7.
//

#ifndef TOKEN_H
#define TOKEN_H

#include "Val.h"
#include <vector>
#include <set>
#define OP 0
#define NUM 1
#define VAR 2
class Token {
public:
    Val num;//数字
    char op;//操作符
    std::string var;//变量名
    int type;
    Token(){}
    Token(char ch) {
        type = OP;
        op = ch;
    }
    Token(Val x) {
        type = NUM;
        num = x;
    }
    Token(std::string s) {
        type = VAR;
        var = s;
    }
};
std::ostream& operator<<(std::ostream& os, const Token& t);

std::vector<Token> Lexer(std::string s);
Token parser_op();//解析操作符
Token parser_num();//解析数字
Token parser_var();//解析变量
#endif //TOKEN_H
