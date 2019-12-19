#ifndef FIBIN_FIBIN_H
#define FIBIN_FIBIN_H

#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cassert>
#include <cstdint>

/// Base used for encoding Var(36 is enough).
#define BASE 36

/// Return type of Var.
using var_t = uint32_t;

/// Declarations of necessary types.
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

template<var_t Var, typename Value, typename Expression>
struct Let {
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

/**
 * Encodes variable identifier.
 * Correct variable name contains from 1 up to 6 characters.
 * Correct characters are: 0-9, A-Z, a-z.
 * Uppercase and lowercase letters encode to same value.
 */
constexpr var_t Var(const char *str) {
    assert(str[0] != '\0');

    int i = 0;
    var_t res = 0;
    while (i < 6 && str[i] != '\0') {
        assert((str[i] >= '0' && str[i] <= '9') ||
               (str[i] >= 'A' && str[i] <= 'Z') ||
               (str[i] >= 'a' && str[i] <= 'z'));

        res *= BASE;

        if (str[i] <= '9' && str[i] >= '0') {
            res += str[i] - '0' + 1;
        } else if (str[i] <= 'Z' && str[i] >= 'A') {
            res += str[i] - 'A' + 11;
        } else {
            res += str[i] - 'a' + 11;
        }
        ++i;
    }

    assert(str[i] == '\0');

    return res;
}

/**
 * Fibin language interpreter.
 * @tparam ValueType type used for calculations.
 */
template<typename ValueType>
class Fibin {
private:
    /// Declarations of necessery structures.
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

    /// Empty environment.
    struct EmptyEnv;

    /// Used to store current environment for lambda function.
    template<typename Lambda, typename Env>
    struct Closure {
    };

    /// List of all variables in the environment.
    template<var_t Var, typename Value, typename Env>
    struct List {
    };

    /// Structure for finding variable in given environment.
    template<var_t Var, typename Env>
    struct Find {
    };

    /// Variable not found in the list.
    template<var_t Var>
    struct Find<Var, EmptyEnv> {
    };

    /// Variable found in the list. Called when value is a function.
    template<var_t Var, typename Value, typename Env>
    struct Find<Var, List<Var, Value, Env> > {
        using result = Value;
    };

    /// Variable found in the list. Called when value is a literal.
    template<var_t Var, typename T, typename Env>
    struct Find<Var, List<Var, Lit<T>, Env>> {
        using result = typename Eval<Lit<T>, Env>::result;
    };

    /// Looking for the variable in the rest of the list.
    template<var_t Var, var_t Var2, typename Value2, typename Env>
    struct Find<Var, List<Var2, Value2, Env> > {
        using result = typename Find<Var, Env>::result;
    };

    /// Calculates Nth fibonacci number
    template<int N, typename Env>
    struct Get<Fib<N>, Env> {
        static_assert(N >= 0);
        static constexpr ValueType value =
                Get<Fib<N - 1>, Env>::value + Get<Fib<N - 2>, Env>::value;
    };

    template<typename Env>
    struct Get<Fib<1>, Env> {
        static constexpr ValueType value = 1;
    };

    template<typename Env>
    struct Get<Fib<0>, Env> {
        static constexpr ValueType value = 0;
    };

    /// Evaluates numeric literal.
    template<int N, typename Env>
    struct Eval<Lit<Fib<N>>, Env> {
        using result = Get<Fib<N>, Env>;
    };

    /// Boolean literal.
    template<typename T, typename Env>
    struct Eval<Lit<T>, Env> {
        using result = T;
    };

    template<typename T, typename Env>
    struct Get<SumAux<T>, Env> {
        static constexpr ValueType value = Eval<T, Env>::result::value;
    };

    template<typename T, typename... Rest, typename Env>
    struct Get<SumAux<T, Rest...>, Env> {
        static constexpr ValueType value =
                Eval<T, Env>::result::value + Get<SumAux<Rest...>, Env>::value;
    };

    /// Calculates the sum.
    template<typename T1, typename T2, typename... Rest, typename Env>
    struct Eval<Sum<T1, T2, Rest...>, Env> {
        using result = Get<SumAux<T1, T2, Rest...>, Env>;
    };

    /// Increments argument by Fib<1>.
    template<typename Arg, typename Env>
    struct Eval<Inc1<Arg>, Env> {
        using result = Get<SumAux<Lit<Fib<1>>, Arg>, Env>;
    };

    /// Inrements argument by Fib<10>.
    template<typename Arg, typename Env>
    struct Eval<Inc10<Arg>, Env> {
        using result = Get<SumAux<Lit<Fib<10>>, Arg>, Env>;
    };

    /// Defines a type based on a flag.
    template<bool flag, typename T1, typename T2>
    struct If_then_else {
        typedef T1 result;
    };

    template<typename T1, typename T2>
    struct If_then_else<false, T1, T2> {
        typedef T2 result;
    };

    /// Compares 2 values.
    template<typename Left, typename Right, typename Env>
    struct Eval<Eq<Left, Right>, Env> {
        using result = typename If_then_else<Eval<Left, Env>::result::value ==
                                             Eval<Right, Env>::result::value, True, False>::result;
    };

    /// Evaluates value of variable.
    template<var_t Var, typename Env>
    struct Eval<Ref<Var>, Env> {
        using result = typename Find<Var, Env>::result;
    };

    /// Assigns value to a variable.
    template<var_t Var, typename Value, typename Expression, typename Env>
    struct Eval<Let<Var, Value, Expression>, Env> {
        using result = typename Eval<Expression, List<Var, Value, Env>>::result;
    };

    /// Assigns lambda function to a variable.
    template<var_t Var, var_t Var2, typename Body, typename Expression, typename Env>
    struct Eval<Let<Var, Lambda<Var2, Body>, Expression>, Env> {
        using result = typename Eval<Expression, List<Var, typename Eval<Lambda<Var2, Body>, Env>::result, Env>>::result;
    };

    /// Evaluates Then.
    template<typename Then, typename Else, typename Env>
    struct Eval<If<True, Then, Else>, Env> {
        using result = typename Eval<Then, Env>::result;
    };

    /// Evaluates Else.
    template<typename Then, typename Else, typename Env>
    struct Eval<If<False, Then, Else>, Env> {
        using result = typename Eval<Else, Env>::result;
    };

    /// Evaluates expression based on Condition.
    template<typename Condition, typename Then, typename Else, typename Env>
    struct Eval<If<Condition, Then, Else>, Env> {
        using result = typename Eval<If<typename Eval<Condition, Env>::result, Then, Else>, Env>::result;
    };

    /// Lambda function evaluates into Closure.
    template<var_t Var, typename Body, typename Env>
    struct Eval<Lambda<Var, Body>, Env> {
        using result = Closure<Lambda<Var, Body>, Env>;
    };

    /// Caluclates value of Fun with value of Param.
    template<typename Fun, typename Param, typename Env>
    struct Eval<Invoke<Fun, Param>, Env> {
        using result = typename Apply<typename Eval<Fun, Env>::result, typename Eval<Param, Env>::result>::result;
    };

    /// Calculates Lambda expression for Value.
    /// Environment is from definiction of Lambda expression.
    template<var_t Var, typename Body, typename Value, typename Env>
    struct Apply<Closure<Lambda<Var, Body>, Env>, Value> {
        using result = typename Eval<Body, List<Var, Value, Env> >::result;
    };

public:
    /// Evaluates value of expression when Fibin's ValueType is integral type.
    template<typename Expr, typename X = ValueType, typename std::enable_if_t<std::is_integral<X>::value, int> = 0>
    static constexpr ValueType eval() {
        return Eval<Expr, EmptyEnv>::result::value;
    }

    /// Fibin does not support non-integral types.
    template<typename Expr, typename X = ValueType, typename std::enable_if_t<!std::is_integral<X>::value, int> = 0>
    static constexpr void eval() {
        std::cout << "Fibin doesn't support: " << typeid(X).name() << std::endl;
    }
};

#endif //FIBIN_FIBIN_H

