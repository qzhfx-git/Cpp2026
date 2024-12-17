//
// Created by ASUS on 24-12-17.
//

#ifndef JSONGENERATOR_H
#define JSONGENERATOR_H

#include "JsonParser.h"

class JsonGenerator {
public:
    static auto generate(const Node &node) -> std::string {
        return std::visit(
            [](auto &&arg) -> std::string {
                using T = std::decay_t<decltype(arg)>; //推导并获得arg的最简类型
                if constexpr (std::is_same_v<T, Null>) {
                    return "null";
                } else if constexpr (std::is_same_v<T, Bool>) {
                    return arg ? "true" : "false";
                } else if constexpr (std::is_same_v<T, Int>) {
                    return std::to_string(arg);
                } else if constexpr (std::is_same_v<T, Float>) {
                    return std::to_string(arg);
                } else if constexpr (std::is_same_v<T, String>) {
                    return generate_string(arg);
                } else if constexpr (std::is_same_v<T, Array>) {
                    return generate_array(arg);
                } else if constexpr (std::is_same_v<T, Object>) {
                    return generate_object(arg);
                }
            },
            node.value);
    }

    static auto generate_string(const String &str) -> std::string {
        std::string json_str = "\"";
        json_str += str;
        json_str += '"';
        return json_str;
    }

    static auto generate_array(const Array &array) -> std::string {
        std::string json_str = "[";
        for (const auto &node: array) {
            json_str += generate(node);
            json_str += ',';
        }
        if (!array.empty()) json_str.pop_back();
        json_str += ']';
        return json_str;
    }

    static auto generate_object(const Object &object) -> std::string {
        std::string json_str = "{";
        for (const auto &[key, node]: object) {
            json_str += generate_string(key);
            json_str += ':';
            json_str += generate(node);
            json_str += ',';
        }
        if (!object.empty()) json_str.pop_back();
        json_str += '}';
        return json_str;
    }
};

inline auto generate(const Node &node) -> std::string { return JsonGenerator::generate(node); }


inline auto operator <<(std::ostream &out, const Node &t) -> std::ostream & {
    out << JsonGenerator::generate(t);
    return out;
}


#endif //JSONGENERATOR_H
