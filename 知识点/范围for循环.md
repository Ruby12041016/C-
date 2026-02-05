# 范围 `for` 循环（Range-based for loop）

范围 `for` 循环是 C++11 引入的一种简化的循环方式，主要用于遍历容器（如数组、`std::vector`、`std::map` 等）或任何支持迭代的类型（如字符串）。它自动管理循环的开始和结束条件，使代码更加简洁。

## 基本语法

```cpp
for (declaration : container) {
    // 循环体
}
````

* `declaration`：声明一个变量，用于存储容器中每次迭代的元素。通常，类型会自动推导，也可以显式指定。
* `container`：要遍历的容器，可以是数组、容器类（如 `std::vector`、`std::list` 等）或任何支持迭代的类型。

* **常量引用**：如果容器中的元素较大（如 `std::string` 或其他大型对象），可以使用常量引用来避免不必要的拷贝操作：

  ```cpp
  for (const auto& n : vec) {
      std::cout << n << " ";
  }

  // 通过引用修改元素
  for (int &score : scores) {
      score += 5;  // 每个成绩再加5分
    }
  ```


## 注意事项

1. **使用引用**：当你不打算修改元素时，最好使用常量引用（`const auto&`）以提高效率并避免不必要的拷贝。

2. **修改容器内容**：如上所示，要修改容器中的元素，必须使用引用（`auto&`）而不是值类型。

## 总结

* 范围 `for` 循环是简化迭代过程的一种非常方便的方式。
* 对于不需要修改容器的场景，可以使用常量引用来避免不必要的拷贝。
* 如果需要修改容器内容，则使用普通引用。
* 适用于数组、`std::vector`、`std::list` 等任何支持迭代的容器类型。
---

```cpp
std::numeric_limits<std::streamsize>::max()
│   │             │               │
│   │             │               └── 里面的 max 函数
│   │             └── std 里面的 streamsize 类型
│   └── std 里面的 numeric_limits 类
└── std 命名空间
```
* 在C++中，字符串处理函数和C语言中用法相同，但储存在`#include <cstring>`中