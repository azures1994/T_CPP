#include <iostream>
#include <utility>

int& get_ref() {
    static int value = 10;
    return value;
}

//! C++14
auto f1(){
    return get_ref();
}

//! C++14
decltype(auto) f2(){
    return get_ref();
}

int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    //! 1. lvalue rvalue
    printf("\n====== 1. lvalue rvalue ======\n");
    int a = 5;
    int& b = a;
    int&& c = 5;
    decltype(c) d = 10;
    std::cout << std::boolalpha;
    std::cout << "Is 'a' an lvalue_reference? " << std::is_lvalue_reference<decltype(a)>::value << std::endl;
    std::cout << "Is 'b' an lvalue_reference? " << std::is_lvalue_reference<decltype(b)>::value << std::endl;
    std::cout << "Is 'c' an rvalue_reference? " << std::is_rvalue_reference<decltype(c)>::value << std::endl;
    std::cout << "Is 'd' an rvalue_reference? " << std::is_rvalue_reference<decltype(d)>::value << std::endl;

    // a++ = 10;
    ++a = 10;

    std::cout << "Is decltype(get_ref()) an lvalue_reference? " << std::is_lvalue_reference<decltype(get_ref())>::value << std::endl;

    int e = f1();
    std::cout << "e: " << e << std::endl;
    //! Because auto will discard reference.
    std::cout << "Is decltype(f1()) an lvalue_reference? " << std::is_lvalue_reference<decltype(f1())>::value << std::endl;
    
    //! Because decltype(auto) preserves reference.
    f2() = 20; std::cout << "After f2(), get_ref() = " << get_ref() << std::endl;
    std::cout << "Is decltype(f2()) an lvalue_reference? " << std::is_lvalue_reference<decltype(f2())>::value << std::endl;

    //! 2. decltype(expression)
    printf("\n====== 2. decltype(expression) ======\n");
    int x2 = 10;
    decltype(x2+1) y2 = 20; // decltype(x2+1) is int
    printf("x2 = %d, y2 = %d\n", x2, y2);
    std::cout << "typeid(x2).name(): " << typeid(x2).name() << std::endl;
    std::cout << "typeid(y2).name(): " << typeid(y2).name() << std::endl;

    int a2 = 10;
    decltype(a2) b2 = 20; // decltype(a2) is int
    std::cout << "typeid(b2).name(): " << typeid(b2).name() << std::endl;
    decltype((a2)) c2 = a2;
    a2 = 30;
    printf("a2 = %d, c2 = %d\n", a2, c2); // c2 is a reference to a2
    std::cout << "typeid(c2).name(): " << typeid(c2).name() << std::endl;

    decltype(1+2) d2 = 30;
    
    int e2[5] = {1,2,3,4,5};
    decltype(e2) f2 = {10, 20, 30, 40, 50};
    f2[3] = 300;

    return 0;
}