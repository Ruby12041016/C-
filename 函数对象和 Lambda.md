# 函数对象和Lambda核心要点

## 一、Lambda表达式

### 1. **Lambda的基本形式**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void lambda_basics() {
    // 最简单的lambda
    auto sayHello =  {
        std::cout << "Hello, Lambda!" << std::endl;
    };
    sayHello();
    
    // 带参数的lambda
    auto add = int a, int b {
        return a + b;
    };
    std::cout << "3 + 5 = " << add(3, 5) << std::endl;
    
    // 立即调用的lambda
    int result = int x { return x * x; }(5);
    std::cout << "5的平方: " << result << std::endl;
}
```

### 2. **捕获列表**

```cpp
void capture_basics() {
    int x = 10;
    int y = 20;
    
    // 1. 什么都不捕获 []
    auto func1 = []() {  // ← 这里应该是 []
        std::cout << "独立lambda" << std::endl;
    };
    
    // 2. 捕获所有外部变量（值捕获）[=]
    auto func2 = [=]() {  // ← 这里应该是 [=]
        std::cout << "x = " << x << ", y = " << y << std::endl;
        // 注意：这里不能修改x,y
    };
    
    // 3. 捕获所有外部变量（引用捕获）[&]
    auto func3 = [&]() {  // ← 这里应该是 [&]
        x = 100;  // 可以修改外部变量
        std::cout << "修改后的x = " << x << std::endl;
    };
    
    // 4. 混合捕获 [x, &y]
    auto func4 = [x, &y]() {  // ← 这里应该是 [x, &y]
        // x是值捕获（只读），y是引用捕获（可读写）
        y = 200;
        std::cout << "x=" << x << ", y=" << y << std::endl;
    };
    
    // 初学者建议：明确指定要捕获的变量，避免[=]或[&]
    auto safe_func = [x]() {  // ← 这里应该是 [x]
        std::cout << "安全：只捕获了x" << std::endl;
    };
}
```

### 3. **Lambda在STL中的实际应用**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>  // sort, find_if, count_if, transform, for_each
#include <iterator>   // back_inserter

void lambda_with_stl() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // 1. 排序（从大到小）
    std::sort(numbers.begin(), numbers.end(), 
              [](int a, int b) { return a > b; }); 

    // 2. 查找第一个大于5的数
    auto it = std::find_if(numbers.begin(), numbers.end(),
        [](int n) { return n > 5; }); 
    if (it != numbers.end()) {
        std::cout << "找到: " << *it << std::endl;
    }
    
    // 3. 计数偶数
    int even_count = std::count_if(numbers.begin(), numbers.end(),
        [](int n) { return n % 2 == 0; });  
    std::cout << "偶数个数: " << even_count << std::endl;
    
    // 4. 每个元素乘2
    std::vector<int> doubled;
    std::transform(numbers.begin(), numbers.end(), 
                   std::back_inserter(doubled),
                   [](int n) { return n * 2; }); 

    // 5. 打印所有元素
    std::cout << "所有元素: ";
    std::for_each(numbers.begin(), numbers.end(),
        [](int n) { std::cout << n << " "; });  
    std::cout << std::endl;
}
```

## 二、函数对象（Functor）

### 1. **最简单的函数对象**

```cpp
// 最简单的函数对象
class Adder {
public:
    // 重载函数调用运算符
    int operator()(int a, int b) const {
        return a + b;
    }
};

class Printer {
public:
    void operator()(const std::string& message) const {
        std::cout << "消息: " << message << std::endl;
    }
};

void functor_basics() {
    Adder add;
    std::cout << "10 + 20 = " << add(10, 20) << std::endl;
    
    Printer print;
    print("你好，世界！");
    
    // 带状态的函数对象
    class Counter {
        int count = 0;
    public:
        int operator()() {
            return ++count;
        }
    };
    
    Counter counter;
    std::cout << "计数: " << counter() << std::endl;  // 1
    std::cout << "计数: " << counter() << std::endl;  // 2
}
```

### 2. **什么时候用函数对象？**

```cpp
// 情况1：需要重复使用
class GreaterThan {
    int threshold;
public:
    GreaterThan(int t) : threshold(t) {}
    
    bool operator()(int value) const {
        return value > threshold;
    }
};

void when_use_functor() {
    std::vector<int> nums = {1, 5, 10, 15, 20};
    
    // 使用函数对象（可复用）
    GreaterThan gt5(5);
    GreaterThan gt10(10);
    
    int count1 = std::count_if(nums.begin(), nums.end(), gt5);   // 大于5的
    int count2 = std::count_if(nums.begin(), nums.end(), gt10);  // 大于10的
    
    std::cout << "大于5: " << count1 << ", 大于10: " << count2 << std::endl;
    
    // 情况2：需要多个参数
    class RangeCheck {
        int min, max;
    public:
        RangeCheck(int m, int M) : min(m), max(M) {}
        
        bool operator()(int value) const {
            return value >= min && value <= max;
        }
    };
    
    RangeCheck inRange(5, 15);
    int count3 = std::count_if(nums.begin(), nums.end(), inRange);
    std::cout << "5到15之间: " << count3 << std::endl;
}
```

### **口诀总结**
```
Lambda三步走：
1. 写小括号：参数
2. 写大括号：函数体
3. 写中括号：要用的外部变量

一句话记住：
- 管理内存用智能指针
- 临时函数用lambda
- 重复使用用函数对象
```


