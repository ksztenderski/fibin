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
};

struct False {
};

template<typename T>
struct Lit {};

template<typename T1, typename T2, typename... Rest>
struct Sum {};


template<typename Arg>
struct Inc1 {
};

template<typename Arg>
struct Inc10 {
};

template<typename Left, typename Right>
struct Eq {
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
*/
template<typename T1, typename T2>
struct Eq {};

template<typename Condition, typename Then, typename Else>
struct If {};


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

    template<typename Expression, typename Env>
    struct Get {
    };

    template<int N>
    struct Eval<Fib<N>> {
        static constexpr ValueType value = fib(N);
    };

    template<int N, typename Env>
    struct Eval<Lit<Fib<N>>, Env> {
        using result = Get<Fib<N>, Env>;
    };

    template<typename T1, typename T2>
    struct Eval<Eq<T1, T2>> {
        static constexpr bool value = Eval<T1>::value == Eval<T2>::value;
    };

    template<typename T, typename ...Types, typename Env>
    static ValueType sum() {
        return Eval<T, Env>::value + sum<Types..., Env>();
    }

    template<typename T1, typename T2, typename... Rest, typename Env>
    struct Get<Sum<T1, T2, Rest...>, Env> {
        static constexpr ValueType value = sum<T1, T2, Rest..., Env>();
    };

    template<typename T1, typename T2, typename... Rest, typename Env>
    struct Eval<Sum<T1, T2, Rest...>, Env> {
        using result = Get<Sum<T1, T2, Rest...>, Env>;
    };

    template<int N, typename T, typename Env>
    static constexpr ValueType inc() {
        return Get<Fib<N>, Env>::value + Get<T, Env>::value;
    }

    template<typename T, typename Env>
    struct Get<Inc1<T>, Env> {
        static constexpr ValueType value = inc<1, T, Env>();
    };

    template<typename T, typename Env>
    struct Get<Inc10<T>, Env> {
        static constexpr ValueType value = inc<10, T, Env>();
    };

    template<typename T, typename Env>
    struct Eval<Inc1<T>, Env> {
        using result = Get<Inc1<T>, Env>;
    };

    template<typename T, typename Env>
    struct Eval<Inc10<T>, Env> {
        using result = Get<Inc10<T>, Env>;
    };

    template<bool flag, typename T1, typename T2>
    struct If_then_else {
        typedef T1 result;
    };
    template<typename T1, typename T2>
    struct If_then_else<false, T1, T2> {
        typedef T2 result;
    };

    template<typename T1, typename T2, typename Env>
    struct Eval<Eq<T1, T2>, Env> {
        using result = typename If_then_else<Eval<T1, Env>::result::value ==
                                             Eval<T2, Env>::result::value, True, False>::result;
    };

    template<typename T, typename... Rest>
    struct SumAux {
        constexpr static ValueType value = SumAux<T>::value + SumAux<Rest...>::value;
    };

    template<typename Then, typename Else, typename Env>
    struct Eval<If<True, Then, Else>, Env> {
        using result = typename Eval<Then, Env>::result;
    };

    template<typename Then, typename Else, typename Env>
    struct Eval<If<False, Then, Else>, Env> {
        using result = typename Eval<Else, Env>::result;
    };

    template<typename Condition, typename Then, typename Else, typename Env>
    struct Eval<If<Condition, Then, Else>, Env> {
        using result = typename Eval<If<typename Eval<Condition, Env>::result, Then, Else>, Env>::result;
    };

    template<typename T>
    struct SumAux<T> {
        constexpr static ValueType value = Eval<T>::value;
    };

    // TODO
    template<var_t Var, typename Body>
    struct Eval<Lambda<Var, Body>> {
        using result = Closure<Lambda<Var, Body>, EmptyEnv>;
    };

    /*template<bool flag, typename T1, typename T2>
    struct If_then_else {
        typedef T1 Result;
    };

    template<typename T1, typename T2>
    struct If_then_else<false, T1, T2> {
        typedef T2 Result;
    };*/
    template<bool flag, typename T1, typename T2>
    struct If_then_else {
        static constexpr ValueType value = Eval<T1>::value;
    };

    template<typename T1, typename T2>
    struct If_then_else<false, T1, T2> {
        static constexpr ValueType value = Eval<T2>::value;
    };

    template<typename Condition, typename Then, typename Else>
    struct Eval<If<Condition, Then, Else>> {
        static constexpr ValueType value = If_then_else<Eval<Condition>::value, Then, Else>::value;
    };



public:
    template<typename Expr, typename X = ValueType, typename std::enable_if_t<std::is_integral<X>::value, int> = 0>
    static constexpr ValueType eval() {
        return Eval<Expr>::value;
    }

    template<typename Expr, typename X = ValueType, typename std::enable_if_t<!std::is_integral<X>::value, int> = 0>
    static constexpr void eval() {
        std::cout << "Fibin doesn't support: " << typeid(X).name() << std::endl;
    }
};

#endif //FIBIN_FIBIN_H
