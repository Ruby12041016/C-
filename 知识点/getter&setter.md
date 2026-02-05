# Getter/Setter详解（适合初学者）

## 一、什么是Getter/Setter？

**Getter（获取器）** 和 **Setter（设置器）** 是类中用于访问和修改私有成员变量的公有成员函数。

```cpp
class Student {
private:  // 私有成员，外部不能直接访问
    std::string name;
    int age;
    double score;
    
public:
    // Getter方法 - 获取私有成员的值
    std::string getName() const {  // const表示不修改对象
        return name;
    }
    
    int getAge() const {
        return age;
    }
    
    double getScore() const {
        return score;
    }
    
    // Setter方法 - 设置私有成员的值
    void setName(const std::string& newName) {
        name = newName;
    }
    
    void setAge(int newAge) {
        if (newAge > 0 && newAge < 150) {  // 添加验证
            age = newAge;
        } else {
            std::cout << "年龄无效！" << std::endl;
        }
    }
    
    void setScore(double newScore) {
        if (newScore >= 0 && newScore <= 100) {  // 添加验证
            score = newScore;
        } else {
            std::cout << "分数无效！" << std::endl;
        }
    }
};
```

## 二、为什么需要Getter/Setter？

### 1. **封装性：保护数据**

```cpp
// 没有封装的问题
class BadStudent {
public:  // 所有成员都是公有的
    std::string name;
    int age;
    double score;
};

void problem_example() {
    BadStudent s;
    s.name = "张三";
    s.age = 20;
    s.score = 85.5;
    
    // 可以直接修改，没有验证
    s.age = -10;    // 非法年龄！
    s.score = 150;  // 非法分数！
    
    // 可以直接访问，无法控制访问方式
    std::cout << s.score << std::endl;  // 可以直接看到成绩
}

// 使用Getter/Setter
class GoodStudent {
private:
    std::string name;
    int age;
    double score;
    bool isGraduated;  // 内部状态，不暴露给外界
    
public:
    // 构造函数初始化
    GoodStudent(const std::string& n, int a, double s) 
        : name(n), age(a), score(s), isGraduated(false) {
        if (a <= 0 || a > 120) age = 18;  // 默认值
        if (s < 0 || s > 100) score = 60;  // 默认值
    }
    
    // Getter
    std::string getName() const { return name; }
    int getAge() const { return age; }
    double getScore() const { return score; }
    
    // 只读属性，没有setter
    bool isStudentGraduated() const { 
        return isGraduated && score >= 60;  // 内部逻辑
    }
    
    // Setter
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        }
    }
    
    void setAge(int newAge) {
        if (newAge > 0 && newAge < 120) {
            age = newAge;
        }
    }
    
    void setScore(double newScore) {
        if (newScore >= 0 && newScore <= 100) {
            score = newScore;
            if (score >= 60) {
                isGraduated = true;  // 内部状态变化
            }
        }
    }
};
```


## 三、Getter/Setter的不同写法

### 1. **基本写法**

```cpp
class BasicExample {
private:
    int value;
    
public:
    // 基本Getter
    int getValue() const {
        return value;
    }
    
    // 基本Setter
    void setValue(int v) {
        value = v;
    }
};
```

### 2. **返回引用（谨慎使用！）**

```cpp
class ReferenceExample {
private:
    std::string name;
    std::vector<int> scores;
    
public:
    // 返回const引用（只读）
    const std::string& getName() const {
        return name;
    }
    
    // 返回引用（可修改，危险！）
    std::string& getName() {  // 重载，非const版本
        return name;  // 危险：破坏了封装！
    }
    
    // 返回const引用，安全的
    const std::vector<int>& getScores() const {
        return scores;
    }
    
    // 更好的方式：提供修改方法
    void addScore(int score) {
        if (score >= 0 && score <= 100) {
            scores.push_back(score);
        }
    }
    
    void clearScores() {
        scores.clear();
    }
    
    // 需要返回可修改引用时，要特别小心
    std::vector<int>& getMutableScores() {  // 明确命名
        return scores;  // 调用者知道自己在做什么
    }
};
```

### 3. **计算属性**

```cpp
class Rectangle {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // 基本Getter
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // Setter
    void setWidth(double w) {
        if (w > 0) width = w;
    }
    
    void setHeight(double h) {
        if (h > 0) height = h;
    }
    
    // 计算属性（没有对应的数据成员）
    double getArea() const {
        return width * height;
    }
    
    double getPerimeter() const {
        return 2 * (width + height);
    }
    
    double getDiagonal() const {
        return std::sqrt(width*width + height*height);
    }
    
    // 只读属性
    bool isSquare() const {
        return width == height;
    }
};
```

### 4. **只读属性**

```cpp
class ReadOnlyExample {
private:
    int id;  // 一旦设置，不可修改
    std::string name;
    const std::string type = "Student";  // 常量
    
public:
    ReadOnlyExample(int i, const std::string& n) : id(i), name(n) {}
    
    // 只有Getter，没有Setter
    int getId() const { return id; }
    
    // 普通属性
    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }
    
    // 常量属性
    const std::string& getType() const { return type; }
    
    // 计算属性
    std::string getInfo() const {
        return "ID: " + std::to_string(id) + 
               ", Name: " + name + 
               ", Type: " + type;
    }
};
```


## 四、Getter/Setter的设计原则

### 1. **何时用Getter？何时用Setter？**

```cpp
class DesignExample {
private:
    int id;           // 只有getter
    std::string name; // 有getter和setter
    double price;     // 有getter，setter有验证
    int count;        // 有getter，通过方法修改
    
public:
    DesignExample(int i, const std::string& n, double p) 
        : id(i), name(n), price(p), count(0) {}
    
    // 只有getter的情况
    int getId() const { return id; }  // 创建后不可修改
    
    // 有getter和setter的情况
    const std::string& getName() const { return name; }
    void setName(const std::string& n) { 
        if (!n.empty()) name = n; 
    }
    
    // 有验证的setter
    double getPrice() const { return price; }
    void setPrice(double p) { 
        if (p >= 0) price = p; 
    }
    
    // 只有操作方法，没有setter
    int getCount() const { return count; }
    void increment() { count++; }
    void decrement() { 
        if (count > 0) count--; 
    }
    void reset() { count = 0; }
    
    // 计算属性
    double getTotal() const { 
        return price * count; 
    }
};
```

### 2. **const正确性**

```cpp
class ConstCorrectness {
private:
    mutable int accessCount;  // mutable: 可以在const方法中修改
    std::string data;
    
public:
    ConstCorrectness(const std::string& d) : data(d), accessCount(0) {}
    
    // const Getter: 不会修改对象
    const std::string& getData() const {
        accessCount++;  // 可以修改mutable成员
        return data;
    }
    
    // 非const Getter: 可能修改对象
    std::string& getData() {  // 重载
        return data;  // 返回引用，允许修改
    }
    
    int getAccessCount() const { 
        return accessCount; 
    }
};

void const_example() {
    const ConstCorrectness obj1("常量对象");
    // obj1.getData() = "修改";  // 错误：不能修改常量对象
    
    ConstCorrectness obj2("非常量对象");
    obj2.getData() = "可以修改";  // 正确
}
```

## 五、常见错误

```cpp
// 错误1：过度使用getter/setter
class OveruseExample {
private:
    int a, b, c, d, e;  // 所有字段都有getter/setter
    
public:
    int getA() const { return a; }
    void setA(int v) { a = v; }
    int getB() const { return b; }
    void setB(int v) { b = v; }
    // ... 太多了！
    // 问题：这还不如直接用公有成员！
};

// 正确做法：暴露行为，而不是数据
class GoodExample {
private:
    int x, y;
    
public:
    void move(int dx, int dy) {  // 暴露行为
        x += dx;
        y += dy;
    }
    
    Point getPosition() const {  // 返回值对象
        return Point(x, y);
    }
};

// 错误2：返回内部数据的引用
class BadReturnExample {
private:
    std::vector<int> data;
    
public:
    std::vector<int>& getData() {  // 危险！
        return data;  // 外部可以修改内部数据
    }
    
    const std::vector<int>& getData() const {  // 正确
        return data;  // 返回const引用
    }
};
```


## 六、总结要点

### **什么时候用Getter/Setter？**
1. 需要控制数据的访问和修改
2. 需要验证数据
3. 需要记录数据访问日志
4. 需要触发其他操作（如观察者模式）

### **什么时候不用Getter/Setter？**
1. 简单数据结构（用struct）
2. 内部辅助类
3. 性能敏感的代码
4. 应该用行为方法替代的情况

### **Getter设计原则：**
1. 命名：`getXxx()` 或 `isXxx()` 或 `hasXxx()`
2. 尽量返回const引用或值
3. 添加const修饰符
4. 可以返回计算属性

### **Setter设计原则：**
1. 命名：`setXxx()`
2. 添加数据验证
3. 考虑返回bool表示成功/失败
4. 或者抛出异常
5. 可以返回引用支持链式调用


```

记住：**Getter/Setter是工具，不是目标**。目标是良好的封装和易用的接口。