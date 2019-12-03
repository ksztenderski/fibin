#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <iostream>
#include <cstdint>
#include <typeinfo>

#define BASE 37

using var_t = unsigned;

template<int N>
struct Fib {
};

struct True {
    static constexpr bool value = true;
};

struct False {
    static constexpr bool value = false;
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
    //constexpr static uint64_t val = T::val + Fib<1>::val;
};

template<typename T>
struct Inc10 {
    //constexpr static uint64_t val = T::val + Fib<10>::val;
};

//rzeczy do refa

struct EmptyEnv;


template<var_t Name, typename Value, typename Env>
struct List {
};

template<var_t Name, typename Env>
struct Find {
};

template<var_t Name>
struct Find<Name, EmptyEnv> {
};

template<var_t Name, typename Value, typename Env>
struct Find<Name, List<Name, Value, Env> > {
    Value typedef result;
};

template<var_t Name, var_t Name2, typename Value2, typename Env>
struct Find<Name, List<Name2, Value2, Env> > {
    typename Find<Name, Env>::result typedef result;
};

template<var_t Name, typename Value, typename Env>
struct Let {
    using result = List<Name, Value, Env>;
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

// constexpr to calculate the length of a string
constexpr size_t str_len(const char *p_str) {
    return (*p_str == '\0') ? 0 : str_len(p_str + 1) + 1;
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

/*
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
*/
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


template<typename ValueType>
class Fibin {
private:
    static constexpr ValueType fib(int N) {
        if (N == 0) return 0;
        if (N == 1) return 1;
        return fib(N - 1) + fib(N - 2);
    }

    template<typename T>
    struct Eval {
    };

    template<int N>
    struct Eval<Fib<N>> {
        static constexpr ValueType value = fib(N);
    };

    template<int N>
    struct Eval<Lit<Fib<N>>> {
        using result = Eval<Fib<N>>;
    };

    template<typename T>
    struct Eval<Lit<T>> {
        using result =T;
    };


public:
    template<typename Expr, typename X = ValueType, typename std::enable_if_t<std::is_integral<X>::value, int> = 0>
    static X eval() {
        return Eval<Expr>::result::value;
    }

    template<typename Expr, typename X = ValueType, typename std::enable_if_t<!std::is_integral<X>::value, int> = 0>
    static void eval() {
        std::cout << "Fibin doesn't support: " << typeid(X).name() << std::endl;
    }


};

#endif //FIBIN_FIBIN_H
