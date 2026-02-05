

# 类与对象（class / struct / 封装思想）

## 1. **什么是类（class）**

C++ 中的类是**用户自定义类型**，它定义了对象的**属性**和**行为**。通过类，我们能够创建多个对象，每个对象都有自己的数据和方法。

```cpp
class Person {
public:
    int age;
    string name;

    // 成员函数
    void show() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
```

### 📌 解释：

* **class**：定义一个类。
* **成员变量**：`age` 和 `name`，表示类的属性。
* **成员函数**：`show()`，表示类的行为。

> **类是模板**，**对象是实例化出来的实例**。也就是说，类是对象的蓝图。

---

## 2. **类与对象**

类本身不占内存，只有对象实例化后，才会占用内存。每个对象都有自己的一份**数据**。

### 示例：

```cpp
Person p1, p2; // 创建两个对象 p1 和 p2

p1.name = "Tom";
p1.age = 18;
p1.show();  // 输出 "Name: Tom, Age: 18"

p2.name = "Jerry";
p2.age = 20;
p2.show();  // 输出 "Name: Jerry, Age: 20"
```

* **p1** 和 **p2** 是 **Person** 类的两个实例（对象），它们有不同的属性值。

---

## 3. **构造函数（Constructor）**

构造函数是在创建对象时自动调用的特殊成员函数。它用于初始化对象的状态。类中的构造函数名必须与类名相同。

### 默认构造函数：

```cpp
class Person {
public:
    string name;
    int age;

    // 默认构造函数
    Person() {
        name = "Unknown";
        age = 0;
    }
};

Person p1;  // 自动调用默认构造函数
cout << p1.name << " " << p1.age << endl;  // 输出 "Unknown 0"
```

### 带参构造函数：

```cpp
class Person {
public:
    string name;
    int age;

    // 带参构造函数
    Person(string n, int a) {
        name = n;
        age = a;
    }
};

Person p2("Tom", 20);  // 使用带参构造函数
```

### 构造函数初始化列表：

构造函数初始化列表在创建对象时直接初始化成员变量，而不是先默认初始化再赋值。

```cpp
class Person {
public:
    string name;
    int age;

    // 构造函数初始化列表
    Person(string n, int a) : name(n), age(a) {}
};
```

---

## 4. **析构函数（Destructor）**

析构函数用于在对象生命周期结束时释放资源。它会在对象销毁时自动调用。析构函数的名字与类名相同，但前面有一个波浪号（`~`）。
* 何时调用析构函数：
1. 对象离开作用域
2. delete动态分配的对象
3. 对象是另一个对象的成员，那个对象被销毁时
4. 临时对象创建后立即销毁

```cpp
class Person {
public:
    // 析构函数
    ~Person() {
        cout << "Destructor called!" << endl;
    }
};

Person p1;  // 当 p1 被销毁时，析构函数自动调用
```

---

## 5. **成员函数（Member Function）**

成员函数用于描述类的行为，通常会操作类中的成员变量。它们可以是普通的成员函数，也可以是常量成员函数（`const`）。

### 常规成员函数：

```cpp
class Person {
public:
    string name;
    int age;

    void show() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
```

### 常量成员函数：

常量成员函数声明在函数末尾加上 `const`，表示该函数不能修改对象的成员变量。

```cpp
class Person {
public:
    string name;
    int age;

    // 常量成员函数
    void show() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
```

---

## 6. **访问控制：public、private、protected**

C++ 通过访问控制符来限定类成员的访问权限：

* **public**：公开访问，类外可以访问。
* **private**：私有访问，类外无法访问，只有类内和友元函数可以访问。
* **protected**：受保护访问，类外无法访问，但继承的子类可以访问。

### 示例：

```cpp
class Person {
public:
    string name;
    int age;

private:
    double salary;  // 只能在类内访问

public:
    void setSalary(double s) { salary = s; }  // 设置 salary 的方法
    double getSalary() { return salary; }     // 获取 salary 的方法
};
```

```cpp
Person p;
p.name = "Tom";  // public
p.age = 20;      // public
// p.salary = 50000;  // ❌ 不能访问 private 成员
```

---

## 7. **构造函数初始化列表**

构造函数初始化列表比在构造函数体内赋值更高效。它直接在构造时初始化成员变量。

```cpp
class Person {
public:
    string name;
    int age;

    // 构造函数初始化列表
    Person(string n, int a) : name(n), age(a) {
        cout << "Person created!" << endl;
    }
};
```

> **注意**：构造函数初始化列表中的初始化顺序是按照成员声明顺序来初始化的，而不是初始化列表中的顺序。

---

## 8. **this 指针**

C++ 中，每个成员函数都有一个隐含的 `this` 指针，指向当前对象。在成员函数内部可以使用 `this` 指针来区分成员变量和函数参数。

```cpp
class Person {
public:
    int age;

    void setAge(int age) {
        this->age = age;  // 通过 this 指针区分成员变量和参数
    }
};
```

---

## 9. **类的成员初始化顺序**

C++ 中，类成员的初始化顺序是按照成员变量在类中声明的顺序，而不是初始化列表中的顺序。

```cpp
class Person {
public:
    int a;
    int b;

    // b 先初始化，再初始化 a
    Person() : b(20), a(10) {  
        cout << a << " " << b << endl;
    }
};
```

---

