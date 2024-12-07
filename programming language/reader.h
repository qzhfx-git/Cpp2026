//
// Created by ASUS on 24-12-7.
//

#ifndef READER_H
#define READER_H
#include <sstream>
#include<string>

class Reader {
    std::stringstream ss;
public:
    Reader(){}
    Reader(std::string s) {
        ss << s;
    }
    char get() {
        return ss.peek();
    }
    void next() {
        ss.get();
    }
    bool has_next() {
        return ss.peek() != -1;
    }
    void clear() {
        ss.clear();
    }
    // ~Reader() {
    //     ss.clear();
    // }
};



#endif //READER_H
