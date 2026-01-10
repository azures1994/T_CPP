#include <iostream>
#include <type_traits>

//! 顶层const 和 底层const
//! 顶层const: 作用于变量本身，该变量不可修改；
//! 底层const: 作用于指针或引用的对象，不能通过该变量修改指向的对象；

//! 基本类型只有顶层const
//! 引用只有底层const
//! 指针的const: (1) const int* p = &x; //! 底层const (2) int* const p = &x; //! 顶层const

static int test_basic(){

    //! 1. auto 值类型推导
    printf("================== 1. auto 值类型推导 =====================\n");
    {
        int a = 1;
        auto va = a;
        // static_assert(std::is_same_v<decltype(va), int>, "va is int");
        std::cout << "va is int? " << std::is_same_v<decltype(va), int> << std::endl;

        const int b = a; //! 去掉顶层const
        auto vb = b;
        std::cout << "vb is int? " << std::is_same_v<decltype(vb), int> << std::endl;

        const int* pc = &a;
        auto vpc = pc;
        std::cout << "vpc is const int* ? " << std::is_same_v<decltype(vpc), const int*> << std::endl;
        std::cout << "vpc is int* ? " << std::is_same_v<decltype(vpc), int*> << std::endl;

        int* const pd = &a;
        auto vpd = pd;
        std::cout << "vpd is int* ? " << std::is_same_v<decltype(vpd), int*> << std::endl;
        std::cout << "vpd is int* const ? " << std::is_same_v<decltype(vpd), int* const> << std::endl;
        
        const char arr[] = "Hello";
        auto varr = arr;
        std::cout << "varr is const char* ? " << std::is_same_v<decltype(varr), const char*> << std::endl;
        std::cout << "varr is char* ? " << std::is_same_v<decltype(varr), char*> << std::endl;
    }

    //! 2. auto& 左值引用推导
    printf("================== 2. auto& 左值引用推导 =====================\n");
    {

        int a = 10;
        auto& va = a;
        std::cout << "va is int& ? " << std::is_same_v<decltype(va), int&> << std::endl;

        const int b = a;
        auto& vb = b;
        std::cout << "vb is const int&? " << std::is_same_v<decltype(vb), const int&> << std::endl;
        std::cout << "vb is int&? " << std::is_same_v<decltype(vb), int&> << std::endl;

        const int *pc = &a;
        auto& vpc = pc;
        std::cout << "vpc is const int* & ? " << std::is_same_v<decltype(vpc), const int* &> << std::endl;
        std::cout << "vpc is int* & ? " << std::is_same_v<decltype(vpc), int* &> << std::endl;
        std::cout << "vpc is const int* ? " << std::is_same_v<decltype(vpc), const int* > << std::endl;

        int* const pd = &a;
        auto& vpd = pd;
        std::cout << "vpd is int* const& ? " << std::is_same_v<decltype(vpd), int* const&> << std::endl;
        std::cout << "vpd is int*& ? " << std::is_same_v<decltype(vpd), int*&> << std::endl;

        const char arr[] = "World";
        auto& varr = arr;
        
    }

    //! 3. auto&& 万能引用推导
    printf("================== 3. auto&& 万能引用推导 =====================\n");
    {
        auto&& a = 1; // 1 是 右值
        std::cout << "a is int&& ? " << std::is_same_v<decltype(a), int&&> << std::endl;
    }

    return 0;
}

int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    test_basic();

    return 0;
}