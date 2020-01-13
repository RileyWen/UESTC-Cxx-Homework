#include <exception>
#include <iostream>

//请一定不要修改 ---BEGIN--- 和 ---END--- 两个标记之间的代码

//---BEGIN---
//普通的iterator。 实际上，这个iterator还未完成，不过这个程序中用不到它。
template <typename value_t>
struct iterator {
    using value_type = value_t;
    using reference = value_type&;
    using pointer = value_type*;
};

// traits。用于从iterator中萃取类型。
template <typename iterator_t>
struct iterator_traits {
    using value_type = typename iterator_t::value_type;
    using reference = typename iterator_t::reference;
    using pointer = typename iterator_t::pointer;
};

// traits的部分特化。用于迭代器是个原生指针的情况。
template <typename value_t>
struct iterator_traits<value_t*> {
    using value_type = value_t;
    using reference = value_type&;
    using pointer = value_type*;
};

//抽象的容器类模板，只能作为其它容器类模板的父模板
//两个类型参数分别是：元素类型、迭代器类型
//注意：迭代器类型有可能是原生指针
template <typename value_t, typename iterator_t = iterator<value_t>>
struct container {
    //定义迭代器类型的别名
    using iterator = iterator_t;
    //从traits中获得类型，这很安全
    using value_type = typename iterator_traits<iterator>::value_type;
    using reference = typename iterator_traits<iterator>::reference;
    using pointer = typename iterator_traits<iterator>::pointer;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;

    virtual iterator rbegin() = 0;
    virtual iterator rend() = 0;

    virtual ~container() {}
};

// vector类型，但用原生指针作为迭代器类型，因为其内部存储使用了原生指针
template <typename value_t>
class vector final : public container<value_t, value_t*> {
   public:
    using value_type = typename container<value_t>::value_type;
    using reference = typename container<value_t>::reference;
    using pointer = typename container<value_t>::pointer;

    using iterator = typename container<value_type, pointer>::iterator;
    //---END---

   private:
    pointer s;  //内部存储指针。
    // 1. 请添加其他必要的成员
    size_t cap;

   public:
    // 2. 请添加必要的构造函数和析构函数
    //以下是一个必要的构造函数原型
    vector(size_t n) : cap(n) { s = new value_type[n]; }

    ~vector() { delete[] s; }
    // n是vector能存储的元素个数。这意味着你需要为指针s分配内存。
    //注意：在所有添加的函数中，不要有任何的输入和输出

    // 3. 请添加重载的[]运算符函数
    //当下标超出范围时，必须抛出std::out_of_range("index out of range")异常
    //在catch子句中，打印出错信息index out of range，然后调用exit(0)退出程序
    reference operator[](size_t index) try {
        if (index >= this->cap)
            throw std::out_of_range("index out of range");
        else
            return s[index];
    } catch (std::out_of_range& e) {
        std::cout << e.what();
        exit(0);
    }

    // 4. 添加begin(), end(), rbegin(), rend()四个成员
    //这些成员的返回类型都是iterator，这个类型在前面做了定义
    //提示：迭代器是原生指针，是伪迭代器
    iterator begin() { return &s[0]; }
    iterator end() { return &s[this->cap]; }

    iterator rbegin() { return &s[this->cap - 1]; }
    iterator rend() { return &s[-1]; }
};

//---BEGIN---
template <typename T>
void foo(size_t n, int a, int b) {
    using iterator_t = T*;
    auto vp = new vector<T>(n);
    container<T, iterator_t>& v = *vp;

    for (auto& e : v) std::cin >> e;
    for (auto i = v.rbegin() - a; i != v.rend() + b; --i)
        std::cout << *i << ',';

    std::cout << (*vp)[10];

    delete vp;
}

int main() {
    size_t n, a, b;
    std::cin >> n >> a >> b;

    if (n % 2 == 0)
        foo<int>(n, a, b);
    else
        foo<char>(n, a, b);

    return 0;
}
//---END---
