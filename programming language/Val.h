//
// Created by ASUS on 24-12-7.
//

#ifndef VAL_H
#define VAL_H

#include <iostream>
#include<iomanip>
#include <string>
#include<map>
#include<fstream>
#include<cmath>

#define INT 0
#define DOU 1
#define STR 2
#define MAP 3

class Val {
public:
    int INT_VAL;
    double DOU_VAL;
    std::string STR_VAL;
    std::map<Val, Val> MAP_VAL;
    int type;

    void del() {
        INT_VAL = 0;
        DOU_VAL = 0;
        STR_VAL.clear();
        MAP_VAL.clear();
    }

    Val() {
        del();
        type = -1;
    }

    Val(int val) {
        del();
        type = INT;
        INT_VAL = val;
    }

    Val(double val) {
        del();
        type = DOU;
        DOU_VAL = val;
    }
};

Val operator +(Val a, Val b);

Val operator -(Val a, Val b);

Val operator *(Val a, Val b);

Val operator /(Val a, Val b);

bool operator ==(Val a, Val b);

bool operator &&(Val a, Val b);

bool operator ||(Val a, Val b);

std::ostream &operator<<(std::ostream &os, const Val &val);

#endif //VAL_H
