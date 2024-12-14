#include<iostream>

template<int N>
struct  Fac {
    const static int value = N * Fac<N-1>::value;
};
template<>
struct  Fac<0> {
    const static int value = 1;
};
int main() {
    Fac<3>::value;
    return 0;
}