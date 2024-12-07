//
// Created by ASUS on 24-12-7.
//

#include "Val.h"
Val operator + (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL + b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL + b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL + b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL + b.DOU_VAL;
    }
}

Val operator - (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL - b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL - b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL - b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL - b.DOU_VAL;
    }
}

Val operator * (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL * b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL * b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL * b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL * b.DOU_VAL;
    }
}

Val operator / (Val a, Val b) {
    if (a.type == DOU) {
        if (b.type == INT)return a.DOU_VAL / b.INT_VAL;
        if (b.type == DOU)return a.DOU_VAL / b.DOU_VAL;
    }
    if (a.type == INT) {
        if (b.type == INT)return a.INT_VAL / b.INT_VAL;
        if (b.type == DOU)return a.INT_VAL / b.DOU_VAL;
    }
}

std::ostream& operator<<(std::ostream& os,const Val& val) {

    if(val.type == INT) os << val.INT_VAL;
    if(val.type == DOU) os << val.DOU_VAL;
    return os;
}