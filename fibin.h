#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <iostream>
#include <typeinfo>
#include <cassert>
#include <cstdint>

// Stała używana przy hashowaniu w Var.
#define BASE 37

// Typ wynikowy funkcji Var.
using var_t = uint32_t;

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

template<typename T1, typename T2, typename... Rest>
struct Sum {
};

template<typename Arg>
struct Inc1 {
};

template<typename Arg>
struct Inc10 {
};

template<typename Left, typename Right>
struct Eq {
};

template<var_t Var>
struct Ref {
};

template<typename Condition, typename Then, typename Else>
struct If {
};

template<var_t Var, typename Body>
struct Lambda {
};

template<typename Fun, typename Param>
struct Invoke {
};

template<var_t Name, typename Value, typename Expression>
struct Let {
};

constexpr bool properVar(const char *str) {
    if (str[0] == '\0') return false;
    int i = 0;
    while (i < 6 && str[i] != '\0') {
        if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') ||
            (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') {
                return false;
            }
        ++i;
    }

    return str[i] == '\0';
}

constexpr var_t Var(const char *str) {
    assert(properVar(str));

    int i = 0;
    var_t res = 0;
    while (i < 6 && str[i] != '\0') {
        res *= BASE;
        if (str[i] <= '9' && str[i] >= '0') {
            res += str[i] - '0' + 1;
        }
        else if (str[i] <= 'Z' && str[i] >= 'A') {
            res += str[i] - 'A' + 11;
        }
        else if (str[i] <= 'z' && str[i] >= 'a') {
            res += str[i] - 'a' + 11;
        }
        ++i;
    }

    return res;
}

template<typename ValueType>
class Fibin {
private:
    template<typename Expression, typename Env>
    struct Eval {
    };

    template<typename Expression, typename Env>
    struct Get {
    };

    template<typename T, typename... Rest>
    struct SumAux {
    };

    template<typename T>
    struct SumAux<T> {
    };

    template<typename Proc, typename Value>
    struct Apply {
    };

    struct EmptyEnv;

    template<typename Lam, typename Env>
    struct Closure {
    };

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
        using result = typename Eval<Value, Env>::result;
    };

    template<var_t Name, var_t Name2, typename Value2, typename Env>
    struct Find<Name, List<Name2, Value2, Env> > {
        using result = typename Find<Name, Env>::result;
    };

    template<int N, typename Env>
    struct Get<Fib<N>, Env> {
        static_assert(N >= 0);
        static constexpr ValueType value = Get<Fib<N - 1>, Env>::value + Get<Fib<N - 2>, Env>::value;
    };

    template<typename Env>
    struct Get<Fib<1>, Env> {
        static constexpr ValueType value = 1;
    };

    template<typename Env>
    struct Get<Fib<0>, Env> {
        static constexpr ValueType value = 0;
    };

    template<int N, typename Env>
    struct Eval<Lit<Fib<N>>, Env> {
        using result = Get<Fib<N>, Env>;
    };

    template<typename T, typename Env>
    struct Eval<Lit<T>, Env> {
        using result = T;
    };

    template<typename T, typename Env>
    struct Get<SumAux<T>, Env> {
        static constexpr ValueType value = Eval<T, Env>::result::value;
    };

    template<typename T1, typename... Rest, typename Env>
    struct Get<SumAux<T1, Rest...>, Env> {
        static constexpr ValueType value =
                Eval<T1, Env>::result::value + Get<SumAux<Rest...>, Env>::value;
    };

    template<typename T1, typename T2, typename... Rest, typename Env>
    struct Eval<Sum<T1, T2, Rest...>, Env> {
        using result = Get<SumAux<T1, T2, Rest...>, Env>;
    };

    template<typename T, typename Env>
    struct Eval<Inc1<T>, Env> {
        using result = Get<SumAux<Lit<Fib<1>>, T>, Env>;
    };

    template<typename T, typename Env>
    struct Eval<Inc10<T>, Env> {
        using result = Get<SumAux<Lit<Fib<10>>, T>, Env>;
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

    template<var_t Var, typename Env>
    struct Eval<Ref<Var>, Env> {
        using result = typename Find<Var, Env>::result;
    };

    template<var_t Var, typename Value, typename Expression, typename Env>
    struct Eval<Let<Var, Value, Expression>, Env> {
        using result = typename Eval<Expression, List<Var, Value, Env>>::result;
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

    template<var_t Var, typename Body, typename Env>
    struct Eval<Lambda<Var, Body>, Env> {
        using result = Closure<Lambda<Var, Body>, Env>;
    };

    template<typename Fun, typename Param, typename Env>
    struct Eval<Invoke<Fun, Param>, Env> {
        using result = typename Apply<typename Eval<Fun, Env>::result, Param>::result;
    };

    template<var_t Var, typename Body, typename Value, typename Env>
    struct Apply<Closure<Lambda<Var, Body>, Env>, Value> {
        using result = typename Eval<Body, List<Var, Value, Env> >::result;
    };

public:
    template<typename Expr, typename X = ValueType, typename std::enable_if_t<std::is_integral<X>::value, int> = 0>
    static constexpr ValueType eval() {
        return Eval<Expr, EmptyEnv>::result::value;
    }

    template<typename Expr, typename X = ValueType, typename std::enable_if_t<!std::is_integral<X>::value, int> = 0>
    static constexpr void eval() {
        std::cout << "Fibin doesn't support: " << typeid(X).name() << std::endl;
    }
};

#endif //FIBIN_FIBIN_H

