#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);
    // 虚函数（virtual_name()） 会遵循动态绑定，调用时会找到实际的子类实现。
    // 非虚函数（direct_name()） 不会进行动态绑定，而是直接调用对应的类的实现。


    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    // 研究一下
    ASSERT(rab.virtual_name() == 'B', MSG);
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG);

    ASSERT(rab.direct_name() == 'A', MSG);
    ASSERT(rbc.direct_name() == 'B', MSG);
    ASSERT(rcd.direct_name() == 'C', MSG);
    // 通过基类引用调用虚函数
    //  rab.virtual_name()：
    // rab 是 A& 类型，但实际绑定对象是 B，调用 B::virtual_name()，返回 'B'。
    // rbc.virtual_name()：
    // rbc 是 B& 类型，但实际绑定对象是 C，调用 C::virtual_name()，返回 'C'。
    // rcd.virtual_name()：
    // rcd 是 C& 类型，但实际绑定对象是 D，由于 D 继承了 C::virtual_name()，所以返回 'C'。
    // 通过基类引用调用非虚函
    // rab.direct_name()：
    // rab 是 A&，但**direct_name() 不是虚函数**，直接调用 A::direct_name()，返回 'A'。
    // rbc.direct_name()：
    // rbc 是 B&，直接调用 B::direct_name()，返回 'B'。
    // rcd.direct_name()：
    // rcd 是 C&，直接调用 C::direct_name()，返回 'C'。

    // 虚函数遵循动态绑定，会调用实际对象的实现。
    // 非虚函数不会动态绑定，只会调用当前类型的方法。


    A &rac = c;
    B &rbd = d;
    // 更多引用绑定行为
    // rac.virtual_name()：
    // rac 是 A&，但实际对象是 C，调用 C::virtual_name()，返回 'C'。
    // rbd.virtual_name()：
    // rbd 是 B&，但实际对象是 D，由于 D 继承 C::virtual_name()，返回 'C'。
    // rac.direct_name()：
    // rac 是 A&，但 direct_name() 不是虚函数，直接调用 A::direct_name()，返回 'A'。
    // rbd.direct_name()：
    // rbd 是 B&，但 direct_name() 不是虚函数，直接调用 B::direct_name()，返回 'B'。




    ASSERT(rac.virtual_name() == 'C', MSG);
    ASSERT(rbd.virtual_name() == 'C', MSG);
    ASSERT(rac.direct_name() == 'A', MSG);
    ASSERT(rbd.direct_name() == 'B', MSG);

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG);
    ASSERT(rad.direct_name() == 'A', MSG);


    
    // 🔹 结论
    // 虚函数会动态绑定，直接调用实际对象的实现。
    // 非虚函数不会动态绑定，而是直接调用声明的类的方法。
    // final 关键字阻止子类重写虚函数，但子类仍然继承它。
    // 基类引用调用虚函数时，会遵循动态绑定，调用最终派生类的实现。
    // 🚀 这个代码示例很好地展示了 C++ 的虚函数机制！



    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
