//
// Created by ASUS on 24-12-6.
//
#ifndef VAL_H
#define VAL_H
#include<iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <map>
#include <sstream>
#define INT 0
#define DOU 1
#define STR 2
#define BOOL 3
#define LIST 4
#define DICT 5

class Val {
public:
    int INT_VAL; //整数
    double DOUBLE_VAL; //浮点数
    std::string STRING_VAL; //字符串
    bool BOOL_VAL; //逻辑值
    std::vector<Val> List;
    std::map<Val, Val> Dict;
    int type;

    void del() {
        if (type == STR)
            STRING_VAL.clear();
        if (type == LIST)
            List.clear();
        if (type == DICT)
            Dict.clear();
    }

    Val() {
    }

    ~Val() {
        del();
    }

    Val(const int &x) {
        del();
        type = INT;
        INT_VAL = x;
    }

    Val(const double &x) {
        del();
        type = DOU;
        DOUBLE_VAL = x;
    }

    Val(const std::string &x) {
        del();
        type = STR;
        STRING_VAL = x;
    }

    Val(const char *x) {
        del();
        type = STR;
        STRING_VAL = std::string(x);
    }

    Val(const bool &x) {
        del();
        type = BOOL;;
        BOOL_VAL = x;
    }

    Val(std::initializer_list<Val> l) {
        del();
        type = LIST;
        for (auto it: l) {
            List.push_back(it);
        }
    }

    void add(Val x) {
        if (type == LIST) {
            List.push_back(x);
        }
    }

    void put(Val key, Val x) {
        if (type == DICT) {
            Dict[key] = x;
        }
    }

    Val operator[](const Val i) {
        if (type == LIST)return List[i.INT_VAL];
        return Dict[i];
    }

    bool operator<(const Val &x) const {
        if (type != x.type) return type < x.type;
        if (type == INT)return INT_VAL < x.INT_VAL;
        if (type == DOU)return DOUBLE_VAL < x.DOUBLE_VAL;
        if (type == STR)return STRING_VAL < x.STRING_VAL;
        if (type == LIST)return List < x.List;
        if (type == DICT)return Dict < x.Dict;
        return true;
    }

    friend std::ostream &operator <<(std::ostream &out, const Val &v);
};


Val parser_string();

Val parser_num();

Val parser_bool();

Val parser_arr();

Val parser_dic();

Val parser_val();

Val parser(std::string s); //处理json
#endif //VAL_H
