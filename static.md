# 静态成员详解

## 一、什么是静态成员？

**静态成员** 是属于类本身的成员，而不是属于类的某个对象。所有对象共享同一份静态成员。

```cpp
#include <iostream>

class Counter {
private:
    static int count;  // 静态成员变量声明
    
public:
    Counter() {
        count++;  // 每创建一个对象，count加1
    }
    
    ~Counter() {
        count--;  // 每销毁一个对象，count减1
    }
    
    // 静态成员函数
    static int getCount() {
        return count;
    }
    
    static void reset() {
        count = 0;
    }
};

// 静态成员变量定义和初始化
int Counter::count = 0;

int main() {
    std::cout << "初始数量: " << Counter::getCount() << std::endl;  // 0
    
    Counter c1;
    std::cout << "创建c1后: " << Counter::getCount() << std::endl;  // 1
    
    {
        Counter c2;
        std::cout << "创建c2后: " << Counter::getCount() << std::endl;  // 2
    }  // c2离开作用域，被销毁
    
    std::cout << "c2销毁后: " << Counter::getCount() << std::endl;  // 1
    
    Counter::reset();
    std::cout << "重置后: " << Counter::getCount() << std::endl;  // 0
    
    return 0;
}
```

## 二、静态成员变量

### 1. **基本概念**

```cpp
class School {
private:
    std::string name;        // 普通成员变量：每个对象有自己的副本
    static std::string motto;  // 静态成员变量：所有对象共享
    
public:
    School(const std::string& n) : name(n) {}
    
    void display() {
        // 可以访问静态成员
        std::cout << "学校: " << name << ", 校训: " << motto << std::endl;
    }
    
    static void changeMotto(const std::string& newMotto) {
        motto = newMotto;  // 修改静态成员
    }
};

// 静态成员变量定义和初始化
std::string School::motto = "勤奋 求实 创新";

int main() {
    School s1("第一中学");
    School s2("第二中学");
    
    s1.display();  // 学校: 第一中学, 校训: 勤奋 求实 创新
    s2.display();  // 学校: 第二中学, 校训: 勤奋 求实 创新
    
    // 修改静态成员
    School::changeMotto("团结 进取 卓越");
    
    s1.display();  // 学校: 第一中学, 校训: 团结 进取 卓越
    s2.display();  // 学校: 第二中学, 校训: 团结 进取 卓越
    
    return 0;
}
```

### 2. **多个对象共享的例子**

```cpp
#include <iostream>
#include <vector>

class BankAccount {
private:
    std::string owner;
    double balance;
    
    // 静态成员
    static double totalMoney;       // 所有账户总金额
    static int accountCount;        // 账户总数
    static const double interestRate;  // 常量静态成员
    
public:
    BankAccount(const std::string& name, double initial = 0) 
        : owner(name), balance(initial) {
        totalMoney += initial;
        accountCount++;
    }
    
    ~BankAccount() {
        totalMoney -= balance;
        accountCount--;
    }
    
    // 存款
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            totalMoney += amount;
        }
    }
    
    // 取款
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            totalMoney -= amount;
            return true;
        }
        return false;
    }
    
    // Getter
    double getBalance() const { return balance; }
    std::string getOwner() const { return owner; }
    
    // 静态函数
    static double getTotalMoney() { return totalMoney; }
    static int getAccountCount() { return accountCount; }
    static double getInterestRate() { return interestRate; }
    
    // 计算利息
    double calculateInterest() const {
        return balance * interestRate;
    }
    
    // 显示账户信息
    void display() const {
        std::cout << "户主: " << owner 
                  << ", 余额: " << balance
                  << ", 利息: " << calculateInterest() << std::endl;
    }
};

// 静态成员定义和初始化
double BankAccount::totalMoney = 0;
int BankAccount::accountCount = 0;
const double BankAccount::interestRate = 0.03;  // 3%年利率

int main() {
    std::cout << "初始状态:" << std::endl;
    std::cout << "账户数: " << BankAccount::getAccountCount() 
              << ", 总金额: " << BankAccount::getTotalMoney() 
              << std::endl;
    
    BankAccount alice("Alice", 1000);
    BankAccount bob("Bob", 2000);
    
    std::cout << "\n创建两个账户后:" << std::endl;
    std::cout << "账户数: " << BankAccount::getAccountCount()  // 2
              << ", 总金额: " << BankAccount::getTotalMoney()  // 3000
              << std::endl;
    
    alice.display();
    bob.display();
    
    alice.deposit(500);
    bob.withdraw(300);
    
    std::cout << "\n交易后:" << std::endl;
    std::cout << "总金额: " << BankAccount::getTotalMoney() << std::endl;  // 3200
    alice.display();
    bob.display();
    
    {
        BankAccount temp("临时账户", 500);
        std::cout << "\n创建临时账户后, 账户数: " 
                  << BankAccount::getAccountCount() << std::endl;  // 3
    }  // 临时账户销毁
    
    std::cout << "临时账户销毁后, 账户数: " 
              << BankAccount::getAccountCount() << std::endl;  // 2
    
    return 0;
}
```

## 三、静态成员函数

### 1. **基本用法**

```cpp
class MathUtils {
private:
    // 静态成员函数不能访问非静态成员
    // int data;  // 错误：静态函数不能访问
    
    static int callCount;  // 静态成员
    
public:
    // 静态工具函数
    static int add(int a, int b) {
        callCount++;
        return a + b;
    }
    
    static int multiply(int a, int b) {
        callCount++;
        return a * b;
    }
    
    static double circleArea(double radius) {
        callCount++;
        return 3.14159 * radius * radius;
    }
    
    static int getCallCount() {
        return callCount;
    }
    
    static void resetCount() {
        callCount = 0;
    }
    
    // 工厂方法
    static MathUtils* create() {
        return new MathUtils();
    }
};

int MathUtils::callCount = 0;

int main() {
    // 通过类名调用静态函数
    std::cout << "3 + 5 = " << MathUtils::add(3, 5) << std::endl;
    std::cout << "4 * 6 = " << MathUtils::multiply(4, 6) << std::endl;
    std::cout << "半径5的圆面积: " << MathUtils::circleArea(5) << std::endl;
    
    std::cout << "函数调用次数: " << MathUtils::getCallCount() << std::endl;
    
    MathUtils::resetCount();
    std::cout << "重置后调用次数: " << MathUtils::getCallCount() << std::endl;
    
    return 0;
}
```

### 2. **静态函数的特点**

```cpp
class Example {
private:
    int normalVar;           // 普通成员变量
    static int staticVar;    // 静态成员变量
    static const int constStaticVar = 100;  // 静态常量
    
public:
    Example(int val) : normalVar(val) {}
    
    // 普通函数：可以访问所有成员
    void normalFunction() {
        normalVar = 10;           // ✓ 可以访问普通成员
        staticVar = 20;           // ✓ 可以访问静态成员
        // 可以访问静态常量
    }
    
    // 静态函数：只能访问静态成员
    static void staticFunction() {
        // normalVar = 10;         // ✗ 错误：不能访问普通成员
        staticVar = 20;           // ✓ 可以访问静态成员
        
        // 创建对象来访问普通成员
        Example obj(100);
        obj.normalVar = 30;       // ✓ 通过对象可以访问
    }
    
    // 静态函数不能是const
    // static void func() const {}  // 错误！
    
    // 静态函数可以重载
    static void display() {
        std::cout << "静态display" << std::endl;
    }
    
    void display() const {
        std::cout << "普通display, normalVar = " << normalVar << std::endl;
    }
};

int Example::staticVar = 0;

int main() {
    // 通过类名调用静态函数
    Example::staticFunction();
    Example::display();
    
    // 通过对象调用
    Example obj(50);
    obj.display();           // 调用普通函数
    obj.staticFunction();    // 也可以，但不推荐
    
    return 0;
}
```

## 四、静态常量成员

```cpp
class Constants {
public:
    // 静态常量可以在类内初始化（必须是整数类型）
    static const int MAX_SIZE = 100;
    static const char SEPARATOR = ',';
    static const bool DEBUG_MODE = false;
    
    // 非整数类型需要在类外定义
    static const double PI;  // 类内只能声明
    
    // 静态常量数组
    static const int DAYS_IN_WEEK = 7;
    static const std::string DAY_NAMES[7];  // 需要类外定义
    
    // 使用静态常量
    static bool isValidSize(int size) {
        return size > 0 && size <= MAX_SIZE;
    }
    
    static double circleArea(double radius) {
        return PI * radius * radius;
    }
};

// 类外定义
const double Constants::PI = 3.14159265358979;
const std::string Constants::DAY_NAMES[7] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", 
    "Thursday", "Friday", "Saturday"
};

int main() {
    std::cout << "最大大小: " << Constants::MAX_SIZE << std::endl;
    std::cout << "圆周率: " << Constants::PI << std::endl;
    std::cout << "半径5的圆面积: " << Constants::circleArea(5) << std::endl;
    
    std::cout << "\n一周七天:" << std::endl;
    for (int i = 0; i < Constants::DAYS_IN_WEEK; i++) {
        std::cout << Constants::DAY_NAMES[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## 五、实际应用场景

### 1. **单例模式（Singleton）**

```cpp
class Logger {
private:
    // 1. 私有构造函数
    Logger() {
        std::cout << "Logger created" << std::endl;
    }
    
    // 2. 静态实例指针
    static Logger* instance;
    
    std::vector<std::string> logs;
    
public:
    // 3. 删除拷贝构造函数和赋值运算符
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    // 4. 静态获取实例方法
    static Logger& getInstance() {
        if (instance == nullptr) {
            instance = new Logger();
        }
        return *instance;
    }
    
    // 日志功能
    void log(const std::string& message) {
        logs.push_back(message);
        std::cout << "[LOG] " << message << std::endl;
    }
    
    void showAllLogs() {
        std::cout << "\n=== 所有日志 ===" << std::endl;
        for (const auto& msg : logs) {
            std::cout << msg << std::endl;
        }
    }
    
    // 清理
    static void destroy() {
        delete instance;
        instance = nullptr;
    }
};

// 初始化静态成员
Logger* Logger::instance = nullptr;

int main() {
    // 获取唯一的Logger实例
    Logger& logger1 = Logger::getInstance();
    logger1.log("程序启动");
    
    // 再次获取，得到的是同一个实例
    Logger& logger2 = Logger::getInstance();
    logger2.log("用户登录");
    
    // 验证是同一个实例
    logger1.showAllLogs();  // 显示两条日志
    
    Logger::destroy();
    
    return 0;
}
```

### 2. **对象工厂**

```cpp
#include <string>
#include <memory>

class Animal {
public:
    virtual void speak() = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "汪汪！" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        std::cout << "喵喵！" << std::endl;
    }
};

class Bird : public Animal {
public:
    void speak() override {
        std::cout << "叽叽！" << std::endl;
    }
};

class AnimalFactory {
private:
    // 私有构造函数，不能创建对象
    AnimalFactory() = delete;
    
public:
    // 静态工厂方法
    static std::unique_ptr<Animal> createAnimal(const std::string& type) {
        if (type == "dog") {
            return std::make_unique<Dog>();
        } else if (type == "cat") {
            return std::make_unique<Cat>();
        } else if (type == "bird") {
            return std::make_unique<Bird>();
        } else {
            std::cerr << "未知动物类型: " << type << std::endl;
            return nullptr;
        }
    }
    
    // 获取所有支持的动物类型
    static void showSupportedAnimals() {
        std::cout << "支持的动物类型: dog, cat, bird" << std::endl;
    }
    
    // 创建随机动物
    static std::unique_ptr<Animal> createRandomAnimal() {
        static const std::string types[] = {"dog", "cat", "bird"};
        static int count = 0;
        
        std::string type = types[count % 3];
        count++;
        
        return createAnimal(type);
    }
};

int main() {
    AnimalFactory::showSupportedAnimals();
    
    auto dog = AnimalFactory::createAnimal("dog");
    if (dog) dog->speak();
    
    auto cat = AnimalFactory::createAnimal("cat");
    if (cat) cat->speak();
    
    auto random1 = AnimalFactory::createRandomAnimal();
    auto random2 = AnimalFactory::createRandomAnimal();
    auto random3 = AnimalFactory::createRandomAnimal();
    
    if (random1) random1->speak();
    if (random2) random2->speak();
    if (random3) random3->speak();
    
    return 0;
}
```

### 3. **配置管理器**

```cpp
#include <string>
#include <map>
#include <iostream>

class ConfigManager {
private:
    static std::map<std::string, std::string> config;
    static bool isLoaded;
    
    // 私有构造函数
    ConfigManager() = default;
    
public:
    // 加载配置
    static bool loadConfig(const std::string& filename = "config.txt") {
        // 模拟从文件加载
        config["server"] = "localhost";
        config["port"] = "8080";
        config["timeout"] = "30";
        config["debug"] = "false";
        
        isLoaded = true;
        std::cout << "配置已加载" << std::endl;
        return true;
    }
    
    // 获取配置值
    static std::string get(const std::string& key) {
        if (!isLoaded) {
            loadConfig();
        }
        
        auto it = config.find(key);
        if (it != config.end()) {
            return it->second;
        }
        return "";
    }
    
    // 设置配置值
    static void set(const std::string& key, const std::string& value) {
        if (!isLoaded) {
            loadConfig();
        }
        config[key] = value;
    }
    
    // 获取整数配置
    static int getInt(const std::string& key) {
        std::string value = get(key);
        if (!value.empty()) {
            return std::stoi(value);
        }
        return 0;
    }
    
    // 获取布尔配置
    static bool getBool(const std::string& key) {
        std::string value = get(key);
        return value == "true" || value == "1";
    }
    
    // 显示所有配置
    static void showAll() {
        if (!isLoaded) {
            loadConfig();
        }
        
        std::cout << "\n=== 当前配置 ===" << std::endl;
        for (const auto& pair : config) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
    }
    
    // 保存配置（模拟）
    static bool save() {
        std::cout << "配置已保存" << std::endl;
        return true;
    }
};

// 静态成员初始化
std::map<std::string, std::string> ConfigManager::config;
bool ConfigManager::isLoaded = false;

int main() {
    // 无需创建对象即可使用
    std::string server = ConfigManager::get("server");
    int port = ConfigManager::getInt("port");
    bool debug = ConfigManager::getBool("debug");
    
    std::cout << "服务器: " << server << ":" << port << std::endl;
    std::cout << "调试模式: " << (debug ? "是" : "否") << std::endl;
    
    // 修改配置
    ConfigManager::set("port", "9090");
    ConfigManager::set("debug", "true");
    
    // 显示所有配置
    ConfigManager::showAll();
    
    // 保存配置
    ConfigManager::save();
    
    return 0;
}
```

## 六、静态成员在继承中的特性

```cpp
class Base {
public:
    static int count;
    static void showCount() {
        std::cout << "Base count: " << count << std::endl;
    }
};

int Base::count = 0;

class Derived1 : public Base {
public:
    // 继承静态成员
    // 可以访问Base::count
};

class Derived2 : public Base {
public:
    // 也可以有自己的静态成员
    static int derivedCount;
    static void showAll() {
        std::cout << "Base count: " << Base::count << std::endl;
        std::cout << "Derived2 count: " << derivedCount << std::endl;
    }
};

int Derived2::derivedCount = 0;

int main() {
    Base::count = 10;
    Derived1::count = 20;  // 修改的是同一个Base::count
    Derived2::count = 30;  // 修改的还是同一个Base::count
    
    Base::showCount();  // 输出: 30
    
    Derived2::derivedCount = 100;
    Derived2::showAll();
    // 输出:
    // Base count: 30
    // Derived2 count: 100
    
    return 0;
}
```

## 七、静态局部变量

```cpp
class Student {
private:
    std::string name;
    
public:
    Student(const std::string& n) : name(n) {}
    
    // 每次调用生成唯一的学号
    static int generateStudentId() {
        static int nextId = 1001;  // 静态局部变量
        return nextId++;
    }
    
    // 生成多个序列
    static int generateClassId() {
        static int classId = 1;
        return classId++;
    }
    
    static int generateRandomId() {
        static bool initialized = false;
        static int seed;
        
        if (!initialized) {
            seed = time(nullptr);  // 只初始化一次
            initialized = true;
        }
        
        // 伪随机数
        seed = seed * 1103515245 + 12345;
        return (seed / 65536) % 32768;
    }
};

void testStaticLocal() {
    // 静态局部变量在函数第一次调用时初始化
    // 之后调用会保持之前的值
    
    auto counter =  {
        static int count = 0;  // 只初始化一次
        return ++count;
    };
    
    std::cout << "第一次: " << counter() << std::endl;  // 1
    std::cout << "第二次: " << counter() << std::endl;  // 2
    std::cout << "第三次: " << counter() << std::endl;  // 3
}

int main() {
    std::cout << "学生ID序列:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << Student::generateStudentId() << " ";
    }
    std::cout << std::endl;  // 1001 1002 1003 1004 1005
    
    std::cout << "\n班级ID序列:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << Student::generateClassId() << " ";
    }
    std::cout << std::endl;  // 1 2 3
    
    testStaticLocal();
    
    return 0;
}
```


## 八、常见错误

```cpp
class CommonMistakes {
private:
    int normalVar;
    static int staticVar;
    
public:
    // 错误1：在类内初始化非const静态成员
    // static int count = 0;  // 错误！(C++17前)
    
    // 正确：使用constexpr (C++17)
    static constexpr int MAX_SIZE = 100;  // ✓
    
    // 错误2：静态函数访问非静态成员
    static void staticFunc() {
        // normalVar = 10;  // 错误！
    }
    
    // 错误3：忘记定义静态成员
    // static int undefinedVar;  // 需要在类外定义
    
    // 错误4：静态成员函数是虚函数
    // virtual static void func() {}  // 错误！
    
    // 错误5：静态成员函数有const修饰符
    // static void func() const {}  // 错误！
};

// 必须在类外定义
int CommonMistakes::staticVar = 0;  // ✓
```

## 九、总结

### **静态成员变量特点**：
1. 属于类，不属于任何对象
2. 所有对象共享同一份副本
3. 在程序开始时初始化
4. 需要在类外单独定义（除const整数类型）

### **静态成员函数特点**：
1. 只能访问静态成员
2. 没有this指针
3. 不能是虚函数
4. 不能是const函数
5. 可以通过类名或对象调用

### **使用场景**：
1. 记录类的全局信息（如对象计数）
2. 工具函数（如数学计算）
3. 工厂方法
4. 单例模式
5. 配置管理
6. 常量定义

### **最佳实践**：
1. 使用`static`关键字声明
2. 在类外定义和初始化静态变量
3. 通过类名访问静态成员
4. 考虑线程安全性
5. 合理使用静态常量

### **记忆口诀**：
```
静态成员属于类，所有对象共享它
静态变量类外定，静态函数无this
只能访问静态的，常量可在类内赋
工具单例常用到，全局数据要慎用
```