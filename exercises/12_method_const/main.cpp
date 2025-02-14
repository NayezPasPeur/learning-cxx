#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    // 使用数组引用传递参数，避免指针退化
    // 这里初始化的时候为什么返回的是constexpr ？？ 
    constexpr Fibonacci(const int (&arr)[11]) {
        for (int i = 0; i < 11; ++i) {
            numbers[i] = arr[i];
        }
    }

    // `get` 方法应该是 `constexpr`，并且 `const` 以支持 `constexpr Fibonacci`
    constexpr int get(int i) const {
        return numbers[i];
    }

};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
