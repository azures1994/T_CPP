#include <iostream>
#include <vector>
#include <list>

#include "Template.h"

enum class COLOR{
    RED,
    GREEN,
    BLUE

};

std::ostream& operator<<(std::ostream& os, const COLOR& color){
    switch(color){
    case COLOR::RED:        os << "RED"; break;
    case COLOR::GREEN:      os << "GREEN"; break;
    case COLOR::BLUE:       os << "BLUE"; break;
    default:                os << "UNDEFINED COLOR"; break;
    }
    return os;
}

template <typename T>
void print_impl(const T& t){
    std::cout << t << std::endl;
}

template <typename T, typename... Rest>
void print_impl(const T& t, const Rest&... rest){
    std::cout << t << ", ";
    print_impl(rest...);
}

template <typename _Ty>
void printData(_Ty data){
    std::cout << data << "\t";
}

template <typename... Args>
void print(Args... args){
    //! 1
    // int array[] = {(printData(args), 0)...};
    // std::cout << std::endl;

    // (printData(args), ...);

    // //! 2
    print_impl(args...);
}

template <typename _Ty1, typename _Ty2, typename _Ty3>
class Info{
public:
    Info(const _Ty1& arg1, const _Ty2& arg2, const _Ty3& arg3)
    :_arg1(arg1), _arg2(arg2), _arg3(arg3){}

    virtual ~Info() = default;

    virtual void print();

protected:
    _Ty1 _arg1;
    _Ty2 _arg2;
    _Ty3 _arg3;

};

template <typename _Ty1, typename _Ty2, typename _Ty3>
void Info<_Ty1, _Ty2, _Ty3>::print(){
    std::cout << _arg1 << "\t" << _arg2 << "\t" << _arg3 << std::endl;
}

template <typename _Ty1, typename _Ty2, typename _Ty3, typename _U>
class StudentInfo : public Info<_Ty1, _Ty2, _Ty3>{

public:
    StudentInfo(const _Ty1& arg1, const _Ty2& arg2, const _Ty3& arg3, const _U& s1, const _U& s2, const _U& s3)
    :Info<_Ty1, _Ty2, _Ty3>(arg1, arg2, arg3), _s1(s1), _s2(s2), _s3(s3){}

    virtual ~StudentInfo() = default;

    virtual void print();

protected:
    _U _s1;
    _U _s2;
    _U _s3;

};

template <typename _Ty1, typename _Ty2, typename _Ty3, typename _U>
void StudentInfo<_Ty1, _Ty2, _Ty3, _U>::print(){
    Info<_Ty1, _Ty2, _Ty3>::print();
    std::cout << _s1 << "\t" << _s2 << "\t" << _s3 << std::endl;
}

template <int N>
struct Factorial{
    static const int value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0>{
    static const int value = 1;
};

template <int N>
struct Fibonacci{
    static const int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
struct Fibonacci<0>{
    static const int value = 0;
};

template <>
struct Fibonacci<1>{
    static const int value = 1;
};

template <int N, int... Ns>
struct Sum{
    static const int value = N + Sum<Ns...>::value;
};

template <int N>
struct Sum<N>{
    static const int value = N;
};


int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    COLOR color = COLOR::RED;
    std::cout << color << std::endl; //! Overload operator<< for enum COLOR

    //! 1. Function Templates
    printf("\n====== 1. Function Templates ======\n");
    print(123, "Hello", color, 3.14, 'z');

    //! 2. Class Templates
    printf("\n====== 2. Class Templates ======\n");
    Info<int, std::string, double> info1(1, "Jack", 90.5);
    info1.print();

    StudentInfo<int, std::string, double, double> studentInfo1(2, "Tom", 60, 92, 95, 91);
    studentInfo1.print();

    Info<int, std::string, double>* info_a = new Info<int, std::string, double>(3, "Mike", 80);
    info_a->print();

    Info<int, std::string, double>* info_b = new StudentInfo<int, std::string, double, double>(4, "Lucy", 70, 90, 85, 80);
    info_b->print();

    //! 3. Template Template Parameters
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::list<int> l1 = {22, 33, 44, 55, 66};

    // ContainerPrinter<std::vector, int> _containerPrinter1(v1);
    // _containerPrinter1.print();

    // ContainerPrinter<std::list, int> _containerPrinter2(l1);
    // _containerPrinter2.print();

    ContainerPrinter<std::vector, int>::print(v1);
    ContainerPrinter<std::list, int>::print(l1);

    printf("\n====== Function specialization ======\n");
    printValue(1);
    printValue(2.5);
    printValue(std::string("Hello Function Template!"));

    int a = 10;
    int b = 20;
    const int* pA = &a;
    printValue(pA);
    printValue(&a);

    pA = &b;
    printValue(pA);
    printValue(&b);

    coutAll(3, 3.45, "Hello World!");

    //! 4. SFINAE£¨Substitution Failure Is Not An Error£©
    printf("\n====== 4. SFINAE (Substitution Failure Is Not An Error) ======\n");
    int a4 = 100;
    print_type(a4);
    print_type(3.3);
    print_type("Hello C-style");
    print_type(std::string("Hello std::string"));
    print_type(&a4);
    float b4 = 3.12;
    print_type(&b4);

    double c4 = 7.22;
    print_type(c4);

    // int
    std::vector<int>::value_type d4 = 100;
    std::cout << "d4: " << d4 << std::endl;

    //! 5. Template Metaprogramming
    printf("\n====== 5. Template Metaprogramming ======\n");
    std::cout << "5! = " << Factorial<5>::value << std::endl;
    std::cout << "3! = " << Factorial<3>::value << std::endl;
    std::cout << "0! = " << Factorial<0>::value << std::endl;

    std::cout << "Fibonacci<5> = " << Fibonacci<5>::value << std::endl;
    std::cout << "Fibonacci<10> = " << Fibonacci<10>::value << std::endl;

    std::cout << "Sum<1, 2, 3, 4, 5>::value = " << Sum<1, 2, 3, 4, 5>::value << std::endl;
    std::cout << "Sum<0> = " << Sum<0>::value << std::endl;
    std::cout << "Sum<0, 1> = " << Sum<0, 1>::value << std::endl;

    return 0;
}