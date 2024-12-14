#include <iostream>
#include <vector>
#include <string>
using namespace std;

// struct Any {
//     Any() : ptr{0} {
//     }
//
//     template<typename T>
//     Any(const T &t) : ptr{new Data<T>(t)} {
//     };
//
//     Any(const Any &rhs) {
//         ptr = rhs.ptr->clone();
//     }
//
//     Any &operator=(const Any &rhs) {
//         if (ptr)delete ptr;
//         ptr = rhs.ptr->clone();
//         return *this;
//     }
//
//     Any(Any &&rhs) noexcept {
//         ptr = rhs.ptr;
//         rhs.ptr = 0;
//     }
//
//     Any &operator=(Any &&rhs) noexcept {
//         if (ptr)delete ptr;
//         ptr = rhs.ptr;
//         rhs.ptr = 0;
//         return *this;
//     }
//
//     struct Base {
//         virtual Base *clone() = 0;
//
//         virtual ostream &print(ostream &out) = 0;
//     };
//
//     template<typename T>
//     struct Data : Base {
//         T data;
//
//         Data(const T &t) : data(t) {
//         }
//
//         virtual Base *clone() { return new Data<T>(data); }
//
//         virtual ostream &print(ostream &out) {
//             out << data;
//             return out;
//         }
//     };
//
//     Base *ptr;
//
//     template<typename T>
//     T &get_data() {
//         return ((Data<T> *) ptr)->data;
//     }
//
//     ~Any() {
//         if (ptr)delete ptr;
//     }
// };
//
// ostream &operator <<(ostream &out, const Any &oth) {
//     oth.ptr->print(out);
//     return out;
// }
//
// template<typename T>
// ostream &operator <<(ostream &out, const vector<T> &v) {
//     out << "[";
//     for (auto it = v.begin(); it != v.end(); it++) {
//         if (it != v.begin())out << ",";
//         out << *it;
//     }
//     out << "]";
//     return out;
// }


struct Any {
    Any(): ptr{nullptr} {
    }

    template<typename T>
    Any(const T &x): ptr{new Data<T>(x)} {
    }

    Any(const Any &other) {
        ptr = other.ptr->clone();
    }

    Any &operator=(const Any &other) {
        if (ptr)delete ptr;
        ptr = other.ptr->clone();
        return *this;
    }

    // Any(Any &&rhs) noexcept {
    //     ptr = rhs.ptr;
    //     rhs.ptr = 0;
    // }
    //
    // Any &operator=(Any &&rhs) noexcept {
    //     if (ptr)delete ptr;
    //     ptr = rhs.ptr;
    //     rhs.ptr = 0;
    //     return *this;
    // }

    struct Base {
        virtual Base *clone() = 0;

        virtual std::ostream &print(std::ostream &out) = 0;
    };

    template<typename T>
    struct Data : Base {
        T data;

        Data(const T &a): data(a) {
        }

        // template<typename T>
        Base *clone() override {
            return new Data<T>(data);
        }

        std::ostream &print(std::ostream &out) override {
            out << (data);
            return out;
        }
    };


    Base *ptr;

    template<typename T>
    T &get_data() {
        return (static_cast<Data<T> *>(ptr)->data);
    }

    ~Any() {
        if (ptr)delete ptr;
    }
};

std::ostream &operator<<(std::ostream &out, const Any &a) {
    a.ptr->print(out);
    return out;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << "[";
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin())out << ",";
        out << *it;
    }
    out << "]";
    return out;
}

int main() {
    vector<Any> vec = {114, 514, 1919, 8.10, string("asoul"), string("4soul")};
    cout << vec << endl;
    vector<Any> oth = {string("ygg"), 233};
    vec.push_back(oth);
    cout << vec << endl;
    vec[1] = vector<Any>{oth, oth};
    cout << vec << endl;
}
