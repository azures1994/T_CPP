#pragma once
#include <iostream>
#include <type_traits>

//! Template Template Parameters
template <template <typename, typename> class Container, typename T>
class ContainerPrinter{
public:
    ContainerPrinter(const Container<T, std::allocator<T>>& container) : _container(container) {}

    void print() const{
        for (auto& item : _container){
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    static void print(const Container<T, std::allocator<T>>& container){
        for (auto& item : container){
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

private:
    const Container<T, std::allocator<T>>& _container;
};

//! ====== Function specialization ======

template <typename T>
void printValue(const T& value){
    std::cout << "General printValue: " << value << std::endl;
}

template <>
void printValue<std::string>(const std::string& value){
    std::cout << "Specialized printValue for std::string: " << value << std::endl;
}

template <>
void printValue<double>(const double& value){
    std::cout << "Specialized printValue for double: " << value << std::endl;
}

//! function overload
void printValue(const int*& value){
    std::cout << "printValue(Overload) for int*: " << value << std::endl;
}

void coutAll(){
    std::cout << std::endl;
}

template <typename T, typename... Args>
void coutAll(const T& first, const Args&... args){
    std::cout << first << std::endl;
    coutAll(args...);
}

//! ====== SFINAE (Substitution Failure Is Not An Error) ======

template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_type(T value){
    std::cout << "Integer Value: " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
print_type(T value){
    std::cout << "Floating point: " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<T, const char*>::value || std::is_same<T, char*>::value, void>::type
print_type(T value){
    std::cout << "C-style string: " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_type(T value){
    std::cout << "std::string: " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_pointer<T>::value && !std::is_same<T, const char*>::value && !std::is_same<T, char*>::value, void>::type
print_type(T value){
    std::cout << "Pointer: " << *value << std::endl;
}

// template <typename T>
// void print_type(T value){
//     std::cout << "Generic: " << value << std::endl;
// }




