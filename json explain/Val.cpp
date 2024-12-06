//
// Created by ASUS on 24-12-6.
//

#include "Val.h"
#include<iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <map>
#define INT 0
#define DOU 1
#define STR 2
#define BOOL 3
#define LIST 4
#define DICT 5

std::ostream &operator <<(std::ostream &out, const Val &v) {
    if (v.type == INT)out << v.INT_VAL;
    if (v.type == DOU)out << v.DOUBLE_VAL;
    if (v.type == STR)out << '\"' << v.STRING_VAL << '\"';
    if (v.type == BOOL) {
        if (v.BOOL_VAL)out << "true";
        else out << "false";
    }
    if (v.type == LIST) {
        out << "[";
        for (int i = 0; i < v.List.size(); i++) {
            if (i)out << ',';
            out << v.List[i];
        }
        out << ']';
    }
    if (v.type == DICT) {
        out << "{";
        for (auto it = v.Dict.begin(); it != v.Dict.end(); ++it) {
            if (it != v.Dict.begin()) {
                out << ",";
            }
            out << it->first << ":" << it->second;
        }
        out << "}";
    }
    return out;
}

std::stringstream ss;

Val parser_string() {
    ss.get(); //消除引号
    std::string s;
    while (ss.peek() != '"')
        s.push_back(ss.get());
    ss.get(); //消除引号
    return s;
}

Val parser_num() {
    std::string s;
    while (isdigit(ss.peek()) || ss.peek() == 'e' || ss.peek() == '-' || ss.peek() == '+' || ss.peek() == '.')
        s.push_back(ss.get());
    if (std::count(s.begin(), s.end(), '.')) {
        return Val(stof(s));
    }
    return Val(stoi(s));
}

Val parser_bool() {
    if (ss.peek() == 'f') {
        for (int i = 0; i < 5; i++)
            ss.get();
        return Val(false);
    }
    for (int i = 0; i < 4; i++) {
        ss.get();
    }
    return Val(true);
}

Val parser_arr() {
    ss.get(); //eat '['
    Val arr;
    arr.type = LIST;
    while (ss.peek() != ']') {
        arr.add(parser_val());
        while (ss.peek() != ']' && (ss.peek() == '\n' || ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == ','))
            ss.get();
    }
    ss.get(); //eat ']'
    return arr;
}

Val parser_dic() {
    ss.get(); //eat '{'
    Val dict;
    dict.type = DICT;
    while (ss.peek() != '}') {
        Val key = parser_val();
        while (ss.peek() == ' ' || ss.peek() == ':')ss.get();
        Val val = parser_val();
        dict.put(key, val);
        while (ss.peek() != '}' && (ss.peek() == '\n' || ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == ','))
            ss.get();
    }
    ss.get();
    return dict;
}

Val parser_val() {
    //json流处理
    while (ss.peek() != -1) {
        if (ss.peek() == ' ' || ss.peek() == '\n' || ss.peek() == '\t')ss.get();
        else if (ss.peek() == '"')return parser_string();
        else if (ss.peek() == 'f' || ss.peek() == 't')return parser_bool();
        else if (ss.peek() == '[') {
            return parser_arr();
        } else if (ss.peek() == '{') {
            return parser_dic();
        } else return parser_num();
    }
    return 0;
}

Val parser(std::string s) {
    //开始处理json
    ss.clear();
    ss << s;
    return parser_val();
}
