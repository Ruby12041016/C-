# try-catch 详解（适合初学者）

## 一、try-catch 基本语法

```cpp
#include <iostream>
#include <stdexcept>

void basicExample() {
    try {
        // 可能抛出异常的代码
        std::cout << "尝试执行代码..." << std::endl;
        throw std::runtime_error("这是一个异常！");
        std::cout << "这行代码不会执行" << std::endl;
    } 
    catch (const std::exception& e) {
        // 捕获异常并处理
        std::cout << "捕获到异常: " << e.what() << std::endl;
    }
    
    std::cout << "程序继续执行..." << std::endl;
}
```

## 二、完整的 try-catch 结构

```cpp
#include <iostream>
#include <stdexcept>

void completeStructure() {
    std::cout << "程序开始" << std::endl;
    
    try {
        // 代码块：可能抛出异常
        std::cout << "在 try 块中..." << std::endl;
        
        int choice = 2;  // 尝试改变这个值看看效果
        
        if (choice == 1) {
            throw std::runtime_error("运行时错误！");
        } 
        else if (choice == 2) {
            throw std::logic_error("逻辑错误！");
        } 
        else if (choice == 3) {
            throw 42;  // 抛出整数
        } 
        else if (choice == 4) {
            throw "字符串异常";  // 抛出字符串
        }
        
        std::cout << "try 块正常结束" << std::endl;
    }
    catch (const std::runtime_error& e) {
        // 捕获 runtime_error
        std::cout << "捕获 runtime_error: " << e.what() << std::endl;
    }
    catch (const std::logic_error& e) {
        // 捕获 logic_error
        std::cout << "捕获 logic_error: " << e.what() << std::endl;
    }
    catch (int errorCode) {
        // 捕获整数异常
        std::cout << "捕获整数异常: " << errorCode << std::endl;
    }
    catch (const char* errorMessage) {
        // 捕获字符串异常
        std::cout << "捕获字符串异常: " << errorMessage << std::endl;
    }
    catch (...) {
        // 捕获所有其他异常
        std::cout << "捕获未知异常" << std::endl;
    }
    
    std::cout << "程序继续执行..." << std::endl;
}
```

## 三、标准库异常类型

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

void standardExceptions() {
    try {
        int choice = 1;  // 改变这个值测试不同异常
        
        switch (choice) {
            case 1:  // logic_error
                throw std::logic_error("逻辑错误");
                
            case 2:  // invalid_argument
                throw std::invalid_argument("无效参数");
                
            case 3:  // out_of_range
                std::vector<int> vec = {1, 2, 3};
                int x = vec.at(10);  // 抛出 out_of_range
                break;
                
            case 4:  // length_error
                std::string str;
                str.resize(str.max_size() + 1);  // 抛出 length_error
                break;
                
            case 5:  // runtime_error
                throw std::runtime_error("运行时错误");
                
            case 6:  // overflow_error
                throw std::overflow_error("溢出错误");
                
            case 7:  // underflow_error
                throw std::underflow_error("下溢错误");
                
            case 8:  // range_error
                throw std::range_error("范围错误");
        }
    }
    catch (const std::logic_error& e) {
        // logic_error 及其子类
        std::cout << "逻辑错误: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        // runtime_error 及其子类
        std::cout << "运行时错误: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // 所有标准异常
        std::cout << "标准异常: " << e.what() << std::endl;
    }
    catch (...) {
        // 其他所有异常
        std::cout << "未知异常" << std::endl;
    }
}
```

## 四、嵌套的 try-catch

```cpp
#include <iostream>
#include <stdexcept>

void outerFunction() {
    try {
        std::cout << "外层函数开始" << std::endl;
        
        try {
            std::cout << "内层 try 块开始" << std::endl;
            throw std::runtime_error("内层异常");
            std::cout << "这行不会执行" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "内层捕获: " << e.what() << std::endl;
            // 可以选择重新抛出
            throw;  // 重新抛出给外层
        }
        
        std::cout << "外层 try 块继续" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "外层捕获: " << e.what() << std::endl;
    }
}

void testNested() {
    outerFunction();
    std::cout << "测试完成" << std::endl;
}
```

## 五、函数中的异常传播

```cpp
#include <iostream>
#include <stdexcept>

// 函数可能抛出异常
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("除数不能为零");
    }
    return a / b;
}

// 调用可能抛出异常的函数
void calculate() {
    int x = 10, y = 0;
    
    try {
        int result = divide(x, y);
        std::cout << "结果: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "calculate 函数中捕获: " << e.what() << std::endl;
        // 可以重新抛出
        throw;  // 继续向上传播
    }
}

void testPropagation() {
    try {
        calculate();
    }
    catch (const std::exception& e) {
        std::cout << "testPropagation 中捕获: " << e.what() << std::endl;
    }
    
    std::cout << "程序继续..." << std::endl;
}
```

## 六、实际应用示例

### 1. **文件操作**

```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void readFile(const std::string& filename) {
    try {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("无法打开文件: " + filename);
        }
        
        std::string line;
        int lineCount = 0;
        
        while (std::getline(file, line)) {
            lineCount++;
            std::cout << "第 " << lineCount << " 行: " << line << std::endl;
            
            if (lineCount > 100) {
                throw std::runtime_error("文件行数过多");
            }
        }
        
        if (file.bad()) {
            throw std::runtime_error("读取文件时发生错误");
        }
        
        file.close();
        std::cout << "成功读取 " << lineCount << " 行" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "文件操作错误: " << e.what() << std::endl;
        throw;  // 重新抛出
    }
}

void testFileOperation() {
    try {
        readFile("test.txt");
    }
    catch (const std::exception& e) {
        std::cout << "主程序捕获: " << e.what() << std::endl;
        
        // 尝试备份文件
        try {
            std::cout << "尝试读取备份文件..." << std::endl;
            readFile("backup.txt");
        }
        catch (...) {
            std::cout << "备份文件也读取失败" << std::endl;
        }
    }
}
```

### 2. **网络请求模拟**

```cpp
#include <iostream>
#include <stdexcept>
#include <random>
#include <chrono>
#include <thread>

class NetworkException : public std::runtime_error {
public:
    NetworkException(const std::string& msg) : std::runtime_error(msg) {}
};

std::string makeRequest(const std::string& url) {
    // 模拟网络延迟
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // 模拟随机错误
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    
    int random = dis(gen);
    
    if (random <= 3) {  // 30% 概率超时
        throw NetworkException("请求超时: " + url);
    } 
    else if (random <= 5) {  // 20% 概率服务器错误
        throw std::runtime_error("服务器内部错误");
    } 
    else if (random <= 6) {  // 10% 概率无效响应
        throw "无效响应";
    }
    
    return "来自 " + url + " 的响应数据";
}

void testNetwork() {
    std::string url = "https://api.example.com/data";
    
    for (int attempt = 1; attempt <= 3; attempt++) {
        try {
            std::cout << "第 " << attempt << " 次尝试..." << std::endl;
            std::string response = makeRequest(url);
            std::cout << "成功: " << response << std::endl;
            return;  // 成功，退出
        }
        catch (const NetworkException& e) {
            std::cout << "网络异常: " << e.what() << std::endl;
            
            if (attempt < 3) {
                std::cout << "等待 " << attempt << " 秒后重试..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(attempt));
            }
        }
        catch (const std::runtime_error& e) {
            std::cout << "运行时错误: " << e.what() << std::endl;
            break;  // 服务器错误，不重试
        }
        catch (const char* msg) {
            std::cout << "错误消息: " << msg << std::endl;
            break;  // 无效响应，不重试
        }
        catch (...) {
            std::cout << "未知网络错误" << std::endl;
            break;
        }
    }
    
    std::cout << "所有重试失败" << std::endl;
}
```

### 3. **数据库操作模拟**

```cpp
#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>

class DatabaseConnection {
private:
    std::string connectionString;
    bool isConnected = false;
    
public:
    DatabaseConnection(const std::string& connStr) 
        : connectionString(connStr) {
        std::cout << "创建数据库连接: " << connStr << std::endl;
    }
    
    void connect() {
        if (connectionString.empty()) {
            throw std::runtime_error("连接字符串为空");
        }
        
        if (connectionString.find("error") != std::string::npos) {
            throw std::runtime_error("连接失败: 无效的连接字符串");
        }
        
        isConnected = true;
        std::cout << "数据库连接成功" << std::endl;
    }
    
    void executeQuery(const std::string& query) {
        if (!isConnected) {
            throw std::runtime_error("数据库未连接");
        }
        
        if (query.empty()) {
            throw std::invalid_argument("查询语句为空");
        }
        
        if (query.find("DROP") != std::string::npos) {
            throw std::runtime_error("危险操作: 不允许 DROP 语句");
        }
        
        std::cout << "执行查询: " << query << std::endl;
        
        if (query.find("error") != std::string::npos) {
            throw std::runtime_error("查询执行失败");
        }
        
        std::cout << "查询成功" << std::endl;
    }
    
    void disconnect() {
        if (isConnected) {
            std::cout << "断开数据库连接" << std::endl;
            isConnected = false;
        }
    }
    
    ~DatabaseConnection() {
        disconnect();
    }
};

void testDatabase() {
    try {
        DatabaseConnection db("server=localhost;database=mydb");
        
        try {
            db.connect();
            
            try {
                db.executeQuery("SELECT * FROM users");
                db.executeQuery("UPDATE users SET name='John' WHERE id=1");
                // db.executeQuery("DROP TABLE users");  // 这会抛出异常
                // db.executeQuery("");  // 这也会抛出异常
            }
            catch (const std::exception& e) {
                std::cout << "查询错误: " << e.what() << std::endl;
                throw;  // 向上传播
            }
        }
        catch (const std::exception& e) {
            std::cout << "连接错误: " << e.what() << std::endl;
            throw;  // 向上传播
        }
    }
    catch (const std::exception& e) {
        std::cout << "数据库操作失败: " << e.what() << std::endl;
    }
    
    std::cout << "数据库测试完成" << std::endl;
}
```

## 七、异常安全保证

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

// 异常安全的类
class ExceptionSafe {
private:
    std::unique_ptr<int[]> data;
    int size;
    
public:
    ExceptionSafe(int n) : size(n) {
        data = std::make_unique<int[]>(size);
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }
    
    // 异常安全的操作
    void safeOperation(int newValue) {
        // 先创建新资源
        auto newData = std::make_unique<int[]>(size);
        
        // 复制数据
        for (int i = 0; i < size; i++) {
            newData[i] = data[i] + newValue;
            
            // 模拟可能失败的操作
            if (newData[i] > 1000) {
                throw std::runtime_error("值过大");
            }
        }
        
        // 所有操作成功后才更新状态
        data = std::move(newData);
    }
    
    // 不安全的操作
    void unsafeOperation(int newValue) {
        for (int i = 0; i < size; i++) {
            data[i] += newValue;
            
            // 如果这里抛出异常，对象状态会被破坏
            if (data[i] > 1000) {
                throw std::runtime_error("值过大");
            }
        }
    }
    
    void display() {
        std::cout << "数据: ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

void testExceptionSafety() {
    ExceptionSafe obj(5);
    
    std::cout << "初始状态: ";
    obj.display();
    
    try {
        obj.safeOperation(100);
        std::cout << "safeOperation 后: ";
        obj.display();
        
        obj.unsafeOperation(1000);  // 这会抛出异常
    }
    catch (const std::exception& e) {
        std::cout << "异常: " << e.what() << std::endl;
        std::cout << "当前状态: ";
        obj.display();  // safeOperation 的状态是完整的
    }
}
```

## 八、finally 的模拟（C++没有finally）

```cpp
#include <iostream>
#include <memory>

// 使用RAII模拟finally
class Finally {
private:
    std::function<void()> cleanup;
    
public:
    Finally(std::function<void()> f) : cleanup(f) {}
    
    ~Finally() {
        if (cleanup) {
            cleanup();
        }
    }
    
    // 禁止拷贝
    Finally(const Finally&) = delete;
    Finally& operator=(const Finally&) = delete;
    
    // 允许移动
    Finally(Finally&&) = default;
    Finally& operator=(Finally&&) = default;
};

void testFinally() {
    try {
        std::cout << "打开资源..." << std::endl;
        
        Finally cleanup( {
            std::cout << "清理资源（无论是否异常）" << std::endl;
        });
        
        // 业务逻辑
        int x = 0;
        std::cout << "输入一个数字: ";
        // std::cin >> x;  // 实际使用时
        
        if (x < 0) {
            throw std::runtime_error("负数无效");
        }
        
        std::cout << "处理完成: " << x << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "异常: " << e.what() << std::endl;
    }
    
    // cleanup 在离开作用域时自动调用
}
```

## 九、常见错误和调试技巧

### 1. **常见错误**

```cpp
#include <iostream>
#include <stdexcept>

void commonMistakes() {
    // 错误1：捕获异常但不处理
    try {
        throw std::runtime_error("错误");
    } 
    catch (...) {
        // 错误：什么都没做！
    }
    
    // 错误2：不完整的异常信息
    try {
        int x = 0, y = 0;
        if (y == 0) {
            throw std::runtime_error("除零错误");  // 不好：没有足够信息
            // 应该：throw std::runtime_error("除零错误: " + std::to_string(x) + "/" + std::to_string(y));
        }
    }
    catch (...) {}
    
    // 错误3：异常中抛出异常
    try {
        try {
            throw std::runtime_error("第一个异常");
        }
        catch (...) {
            // 清理...
            throw std::runtime_error("第二个异常");  // 丢失了第一个异常的信息
        }
    }
    catch (const std::exception& e) {
        std::cout << "只看到: " << e.what() << std::endl;  // 只看到第二个异常
    }
    
    // 正确做法：使用 throw; 重新抛出原异常
}
```

### 2. **调试技巧**

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

// 带调试信息的异常
class DebugException : public std::exception {
private:
    std::string message;
    std::string file;
    int line;
    std::string function;
    
public:
    DebugException(const std::string& msg, 
                   const std::string& f, 
                   int l, 
                   const std::string& func)
        : message(msg), file(f), line(l), function(func) {}
    
    const char* what() const noexcept override {
        static std::string fullMessage;
        fullMessage = message + 
                     "\n  位置: " + function +
                     "\n  文件: " + file + 
                     ":" + std::to_string(line);
        return fullMessage.c_str();
    }
};

// 调试宏
#define THROW_DEBUG(msg) \
    throw DebugException(msg, __FILE__, __LINE__, __FUNCTION__)

void testDebug() {
    try {
        int x = 0;
        if (x == 0) {
            THROW_DEBUG("x 不能为零");
        }
    }
    catch (const DebugException& e) {
        std::cout << "调试异常:\n" << e.what() << std::endl;
    }
}
```

## 总结

### **try-catch 核心语法**：
```cpp
try {
    // 可能抛出异常的代码
    throw SomeException("错误信息");
}
catch (const SpecificException& e) {
    // 处理特定异常
}
catch (const BaseException& e) {
    // 处理基类异常
}
catch (...) {
    // 处理所有其他异常
}
```

### **关键要点**：
1. **try 块**：包含可能抛出异常的代码
2. **catch 块**：捕获并处理异常
3. **异常类型**：可以捕获特定类型的异常
4. **catch(...)**：捕获所有异常
5. **throw**：抛出异常
6. **throw;**：重新抛出当前异常

### **最佳实践**：
1. 按从具体到一般的顺序捕获异常
2. 在catch块中处理异常，不要忽略
3. 使用RAII管理资源
4. 提供有意义的异常信息
5. 考虑异常安全性
6. 避免在析构函数中抛出异常

### **常见用途**：
1. 文件I/O错误处理
2. 网络通信错误
3. 用户输入验证
4. 资源分配失败
5. 数值计算错误
6. 数据库操作异常

### **记忆口诀**：
```
try-catch 要配对，异常处理不崩溃
try 中放危险代码，catch 来捕获异常
先捕具体后一般，catch(...) 放最后
资源管理用RAII，异常安全要考虑
抛出异常用 throw，重新抛出 throw;
提供有用错误信息，调试维护更容易
```