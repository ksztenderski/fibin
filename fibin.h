#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <vector>

template<int N>
struct Fib {
    enum {
        val = Fib<N - 1>::val + Fib<N - 2>::val
    };
};
template<>
struct Fib<1> {
    enum {
        val = 1
    };
};
template<>
struct Fib<0> {
    enum {
        val = 0
    };
};

struct True {
};

struct False {
};

template<typename T>
struct Lit;

template<int n>
struct Lit<Fib<n>> {
    enum {
        val = Fib<n>::val
    };
};
template<>
struct Lit<True> {
    enum {
        val = true
    };
};
template<>
struct Lit<False> {
    enum {
        val = false
    };
};

template<typename T>
struct Fibin;

#endif //FIBIN_FIBIN_H
