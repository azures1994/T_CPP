#include <iostream>

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

    //! 2
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

int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    COLOR color = COLOR::RED;
    std::cout << color << std::endl; //! Overload operator<< for enum COLOR

    //! Function Templates
    printf("\n====== Function Templates ======\n");
    print(123, "Hello", color, 3.14, 'z');

    //! Class Templates
    printf("\n====== Class Templates ======\n");
    Info<int, std::string, double> info1(1, "Jack", 90.5);
    info1.print();

    StudentInfo<int, std::string, double, double> studentInfo1(2, "Tom", 60, 92, 95, 91);
    studentInfo1.print();

    Info<int, std::string, double>* info_a = new Info<int, std::string, double>(3, "Mike", 80);
    info_a->print();

    Info<int, std::string, double>* info_b = new StudentInfo<int, std::string, double, double>(4, "Lucy", 70, 90, 85, 80);
    info_b->print();

    return 0;
}