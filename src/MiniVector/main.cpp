#include <iostream>

#include "MiniVector/MiniVector.h"

static int test_MiniVector(){

    MiniVector<TestObj> vec1;
    std::cout << "=== emplace_back(10)(C++11原地构造)===" << std::endl;
    vec1.emplace_back(10); // C++11 完美转发，原地构造

    std::cout << "\n=== push_back(TestObj(20))(C++11移动构造)===" << std::endl;
    vec1.push_back(TestObj(20)); // 移动构造，无拷贝

    std::cout << "\n=== 扩容测试(push_back(30)触发扩容）===" << std::endl;
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(50); // 触发扩容（容量从4→8）

    std::cout << "\n=== 移动构造 vec2 = std::move(vec1) ===" << std::endl;
    MiniVector<TestObj> vec2 = std::move(vec1);
    std::cout << "vec2 size: " << vec2.size() << ", vec1 size: " << vec1.size() << std::endl;

    return 0;
}

int main(int argc, char* argv[]){

    printf("****** %s ******\n", PROJECT_NAME);

    test_MiniVector();

    return 0;
}