#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <iostream>

#define BASE 36

using var_t = unsigned;

/*template<typename T>
struct Value {
    constexpr static T val = 0;
};

template<typename T>
struct Function {
    constexpr static T val = 0;

    constexpr static void run() {}
};*/

template<typename N, typename V, typename E>
struct List {
};

struct EmptyEnvironment {
};

List<var_t Var, Value1, EmptyEnvironment>

template<>
struct

template<int N>
struct Fib {
    static_assert(N >= 0, "Fib's argument must not be negative!");

    constexpr static uint64_t val = Fib<N - 1>::val + Fib<N - 2>::val;
};

template<>
struct Fib<1> {
    constexpr static int val = 1;
};

template<>
struct Fib<0> {
    constexpr static int val = 0;
};

struct True {
    constexpr static bool val = true;
};

struct False {
    constexpr static bool val = false;
};

template<typename T>
struct Lit {
    constexpr static auto val = T::val;
};

constexpr var_t Var(const char *str) {
    int i = 0;
    var_t res = 0;
    if (str[0] == '\0') return 0;
    while (i < 6 && str[i] != '\0') {
        res *= BASE;
        if (str[i] <= '9' && str[i] >= '0') {
            res += str[i] - '0' + 1;
        } else if (str[i] <= 'Z' && str[i] >= 'A') {
            res += str[i] - 'A' + 11;
        } else if (str[i] <= 'z' && str[i] >= 'a') {
            res += str[i] - 'a' + 11;
        } else {
            return 0;
        }
        ++i;
    }
    if (str[i] != '\0') return 0;

    return res;
}

template<unsigned n>
struct Nr {
    static uint64_t val;
};
template<unsigned n>
uint64_t Nr<n>::val = 0;

template<var_t Var>
struct Ref {
    constexpr static uint64_t &val = Nr<Var>::val;

    constexpr static void set(uint64_t newValue) {
        val = newValue;
    }
};

template<var_t Var, typename Value, typename Expression>
struct Let {
    constexpr static auto result = List<Var, Value::val, Expression>

    constexpr static auto run() {
        Ref<Var>::set(Value::val);
        return Expression::val;
    }
};

template<typename T1, typename T2>
struct Eq {
    constexpr static bool val = T1::val == T2::val;
};

template<bool flag, typename T1, typename T2>
struct If_then_else {
    typedef T1 Result;
};

template<typename T1, typename T2>
struct If_then_else<false, T1, T2> {
    typedef T2 Result;
};

template<typename Condition, typename Then, typename Else>
struct If {
    typedef typename If_then_else<Condition::val, Then, Else>::Result tmp;

    constexpr static uint64_t val = tmp::val;
};

template<typename ValueType>
struct Fibin {
    template<typename T, typename X = ValueType, std::enable_if_t<std::is_integral<X>::value, int> = 0>
    constexpr std::enable_if_t<std::is_integral<X>::value, X> static eval() {
        return T::val;
    }

    template<typename T>
    constexpr std::enable_if_t<!std::is_integral<ValueType>::value> static eval() {
        std::cout << "Fibin doesn't support: PKc" << std::endl;
    }
};

/*template<typename ValueType>
struct Fibin<ValueType, typename std::enable_if<std::is_integral_v<ValueType>>::type> {
    template<typename T>
    constexpr ValueType static eval() {
        return T::val;
    }
};*/

template<typename T, typename... Rest>
struct SumAux {
    constexpr static uint64_t val = SumAux<T>::val + SumAux<Rest...>::val;
};

template<typename T>
struct SumAux<T> {
    constexpr static uint64_t val = T::val;
};


template<typename T1, typename T2, typename... Rest>
struct Sum {
    constexpr static uint64_t val = SumAux<T1>::val + SumAux<T2, Rest...>::val;
};


template<typename T>
struct Inc1 {
    constexpr static uint64_t val = T::val + Fib<1>::val;
};

template<typename T>
struct Inc10 {
    constexpr static uint64_t val = T::val + Fib<10>::val;
};

#endif //FIBIN_FIBIN_H
