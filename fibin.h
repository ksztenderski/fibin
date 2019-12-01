#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <vector>

template<int N>
struct Fib {
    static_assert(N >= 0, "Fib's argument must not be negative!");
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


template <typename T, typename... Rest>
struct SumAux {
    enum {
        val = SumAux<T>::val + SumAux<Rest...>::val
    };
};


template<typename T1, typename T2, typename... Rest>
struct Sum {
    enum {
        val = SumAux<T1>::val + SumAux<T2, Rest...>::val
    };
};


template<typename T>
struct Inc1 {};

template<int n>
struct Inc1<Lit<Fib<n>>> {
    enum {
        val = Lit<Fib<n>>::val + Lit<Fib<1>>::val
    };
};

template<typename T>
struct Inc10 {};

template<int n>
struct Inc10<Lit<Fib<n>>> {
    enum {
        val = Lit<Fib<n>>::val + Lit<Fib<10>>::val
    };
};


// getVal template
template <typename T>
struct getVal {};

template <int n>
struct getVal<Lit<Fib<n>>> {
    enum {
        val = Fib<n>::val
    };
};

template<typename T>
struct getVal<Inc1<T>> {
    enum {
        val = Inc1<T>::val
    };
};

template<typename T>
struct getVal<Inc10<T>> {
    enum {
        val = Inc10<T>::val
    };
};


template<typename T1, typename T2, typename... Rest>
struct getVal<Sum<T1, T2, Rest...>> {
    enum {
        val = Sum<T1,T2, Rest...>::val
    };
};

template<typename T>
struct SumAux<T> {
    enum {
        val = getVal<T>::val
    };
};

template<typename T>
struct Fibin;

#endif //FIBIN_FIBIN_H
