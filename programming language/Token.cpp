//
// Created by ASUS on 24-12-7.
//

#include "Token.h"

#include <algorithm>

#include "reader.h"

std::ostream& operator<<(std::ostream& os, const Token& t) {
    if(t.type == OP)os << t.op;
    if(t.type == NUM) os << t.num;
    if(t.type == VAR) os << t.var;
    return os;
}
std::set<char>operator_set = {'+','-','*','/','(',')','=','^' ,'<','>','?',',','!',';','%' };
Reader rd;
std::vector<Token> Lexer(std::string s) {
    rd.clear();
    rd = Reader(s);
    std::vector<Token>v;
    while(rd.has_next()) {
        while(rd.has_next()&&(rd.get() == ' '|| rd.get() == '\n'|| rd.get() == '\t'))rd.next();
        if(operator_set.count(rd.get())) {
            v.push_back(parser_op());
        }
        else if(rd.get() == '_'||isalpha(rd.get())) {
            v.push_back(parser_var());
        }else {
            // std::cerr << rd.get() << std::endl;
            v.push_back(parser_num());
        }
    }
    return v;
}
Token parser_op() {
    //一个操作符
    char op = rd.get();
    rd.next();
    return {op};
}
Token parser_var() {
    std::string s="";
    while(isalpha(rd.get())||isdigit(rd.get())||rd.get() == '_') {
        s += rd.get();
        rd.next();
    }
    return {s};
}
Token parser_num() {
    std::string s="";
    //通过是否有小数点和e来判断是double还是int
    while(isdigit(rd.get())||rd.get() == '.'||rd.get()=='e'||rd.get() == '-') {
        s.push_back( rd.get());
        rd.next();
    }
    // std::cerr << s << std::endl;
    if(std::count(s.begin(), s.end(), '.')||std::count(s.begin(), s.end(), 'e'))
        return Val(stof(s));
    return Val(stoi(s));
}



