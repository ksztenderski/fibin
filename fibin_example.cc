#include "fibin.h"
#include <iostream>

int main() {
    std::cout << Fib<0>::val << std::endl;
    std::cout << Lit<Fib<100>>::val << std::endl;
    std::cout << Lit<True>::val << std::endl;
    std::cout << Lit<False>::val << std::endl;
    std::cout << Fibin<uint64_t>::eval<Lit<Fib<47>>>() << std::endl;

    Fibin<const char *>::eval<Lit<Fib<47>>>();

    std::cout << Sum<Lit<Fib<2>>, Inc1<Lit<Fib<2>>>, Inc10<Lit<Fib<2>>>,
            Sum<Lit<Fib<1>>, Sum<Lit<Fib<2>>, Lit<Fib<2>>>>>::val << std::endl;

    std::cout << Sum<Lit<Fib<6>>, Lit<Fib<2>>>::val << std::endl;

    std::cout << Eq<Lit<Fib<0>>, Lit<Fib<1>>>::val << std::endl;

    std::cout << Inc1<Lit<Fib<5>>>::val << std::endl;

    /*// Testing: lambda(x) {x + (Fib(1) + Fib(10)) + Fib(2)}(Fib(3))
    // Fib(0) = 0, Fib(1) = 1, Fib(2) = 1, Fib(3) = 2, Fib(10) = 55
    static_assert(59 == Fibin<uint64_t>::eval<Invoke<Lambda<Var("x"),
                  Sum<Ref<Var("x")>, Inc10<Lit<Fib<1>>>, Lit<Fib<2>>>>, Lit<Fib<3>>>>());

    // Testing: if False then Fib(0) else Fib(1)
    static_assert(1 == Fibin<uint8_t>::eval<If<Lit<False>, Lit<Fib<0>>, Lit<Fib<1>>>>());

    // Testing: let z = Fib(0) in {z + Fib(1)}
    static_assert(1 == Fibin<int16_t>::eval<Let<Var("z"), Lit<Fib<0>>, Inc1<Ref<Var("Z")>>>>());

    // Prints out to std::cout: "Fibin doesn't support: PKc"
    Fibin<const char*>::eval<Lit<Fib<0>>>();

    std::cout << "Fibin works fine!" << std::endl;*/

    return 0;
}