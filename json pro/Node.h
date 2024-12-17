//
// Created by ASUS on 24-12-17.
//基础类型结点
//

#ifndef NODE_H
#define NODE_H
#include <variant>
#include <algorithm>
#include<vector>
#include<string>
#include<string_view>
#include<iostream>
#include<map>
struct Node;
using Null = std::monostate;
using Bool = bool;
using Int = long long;
using Float = double;
using String = std::string;
using Array = std::vector<Node>;
using Object = std::map<std::string, Node>;
using Value = std::variant<Null, Bool, Int, Float, String, Array, Object>;

struct Node {
    Value value;
    Node(Value _value) : value(_value) {}
    Node():value(Null{}){}
    auto& operator[](const std::string key) {
        if(auto object = std::get_if<Object>(&value)) {
            return (*object)[key];
        }
        throw std::runtime_error("不是字典!\n");
    }
    auto operator[](size_t index) {
        if(auto array = std::get_if<Array>(&value)) {
            return array->at(index);
        }
        throw std::runtime_error("不是数组!\n");
    }
    void push(const Node& node) {
        if(auto array = std::get_if<Array>(&value)) {
            return array->push_back(node);
        }
        throw std::runtime_error("不是数组,不能push!\n");
    }
};



#endif //NODE_H
