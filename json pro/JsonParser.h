//
// Created by ASUS on 24-12-17.
//

#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "Node.h"
#include <optional>

class JsonParser {
public:
    std::string_view json_str;
    size_t pos = 0;

    void parse_whitespace() {
        while (pos < json_str.size() && std::isspace(json_str[pos])) {
            pos++;
        }
    }

    auto parse_null() -> std::optional<Value> {
        if (json_str.substr(pos, 4) == "null") {
            pos += 4;
            return Null{};
        }
        return {};
    }

    auto parse_true() -> std::optional<Value> {
        if (json_str.substr(pos, 4) == "true") {
            pos += 4;
            return true;
        }
        return {};
    } //判断bool值
    auto parse_false() -> std::optional<Value> {
        if (json_str.substr(pos, 5) == "false") {
            pos += 5;
            return false;
        }
        return {};
    } //判断bool值
    auto parse_number() -> std::optional<Value> {
        size_t endpos = pos;
        while (endpos < json_str.size() && (std::isdigit(json_str[endpos]) || json_str[endpos] == 'e' || json_str[
                                                endpos] == '.')) {
            endpos++;
        }
        std::string number = std::string{json_str.substr(endpos, endpos - pos)};
        pos = endpos;
        static auto is_Float = [](std::string &number) {
            return number.find('.') != std::string::npos || number.find('e') == std::string::npos;
        };
        if (is_Float(number)) {
            try {
                Float value = std::stod(number);
                return value;
            } catch (...) {
                return {};
            }
        } else {
            try {
                Int ret = std::stoll(number);
                return ret;
            } catch (...) {
                return {};
            }
        }
    }

    auto parse_string() -> std::optional<Value> {
        pos++;
        size_t endpos = pos;
        while (endpos < json_str.size() && json_str[endpos] != '"') {
            endpos++;
        }
        std::string str = std::string{json_str.substr(pos, endpos - pos)};
        pos = endpos + 1;
        return str;
    }

    auto parse_array() -> std::optional<Value> {
        pos++; // [
        Array arr;
        while (pos < json_str.size() && json_str[pos] != ']') {
            auto value = parse_value();
            arr.push_back(value.value());
            parse_whitespace();
            if (pos < json_str.size() && json_str[pos] == ',') {
                pos++; // ,
            }
            parse_whitespace();
        }
        pos++; // ]
        return arr;
    }

    auto parse_object() -> std::optional<Value> {
        pos++; // {
        Object obj;
        while (pos < json_str.size() && json_str[pos] != '}') {
            auto key = parse_value();
            parse_whitespace();
            if (!std::holds_alternative<String>(key.value())) {
                return {};
            }
            if (pos < json_str.size() && json_str[pos] == ':') {
                pos++; // ,
            }
            parse_whitespace();
            auto val = parse_value();
            obj[std::get<String>(key.value())] = val.value();
            parse_whitespace();
            if (pos < json_str.size() && json_str[pos] == ',') {
                pos++; // ,
            }
            parse_whitespace();
        }
        pos++; // }
        return obj;
    }

    auto parse_value() -> std::optional<Value> {
        parse_whitespace();
        switch (json_str[pos]) {
            case 'n':
                return parse_null();
            case 't':
                return parse_true();
            case 'f':
                return parse_false();
            case '"':
                return parse_string();
            case '[':
                return parse_array();
            case '{':
                return parse_object();
            default:
                return parse_number();
        }
    }

    auto parse() -> std::optional<Node> {
        parse_whitespace();
        auto value = parse_value();
        if (!value) {
            return {};
        }
        return Node{*value};
    }
};

auto parser(std::string_view json_) -> std::optional<Node>;

#endif //JSONPARSER_H
