#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <vector>

template<int N>
struct Fib {
    static_assert(N >= 0, "Fib's argument must be positive!");
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

/*
template<typename T>
inline T sum(T n) {
    return n;
}

template<int n>
inline int sum(Lit<Fib<n>>) {
    return Lit<Fib<n>>::val;
}

template <typename T, typename... Args>
inline int sum(T n, Args... args) {
    return sum(n) + sum(args...);
}
*/

/*
template <typename ...Ts> struct Sum {};

template <typename T, typename ... Ts>
struct Sum<T, Ts...> : Sum<Ts...> {
    Sum(T t, Ts... ts) : Sum<Ts...>(ts...), el(t) {}

    T el;
};

 */

/*
template <typename... Rest>
struct SumAux{
    enum {
        val = 0
    };
};
*/
template <typename T, typename... Rest>
struct SumAux{
    enum {
        val = SumAux<T>::val + SumAux<Rest...>::val
    };
};


template <typename T1, typename T2, typename... Rest>
struct Sum{
    enum {
        val = SumAux<T1>::val + SumAux<T2, Rest...>::val
    };
};


template<int n>
struct SumAux<Lit<Fib<n>>> {
    enum {
        val = Fib<n>::val
    };
};

template<typename T>
struct Fibin;

#endif //FIBIN_FIBIN_H
