//
// Created by ASUS on 24-12-17.
//

#include "JsonParser.h"

auto parser(std::string_view json_str) -> std::optional<Node> {
    JsonParser p{json_str};
    return p.parse();
}
