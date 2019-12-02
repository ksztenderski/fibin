#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <iostream>
#include <cstdint>

#define BASE 37

using var_t = unsigned;

template<var_t Var, typename Value, typename Environment>
struct List {
};

struct Environment {
};

/*List<var_t Var, typename Value, EmptyEnvironment>

template<>
struct*/

template<int N>
struct Fib {
};

struct True {
};

struct False {
};

template<typename T>
struct Lit {
};

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

constexpr bool properVar(const char *str) {
    if (str[0] == '\0') return false;
    int i = 0;
    while (i < 6 && str[i] != '\0') {
        if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') ||
            (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
            return false;
        ++i;
    }
    return str[i] == '\0';
}

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

template<var_t Var>
struct Ref {
    constexpr static uint64_t &val = Nr<Var>::val;

    constexpr static void set(uint64_t newValue) {
        val = newValue;
    }
};

template<var_t Var, typename Value, typename Expression>
struct Let {
    using result = List<Var, Value, Environment>

    constexpr static auto

    run() {
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

    using val = typename tmp::val;
};

template<typename ValueType, typename Enable = void>
struct Fibin {
    template<typename T>
    constexpr static void eval() {
        std::cout << "Fibin doesn't support: PKc" << std::endl;
    }
};

template<typename ValueType>
class Fibin<ValueType, typename std::enable_if<std::is_integral_v<ValueType>>::type> {
private:

    constexpr ValueType lit(int n) {
        return fib(n);
    }

public:
    template<typename T>
    constexpr ValueType static eval() {
    }

    template<>
    constexpr ValueType static eval<Sum>() {
    }

};

#endif //FIBIN_FIBIN_H
