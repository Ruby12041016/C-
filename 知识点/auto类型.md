# auto 详解

## 一、auto 是什么？

**auto** 是C++11引入的关键字，用于**自动类型推导**，让编译器根据初始化表达式自动推断变量的类型。

```cpp
#include <iostream>
#include <vector>
#include <map>

void basicAuto() {
    // 传统写法
    int x1 = 10;
    double y1 = 3.14;
    std::string s1 = "hello";
    
    // 使用 auto
    auto x2 = 10;        // 自动推导为 int
    auto y2 = 3.14;      // 自动推导为 double
    auto s2 = "hello";   // 注意：推导为 const char*，不是 std::string！
    
    // 明确指定类型
    auto s3 = std::string("hello");  // 推导为 std::string
    
    std::cout << "x2 类型: " << typeid(x2).name() << std::endl;
    std::cout << "y2 类型: " << typeid(y2).name() << std::endl;
    std::cout << "s2 类型: " << typeid(s2).name() << std::endl;
    std::cout << "s3 类型: " << typeid(s3).name() << std::endl;
}
```

## 二、基本用法

### 1. **基本类型推导**

```cpp
#include <iostream>
#include <typeinfo>

void basicTypes() {
    // 基本类型
    auto a = 42;         // int
    auto b = 3.14;       // double
    auto c = 3.14f;      // float
    auto d = 100L;       // long
    auto e = 100ULL;     // unsigned long long
    
    // 字符类型
    auto ch1 = 'A';      // char
    auto ch2 = L'中';    // wchar_t
    auto ch3 = u8'字';   // char8_t (C++20)
    
    // 布尔类型
    auto flag = true;    // bool
    auto flag2 = false;  // bool
    
    // 指针类型
    int value = 100;
    auto ptr = &value;   // int*
    auto& ref = value;   // int&
    
    // 常量类型
    const auto const_value = 100;     // const int
    const auto* const_ptr = &value;   // const int*
    auto const_ptr2 = &value;         // int*，注意：不是 const int*
    
    // volatile
    volatile auto vol_value = 100;    // volatile int
    
    std::cout << "a 类型: " << typeid(a).name() << std::endl;
    std::cout << "b 类型: " << typeid(b).name() << std::endl;
    std::cout << "ptr 类型: " << typeid(ptr).name() << std::endl;
    std::cout << "ref 类型: " << typeid(ref).name() << std::endl;
}
```

### 2. **与 const 和引用结合**

```cpp
#include <iostream>

void constAndRef() {
    int x = 10;
    const int cx = 20;
    int& rx = x;
    const int& crx = x;
    
    // auto 推导规则
    auto a1 = x;     // int (值拷贝)
    auto a2 = cx;    // int (忽略顶层const)
    auto a3 = rx;    // int (忽略引用)
    auto a4 = crx;   // int (忽略const和引用)
    
    // 修改 a1-a4 不会影响原值
    a1 = 100;
    std::cout << "x = " << x << ", a1 = " << a1 << std::endl;
    
    // auto& 推导
    auto& b1 = x;    // int&
    // auto& b2 = cx;   // 错误：不能从 const int 推导出 int&
    auto& b3 = rx;   // int&
    auto& b4 = crx;  // const int&
    
    b1 = 200;  // 修改 x
    // b4 = 300;  // 错误：b4 是 const int&
    
    // const auto&
    const auto& c1 = x;    // const int&
    const auto& c2 = cx;   // const int&
    const auto& c3 = rx;   // const int&
    const auto& c4 = crx;  // const int&
    
    // auto* 推导指针
    int* p = &x;
    const int* cp = &cx;
    
    auto* ap1 = p;   // int*
    auto* ap2 = cp;  // const int*
}
```

## 三、在STL容器中的使用

### 1. **遍历容器**

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>

void stlContainers() {
    // vector
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // 传统遍历
    for (std::vector<int>::iterator it = numbers.begin(); 
         it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 使用 auto
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 范围for循环 + auto
    for (auto num : numbers) {  // 值拷贝
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    for (const auto& num : numbers) {  // const引用，避免拷贝
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // map
    std::map<std::string, int> scores = {
        {"Alice", 90},
        {"Bob", 85},
        {"Charlie", 95}
    };
    
    // map的元素是 pair<const Key, Value>
    for (const auto& entry : scores) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
    
    // 使用结构化绑定 (C++17)
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << std::endl;
    }
}
```

### 2. **复杂容器类型**

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>

void complexContainers() {
    // vector of vectors
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    for (const auto& row : matrix) {  // row 是 const vector<int>&
        for (auto num : row) {        // num 是 int
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    
    // map of vectors
    std::map<std::string, std::vector<int>> studentScores = {
        {"Alice", {90, 85, 95}},
        {"Bob", {80, 75, 85}},
        {"Charlie", {95, 90, 100}}
    };
    
    for (const auto& [name, scores] : studentScores) {
        std::cout << name << ": ";
        for (auto score : scores) {
            std::cout << score << " ";
        }
        std::cout << std::endl;
    }
    
    // 嵌套迭代器
    std::list<std::vector<std::string>> nested = {
        {"a", "b", "c"},
        {"d", "e", "f"}
    };
    
    for (auto it1 = nested.begin(); it1 != nested.end(); ++it1) {
        for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;
    }
}
```

## 四、函数返回类型推导

### 1. **函数返回类型 auto (C++14)**

```cpp
#include <iostream>
#include <vector>
#include <string>

// C++14: auto 推导函数返回类型
auto add(int a, int b) {
    return a + b;  // 推导为 int
}

auto getPi() {
    return 3.14159265358979;  // 推导为 double
}

auto createVector() {
    return std::vector<int>{1, 2, 3, 4, 5};  // 推导为 std::vector<int>
}

auto process(int x) {
    if (x > 0) {
        return 42;     // int
    } else {
        return 3.14;   // 错误：返回类型不一致
    }
}

// 正确：使用条件运算符
auto process2(int x) {
    return x > 0 ? 42 : 3.14;  // double (int 和 double 都转换为 double)
}

void testAutoReturn() {
    auto result1 = add(10, 20);
    std::cout << "add: " << result1 << std::endl;
    
    auto pi = getPi();
    std::cout << "pi: " << pi << std::endl;
    
    auto vec = createVector();
    for (auto num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
```

### 2. **尾置返回类型 (C++11)**

```cpp
#include <iostream>
#include <vector>
#include <string>

// 尾置返回类型
auto multiply(int a, int b) -> int {
    return a * b;
}

// 需要推导的类型
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

// 更复杂的例子
template<typename Container>
auto getFirst(const Container& c) -> decltype(*c.begin()) {
    if (c.empty()) {
        throw std::runtime_error("容器为空");
    }
    return *c.begin();
}

// 与 auto 配合的 lambda
auto makeAdder(int x) {
    return int y { return x + y; };  // 返回 lambda
}

void testTrailingReturn() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto first = getFirst(vec);
    std::cout << "第一个元素: " << first << std::endl;
    
    auto adder = makeAdder(10);
    std::cout << "10 + 5 = " << adder(5) << std::endl;
}
```

## 五、auto 在泛型编程中的应用

### 1. **模板函数**

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <string>

// 传统模板函数
template<typename T>
void printTraditional(const T& container) {
    typename T::const_iterator it;  // 需要 typename
    for (it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// 使用 auto
template<typename T>
void printWithAuto(const T& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// 范围 for + auto
template<typename T>
void printRangeFor(const T& container) {
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// 泛型算法
template<typename Container, typename Func>
void forEach(const Container& c, Func f) {
    for (const auto& element : c) {
        f(element);
    }
}

void testGeneric() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<std::string> lst = {"a", "b", "c"};
    
    printTraditional(vec);
    printWithAuto(vec);
    printRangeFor(vec);
    
    printTraditional(lst);
    printWithAuto(lst);
    printRangeFor(lst);
    
    // 使用 lambda
    forEach(vec, int n {
        std::cout << n * 2 << " ";
    });
    std::cout << std::endl;
}
```

### 2. **类型萃取**

```cpp
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

template<typename T>
void processValue(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "整型: " << value << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "浮点型: " << value << std::endl;
    } else {
        std::cout << "其他类型" << std::endl;
    }
}

// decltype 获取表达式类型
template<typename Container>
auto getValueType(const Container&) -> typename Container::value_type {
    return typename Container::value_type{};
}

// 简化版本
template<typename Container>
using ValueType = typename Container::value_type;

void testTypeTraits() {
    auto a = 10;      // int
    auto b = 3.14;    // double
    auto c = "hello"; // const char*
    
    processValue(a);
    processValue(b);
    processValue(c);
    
    std::vector<int> vec;
    auto value_type = getValueType(vec);
    std::cout << "vector value_type: " << typeid(value_type).name() << std::endl;
}
```

## 六、auto 与 lambda 表达式

### 1. **lambda 表达式类型**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void lambdaWithAuto() {
    // lambda 表达式的类型是唯一的，编译器生成的
    auto lambda1 = int x, int y { return x + y; };
    auto lambda2 = int x, int y { return x + y; };
    
    std::cout << "lambda1(3, 5) = " << lambda1(3, 5) << std::endl;
    std::cout << "lambda2(10, 20) = " << lambda2(10, 20) << std::endl;
    
    // 两个 lambda 类型不同
    std::cout << std::boolalpha;
    std::cout << "类型相同? " << std::is_same_v<decltype(lambda1), decltype(lambda2)> << std::endl;
    
    // 存储 lambda
    std::function<int(int, int)> func = lambda1;  // 可以赋值
    std::cout << "func(3, 5) = " << func(3, 5) << std::endl;
    
    // auto 推导 lambda 参数 (C++14)
    auto genericLambda = auto a, auto b { return a + b; };
    std::cout << "泛型lambda(3, 5) = " << genericLambda(3, 5) << std::endl;
    std::cout << "泛型lambda(3.14, 2.5) = " << genericLambda(3.14, 2.5) << std::endl;
    std::cout << "泛型lambda(\"Hello, \", \"World!\") = " 
              << genericLambda(std::string("Hello, "), std::string("World!")) << std::endl;
}
```

### 2. **高阶函数**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void higherOrderFunctions() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 使用 auto 存储 lambda
    auto isEven = int n { return n % 2 == 0; };
    auto square = int n { return n * n; };
    auto print = int n { std::cout << n << " "; };
    
    // 过滤偶数
    std::vector<int> evens;
    std::copy_if(numbers.begin(), numbers.end(), 
                 std::back_inserter(evens), isEven);
    
    std::cout << "偶数: ";
    std::for_each(evens.begin(), evens.end(), print);
    std::cout << std::endl;
    
    // 平方每个元素
    std::vector<int> squares;
    std::transform(numbers.begin(), numbers.end(), 
                   std::back_inserter(squares), square);
    
    std::cout << "平方: ";
    std::for_each(squares.begin(), squares.end(), print);
    std::cout << std::endl;
    
    // 返回 lambda 的函数
    auto makeMultiplier = int factor {
        return int n { return n * factor; };
    };
    
    auto times3 = makeMultiplier(3);
    std::cout << "5 * 3 = " << times3(5) << std::endl;
}
```

## 七、auto 的特殊情况

### 1. **初始化列表**

```cpp
#include <iostream>
#include <vector>
#include <initializer_list>

void initializerList() {
    // auto 和初始化列表
    auto a = {1, 2, 3};        // std::initializer_list<int>
    auto b = {1, 2, 3.0};      // 错误：类型不一致
    auto c = {1};              // std::initializer_list<int>
    auto d = {};               // 错误：无法推导
    
    // 直接初始化
    auto e{1};                 // C++17 前：initializer_list<int>
                               // C++17 后：int
    auto f{1, 2, 3};           // 错误：C++17 后不允许多个值
    
    // 拷贝初始化
    auto g = {1};              // initializer_list<int>
    
    // 实际应用
    std::vector<int> vec1 = {1, 2, 3};  // 正确
    std::vector<int> vec2{1, 2, 3};     // 正确
    auto vec3 = std::vector<int>{1, 2, 3};  // 正确
    
    std::cout << "a.size(): " << a.size() << std::endl;
    for (auto num : a) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
```

### 2. **auto 和指针数组**

```cpp
#include <iostream>

void pointersAndArrays() {
    int arr[5] = {1, 2, 3, 4, 5};
    
    // auto 推导数组
    auto a1 = arr;      // int* (数组退化为指针)
    auto& a2 = arr;     // int(&)[5] (数组引用)
    
    std::cout << "a1 类型: " << typeid(a1).name() << std::endl;
    std::cout << "a2 类型: " << typeid(a2).name() << std::endl;
    std::cout << "a2 大小: " << sizeof(a2) << std::endl;
    
    // auto 推导字符串
    const char* str = "hello";
    auto s1 = str;      // const char*
    auto& s2 = str;     // const char*&
    auto s3 = "world";  // const char*
    
    // 二维数组
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    auto m1 = matrix;       // int(*)[4]
    auto& m2 = matrix;      // int(&)[3][4]
    
    // 使用 auto 遍历多维数组
    for (auto& row : matrix) {       // row 是 int(&)[4]
        for (auto element : row) {   // element 是 int
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}
```

## 八、auto 的最佳实践

### 1. **何时使用 auto**

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>

class GoodPractice {
public:
    // 1. 迭代器
    void example1() {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        // 好：避免冗长的类型
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // 更好：范围 for
        for (const auto& num : vec) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    
    // 2. 复杂类型
    void example2() {
        std::map<std::string, std::vector<int>> data = {
            {"A", {1, 2, 3}},
            {"B", {4, 5, 6}}
        };
        
        // 好：避免冗长类型
        auto it = data.find("A");
        if (it != data.end()) {
            for (auto num : it->second) {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }
    
    // 3. lambda 表达式
    void example3() {
        // 好：lambda 类型只能用 auto
        auto add = int a, int b { return a + b; };
        std::cout << "3 + 5 = " << add(3, 5) << std::endl;
    }
    
    // 4. 智能指针
    void example4() {
        // 好：使用 auto
        auto ptr = std::make_unique<int>(42);
        auto shared = std::make_shared<std::string>("hello");
        
        // 避免：不要这样写
        // std::unique_ptr<int> ptr2(new int(42));
    }
    
    // 5. 类型明确的简单变量
    void example5() {
        int count = 10;        // 好：类型明确
        auto count2 = 10;      // 也好，但可读性稍差
        
        std::string name = "Alice";  // 好：类型明确
        auto name2 = std::string("Bob");  // 也行
    }
};
```

### 2. **何时避免 auto**

```cpp
#include <iostream>
#include <vector>

class WhenNotToUseAuto {
public:
    // 1. 需要特定类型时
    void example1() {
        // 不好：无法控制精度
        auto x = 3.14;  // double
        auto y = 3.14f; // float
        
        // 好：明确指定类型
        float precise = 3.14f;
        double precise2 = 3.14;
    }
    
    // 2. 接口边界
    int calculate(int a, int b) {
        auto result = a + b;  // 函数内部可以用 auto
        return result;        // 但返回值类型要明确
    }
    
    // 3. 需要类型转换时
    void example3() {
        double value = 3.14;
        
        // 不好：类型不明确
        auto intValue = static_cast<int>(value);
        
        // 好：明确类型
        int intValue2 = static_cast<int>(value);
    }
    
    // 4. 影响代码可读性
    void example4() {
        // 不好：类型不清晰
        auto data = getSomeData();
        
        // 好：类型明确
        std::vector<int> data2 = getSomeData();
    }
    
private:
    std::vector<int> getSomeData() {
        return {1, 2, 3};
    }
};
```

## 九、decltype 和 decltype(auto)

### 1. **decltype**

```cpp
#include <iostream>
#include <type_traits>

void testDecltype() {
    int x = 10;
    const int cx = 20;
    int& rx = x;
    const int& crx = x;
    
    // decltype 获取表达式的类型
    decltype(x) a = 30;        // int
    decltype(cx) b = 40;       // const int
    decltype(rx) c = x;        // int&
    decltype(crx) d = x;       // const int&
    
    // decltype(表达式)
    decltype(x + 5.0) e;       // double
    decltype(x++) f;           // int (x++ 返回 int)
    decltype(++x) g = x;       // int& (++x 返回 int&)
    
    // decltype 在模板中的应用
    std::cout << std::boolalpha;
    std::cout << "a 是 int? " << std::is_same_v<decltype(a), int> << std::endl;
    std::cout << "b 是 const int? " << std::is_same_v<decltype(b), const int> << std::endl;
    std::cout << "c 是 int&? " << std::is_same_v<decltype(c), int&> << std::endl;
    std::cout << "e 是 double? " << std::is_same_v<decltype(e), double> << std::endl;
}
```

### 2. **decltype(auto)**

```cpp
#include <iostream>
#include <string>

// C++14: decltype(auto)
std::string getString() {
    return "Hello, World!";
}

const std::string& getConstRef() {
    static std::string str = "Hello";
    return str;
}

std::string& getRef() {
    static std::string str = "World";
    return str;
}

void testDecltypeAuto() {
    // auto: 值类型
    auto s1 = getString();           // std::string (拷贝)
    auto s2 = getConstRef();         // std::string (拷贝，忽略const和引用)
    auto s3 = getRef();              // std::string (拷贝，忽略引用)
    
    // auto&: 左值引用
    // auto& s4 = getString();       // 错误：不能绑定临时对象
    auto& s5 = getConstRef();        // const std::string&
    auto& s6 = getRef();             // std::string&
    
    // const auto&: const左值引用
    const auto& s7 = getString();    // const std::string&
    const auto& s8 = getConstRef();  // const std::string&
    const auto& s9 = getRef();       // const std::string&
    
    // decltype(auto): 完美转发返回类型
    decltype(auto) d1 = getString();     // std::string
    decltype(auto) d2 = getConstRef();   // const std::string&
    decltype(auto) d3 = getRef();        // std::string&
    
    // 在函数返回类型中使用
    auto function1() -> decltype(getString()) {
        return getString();  // std::string
    }
    
    decltype(auto) function2() {
        return getConstRef();  // const std::string&
    }
    
    std::cout << "s1 类型: " << typeid(s1).name() << std::endl;
    std::cout << "d2 类型: " << typeid(d2).name() << std::endl;
    std::cout << "d3 类型: " << typeid(d3).name() << std::endl;
}
```

## 十、实际应用示例

### 1. **配置解析器**

```cpp
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

// 配置值类型
using ConfigValue = std::variant<int, double, std::string, bool>;

class ConfigParser {
private:
    std::map<std::string, ConfigValue> config;
    
public:
    void set(const std::string& key, ConfigValue value) {
        config[key] = value;
    }
    
    template<typename T>
    T get(const std::string& key) const {
        auto it = config.find(key);
        if (it == config.end()) {
            throw std::runtime_error("配置项不存在: " + key);
        }
        
        try {
            return std::get<T>(it->second);
        } catch (const std::bad_variant_access&) {
            throw std::runtime_error("类型不匹配: " + key);
        }
    }
    
    // 自动推导返回类型
    auto getAuto(const std::string& key) const {
        auto it = config.find(key);
        if (it == config.end()) {
            throw std::runtime_error("配置项不存在: " + key);
        }
        
        // 使用 auto 简化访问
        return std::visit(auto&& value -> ConfigValue {
            return value;
        }, it->second);
    }
    
    void printAll() const {
        for (const auto& [key, value] : config) {
            std::cout << key << " = ";
            std::visit(auto&& val {
                std::cout << val;
            }, value);
            std::cout << std::endl;
        }
    }
};

void testConfigParser() {
    ConfigParser config;
    
    config.set("port", 8080);
    config.set("timeout", 30.5);
    config.set("server", std::string("localhost"));
    config.set("debug", true);
    
    // 使用 auto 简化代码
    auto port = config.get<int>("port");
    auto timeout = config.get<double>("timeout");
    auto server = config.get<std::string>("server");
    auto debug = config.get<bool>("debug");
    
    std::cout << "端口: " << port << std::endl;
    std::cout << "超时: " << timeout << std::endl;
    std::cout << "服务器: " << server << std::endl;
    std::cout << "调试: " << std::boolalpha << debug << std::endl;
    
    std::cout << "\n所有配置:" << std::endl;
    config.printAll();
}
```

### 2. **工厂模式**

```cpp
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <string>

// 产品基类
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

// 具体产品
class ConcreteProductA : public Product {
public:
    void use() override {
        std::cout << "使用产品A" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void use() override {
        std::cout << "使用产品B" << std::endl;
    }
};

// 工厂类
class ProductFactory {
private:
    std::map<std::string, std::function<std::unique_ptr<Product>()>> creators;
    
public:
    ProductFactory() {
        registerCreator("A",  { return std::make_unique<ConcreteProductA>(); });
        registerCreator("B",  { return std::make_unique<ConcreteProductB>(); });
    }
    
    void registerCreator(const std::string& type, 
                        std::function<std::unique_ptr<Product>()> creator) {
        creators[type] = creator;
    }
    
    auto create(const std::string& type) -> std::unique_ptr<Product> {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }
    
    // 使用 auto 简化
    auto createAuto(const std::string& type) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second();
        }
        return std::unique_ptr<Product>{};
    }
};

void testFactory() {
    ProductFactory factory;
    
    // 使用 auto 接受工厂返回的产品
    auto productA = factory.create("A");
    auto productB = factory.create("B");
    auto productC = factory.create("C");  // nullptr
    
    if (productA) productA->use();
    if (productB) productB->use();
    if (!productC) std::cout << "产品C不存在" << std::endl;
    
    // 注册新产品
    class ConcreteProductC : public Product {
    public:
        void use() override {
            std::cout << "使用产品C" << std::endl;
        }
    };
    
    factory.registerCreator("C",  { 
        return std::make_unique<ConcreteProductC>(); 
    });
    
    auto newProductC = factory.createAuto("C");
    if (newProductC) newProductC->use();
}
```

## 十一、常见错误

```cpp
#include <iostream>
#include <vector>

void commonMistakes() {
    // 错误1：auto 推导意外类型
    std::vector<bool> flags = {true, false, true};
    
    // 注意：vector<bool> 的引用返回代理对象
    auto flag = flags[0];  // 不是 bool&！
    // flag = false;       // 可能不会修改 flags[0]
    
    // 正确：明确类型
    bool flag2 = flags[0];
    // 或使用 static_cast
    auto flag3 = static_cast<bool>(flags[0]);
    
    // 错误2：auto 和临时对象
    auto getString =  { return std::string("temp"); };
    
    auto& strRef = getString();  // 错误：临时对象不能绑定到非const引用
    const auto& constRef = getString();  // 正确：延长生命周期
    
    // 错误3：auto 推导指针数组
    const char* strings[] = {"a", "b", "c"};
    
    auto arr = strings;     // const char** (指针数组退化)
    auto& arrRef = strings; // const char*[3] (数组引用)
    
    std::cout << "arr 类型: " << typeid(arr).name() << std::endl;
    std::cout << "arrRef 类型: " << typeid(arrRef).name() << std::endl;
    
    // 错误4：auto 忽略顶层 const
    const int x = 10;
    auto y = x;           // int，忽略 const
    y = 20;              // 可以修改
    
    const auto z = x;    // const int
    // z = 30;           // 错误
}
```

## 总结

### **auto 的优势**：
1. **代码简洁**：减少冗余类型声明
2. **类型安全**：避免隐式类型转换
3. **泛型友好**：适合模板和泛型编程
4. **重构友好**：类型改变时自动调整
5. **lambda必需**：存储lambda表达式的唯一方式

### **使用建议**：
1. **推荐使用**：
   - 迭代器和复杂类型
   - lambda表达式
   - 模板编程
   - 明确初始化的简单变量
   
2. **避免使用**：
   - 需要明确类型的接口
   - 影响代码可读性的情况
   - 需要特定类型转换时

### **最佳实践**：
```cpp
// 1. 使用 const auto& 遍历容器
for (const auto& item : container) {}

// 2. 使用 auto 处理迭代器
auto it = container.find(key);

// 3. 使用 auto 存储 lambda
auto func = int x { return x * 2; };

// 4. 使用 auto 处理复杂类型
auto result = std::make_unique<SomeClass>();

// 5. 明确简单类型
int count = 10;  // 比 auto count = 10; 更清晰
```

### **记忆口诀**：
```
auto 类型自动推，代码简洁又安全
遍历容器最好用，迭代器也方便
lambda 必须用 auto，模板编程更简单
const auto& 是常客，避免拷贝效率高
复杂类型用 auto，简单类型可明确
类型推导有规则，引用 const 要注意
```