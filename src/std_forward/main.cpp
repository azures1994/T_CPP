#include <iostream>
#include <type_traits> //! 用于类型推导

template<typename T>
struct Test{
    using Type = T&&;
};

static int test_001(){

    int value = 42;

    // 测试1： 直接类型别名
    using IntRef = int&;
    using RefToRef = IntRef&; // int& & -> int& 

    static_assert(std::is_same_v<RefToRef, int&>, "类型相同");

    // 测试2： 模版中的引用折叠
    using T1 = Test<int&>::Type;  // int& && -> int&
    using T2 = Test<int&&>::Type; // int&& && -> int&&
    using T3 = Test<int>::Type;   // int && -> int&&

    static_assert(std::is_same_v<T1, int&>, "T1是左值引用");
    static_assert(std::is_same_v<T2, int&&>, "T2是右值引用");
    static_assert(std::is_same_v<T3, int&&>, "T3是右值引用");

    // 测试3： 完美转发示例
    auto&& a = value;   // value是左值， auto = int&, int& && -> int&;
    auto&& b = 100;     // 100是右值，auto = int, int&&
    
    std::cout << std::is_lvalue_reference_v<decltype(a)> << std::endl;
    std::cout << std::is_rvalue_reference_v<decltype(b)> << std::endl;

    return 0;
}

static int test_decltype(){

    int x = 10;
    int& y = x;
    int&& z = 20;

    decltype(y)& a = x; // int& & -> int&
    decltype(z)&& b = 30; // int&& && -> int&&

    static_assert(std::is_same_v<decltype(a), int&>, "decltype(a) is int&");
    static_assert(std::is_same_v<decltype(b), int&&>, "decltype(b) is int&&");

    return 0;
}

template <typename T>
void func(T&& param){

    //! 打印T的类型是否为int(右值入参时)
    std::cout << "T is int? " << std::is_same_v<T, int> << std::endl;

    //! 打印 param 的类型是否为int&&(右值入参时)
    std::cout << "param is int&&? " << std::is_same_v<decltype(param), int&&> << std::endl;

}

template <typename T>
void func2(T param){

    std::cout << "T is int? " << std::is_same_v<T, int> << std::endl;

    std::cout << "T is int&? " << std::is_same_v<T, int&> << std::endl;
    std::cout << "T is int&&? " << std::is_same_v<T, int&&> << std::endl;
    std::cout << "param is int&? " << std::is_same_v<decltype(param), int&> << std::endl;
    std::cout << "param is int&&? " << std::is_same_v<decltype(param), int&&> << std::endl;

}

//! 测试万能引用Universal_Reference
static int test_Universal_Reference(){

    int a = 20;
    
    std::cout << "传入右值 20: " << std::endl;
    func(20); // 右值入参

    std::cout << "传入左值 a: " << std::endl;
    func(a); // 左值入参

    func2(10);
    func2(a);

    return 0;
}

static int test(){

    int&& x = 10;

    printf("&x: %p\n", &x);

    return 0;
}

int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    test_001();

    test_decltype();

    test_Universal_Reference();

    test();

    return 0;
}