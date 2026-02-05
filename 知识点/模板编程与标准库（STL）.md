# 模板编程与标准库（STL）

## ✅ 1. **模板（Templates）**

模板允许你编写 **泛型代码**，从而使得函数或类可以接受不同类型的数据。模板可以分为**函数模板**和**类模板**。

### 1.1 **函数模板**

函数模板让你编写一个通用的函数，可以处理多种数据类型。

#### 示例：函数模板

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 5) << endl;       // 输出 8
    cout << add(2.5, 3.1) << endl;   // 输出 5.6
}
```

### 解析：

* `template <typename T>`：定义一个函数模板，`T` 是占位符，表示任意类型。
* `add` 函数在调用时会根据传入的参数类型来推导 `T`。

---

### 1.2 **类模板**

类模板允许你定义一个类，该类可以根据不同的类型创建不同的实例。

#### 示例：类模板

```cpp
template <typename T>
class Box {
private:
    T value;

public:
    Box(T v) : value(v) {}

    T getValue() {
        return value;
    }
};

int main() {
    Box<int> intBox(5);
    cout << intBox.getValue() << endl;  // 输出 5

    Box<string> strBox("Hello");
    cout << strBox.getValue() << endl;  // 输出 Hello
}
```

### 解析：

* `template <typename T>`：定义一个类模板，`T` 是占位符，表示任意类型。
* `Box<int>` 和 `Box<string>`：模板类的不同实例化类型。

---

### 1.3 **模板的特化**

模板特化允许你为某些特定类型提供定制化实现。

#### 示例：类模板特化

```cpp
template <typename T>
class Box {
public:
    T value;
    Box(T v) : value(v) {}
    void show() {
        cout << "General type: " << value << endl;
    }
};

// 针对 int 类型的特化
template <>
class Box<int> {
public:
    int value;
    Box(int v) : value(v) {}
    void show() {
        cout << "Integer type: " << value << endl;
    }
};

int main() {
    Box<double> doubleBox(5.5);
    doubleBox.show();  // 输出: General type: 5.5

    Box<int> intBox(10);
    intBox.show();  // 输出: Integer type: 10
}
```

### 解析：

* 为 `int` 类型提供了专门的模板特化版本，重写了 `show` 方法。

---

## ✅ 2. **标准库（STL）**

C++ 标准库提供了许多预定义的数据结构和算法，如**容器**、**算法**、**迭代器**等。常见的容器包括 `vector`、`list`、`map`、`set` 等。

### 2.1 **`vector` 容器**

`vector` 是一个动态数组，支持快速随机访问，适用于需要频繁插入和删除元素的场景。

#### 示例：使用 `vector`

```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    // 添加元素
    vec.push_back(6);

    // 遍历元素
    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;  // 输出: 1 2 3 4 5 6

    // 删除最后一个元素
    vec.pop_back();
    cout << vec.size() << endl;  // 输出: 5
}
```

### 解析：

* `push_back()`：在 `vector` 的末尾添加元素。
* `pop_back()`：删除 `vector` 的最后一个元素。

---

### 2.2 **`map` 容器**

`map` 是一个**关联容器**，它存储的是键值对。每个键（key）都是唯一的，可以通过键来访问对应的值。

#### 示例：使用 `map`

```cpp
#include <map>
#include <iostream>
using namespace std;

int main() {
    map<string, int> ageMap;

    // 插入键值对
    ageMap["Tom"] = 20;
    ageMap["Jerry"] = 22;

    // 遍历 map
    for (auto& p : ageMap) {
        cout << p.first << " is " << p.second << " years old." << endl;
    }
}
```

### 解析：

* `map<string, int>`：定义了一个映射，键为 `string` 类型，值为 `int` 类型。
* 遍历 `map` 时，`first` 是键，`second` 是值。

---

### 2.3 **`set` 容器**

`set` 是一个不允许重复元素的容器，所有元素都是唯一的，并且会自动按照一定规则排序。

#### 示例：使用 `set`

```cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    set<int> s = {1, 2, 3, 3, 4, 5};

    // 自动去重
    s.insert(6);
    s.insert(2);

    // 遍历 set
    for (int v : s) {
        cout << v << " ";
    }
    cout << endl;  // 输出: 1 2 3 4 5 6
}
```

### 解析：

* `set` 自动去重，`insert` 操作不会插入重复元素。

---

## ✅ 3. **STL 算法**

STL 提供了丰富的算法，可以对容器进行操作，如排序、查找、删除等。

### 3.1 **排序**

```cpp
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> vec = {5, 3, 1, 4, 2};
    sort(vec.begin(), vec.end());  // 升序排序

    for (int v : vec) {
        cout << v << " ";  // 输出: 1 2 3 4 5
    }
    cout << endl;
}
```

### 3.2 **查找**

```cpp
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    auto it = find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) {
        cout << "Found: " << *it << endl;  // 输出: Found: 3
    } else {
        cout << "Not Found!" << endl;
    }
}
```

### 解析：

* `sort()`：对容器中的元素进行排序。
* `find()`：查找元素，返回指向元素的迭代器。

---

## 🧪 本节练习

---

### ✏️ 练习 1：实现一个泛型 `swap` 函数

使用函数模板实现一个 `swap` 函数，交换两个变量的值。

```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

---

### ✏️ 练习 2：实现一个 `Stack` 类模板

使用类模板实现一个简单的栈（`push` 和 `pop` 功能）。

```cpp
template <typename T>
class Stack {
private:
    vector<T> vec;

public:
    void push(T val) {
        vec.push_back(val);
    }

    T pop() {
        if (vec.empty()) {
            throw runtime_error("Stack is empty!");
        }
        T val = vec.back();
        vec.pop_back();
        return val;
    }

    bool isEmpty() {
        return vec.empty();
    }
};
```

---

### ✏️ 练习 3：使用 `map` 统计单词频率

写一个程序，使用 `map` 容器统计一句话中每个单词出现的次数。

---

### ✏️ 练习 4：使用 `set` 删除重复元素

给定一个整数数组，使用 `set` 删除其中的重复元素。

---


