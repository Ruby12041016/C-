# 字符串与基本I/O

## 第一部分：深入理解字符串

### 一、C++字符串 vs C风格字符串

**重要区别：**

| 特性 | C风格字符串 (char数组) | C++字符串 (std::string) |
|------|---------------------|----------------------|
| 头文件 | `<cstring>` | `<string>` |
| 安全性 | 容易溢出，不安全 | 自动管理内存，安全 |
| 长度获取 | `strlen()` 函数 | `.length()` 或 `.size()` 方法 |
| 复制 | `strcpy()` | `=` 赋值运算符 |
| 连接 | `strcat()` | `+` 或 `+=` 运算符 |
| 比较 | `strcmp()` | `==`, `!=`, `<`, `>` 等运算符 |
| 内存管理 | 手动管理 | 自动管理 |

### 二、C++ string类详解

#### 1. 创建和初始化字符串

```cpp
#include <iostream>
#include <string>  // 必须包含这个头文件
using namespace std;

int main() {
    // 多种初始化方式
    string str1;                     // 空字符串
    string str2 = "Hello";           // 从C字符串初始化
    string str3("World");            // 构造函数
    string str4(5, 'A');             // "AAAAA" - 5个'A'
    string str5 = str2;              // 拷贝构造
    string str6(str2, 1, 3);         // 子串："ell"（从位置1开始，取3个字符）
    string str7(str2.begin(), str2.begin() + 3);  // "Hel"（迭代器范围）
    
    // 检查字符串是否为空
    if (str1.empty()) {
        cout << "str1是空字符串" << endl;
    }
    
    return 0;
}
```

#### 2. 字符串操作详解

**长度和容量：**
```cpp
string s = "Hello World";

// 获取长度/大小
int len1 = s.length();    // 11
int len2 = s.size();      // 11，与length()相同
int max_size = s.max_size();  // 最大可能长度
int capacity = s.capacity();   // 当前分配的容量（>=长度）

// 改变容量
s.reserve(100);  // 预留至少100字符的空间
s.shrink_to_fit();  // 减少容量以匹配大小（C++11）

cout << "长度: " << s.length() << endl;
cout << "容量: " << s.capacity() << endl;
```

**访问字符：**
```cpp
string s = "Hello";

// 多种访问方式
char c1 = s[0];          // 'H'，不检查边界
char c2 = s.at(0);       // 'H'，检查边界，越界会抛出异常
char c3 = s.front();     // 'H'，第一个字符（C++11）
char c4 = s.back();      // 'o'，最后一个字符（C++11）

// 修改字符
s[0] = 'h';              // 改为小写
s.at(1) = 'E';           // 改为大写

// 遍历字符串
for (int i = 0; i < s.length(); i++) {
    cout << s[i] << " ";
}
cout << endl;

for (char ch : s) {      // 范围for循环
    cout << ch << " ";
}
cout << endl;
```

**修改字符串内容：**

```cpp
string s = "Hello";

// 1. 追加
s.append(" World");      // "Hello World"
s += "!";                // "Hello World!"
s.push_back('!');        // "Hello World!!"
s.append(3, '!');        // 追加3个'!'："Hello World!!!!!"

// 2. 插入
s.insert(5, " C++");     // 在位置5插入："Hello C++ World!!!!!"

// 3. 删除
s.erase(5, 4);           // 从位置5删除4个字符："Hello World!!!!!"
s.pop_back();            // 删除最后一个字符："Hello World!!!!"
s.clear();               // 清空字符串：""

// 4. 替换
s = "Hello World";
s.replace(6, 5, "C++");  // 从位置6开始替换5个字符："Hello C++"

// 5. 交换
string a = "Hello";
string b = "World";
a.swap(b);  // 或 swap(a, b);
// 现在 a = "World", b = "Hello"
```

**查找和子串：**

```cpp
string s = "Hello World, Hello C++";

// 1. 查找
size_t pos1 = s.find("Hello");     // 0
size_t pos2 = s.find("Hello", 1);  // 从位置1开始找：13
size_t pos3 = s.find("Python");    // string::npos（表示未找到）

// 2. 反向查找
size_t rpos = s.rfind("Hello");    // 从后往前找：13

// 3. 查找字符集中的任意字符
size_t pos4 = s.find_first_of("aeiou");  // 找到第一个元音：1（e）
size_t pos5 = s.find_last_of("aeiou");   // 找到最后一个元音：20（+）

// 4. 获取子串
string sub1 = s.substr(6);        // 从位置6到结尾："World, Hello C++"
string sub2 = s.substr(6, 5);     // 从位置6开始，取5个字符："World"

// 5. 判断是否包含
if (s.find("World") != string::npos) {
    cout << "包含'World'" << endl;
}
```

**字符串比较：**

```cpp
string s1 = "apple";
string s2 = "banana";
string s3 = "Apple";  // 注意大写A
string s4 = "apple";

// 1. 使用比较运算符
if (s1 == s4) {  // true
    cout << "s1等于s4" << endl;
}
if (s1 != s2) {  // true
    cout << "s1不等于s2" << endl;
}
if (s1 < s2) {   // true，因为'a' < 'b'
    cout << "s1小于s2" << endl;
}

// 2. 使用compare方法
int result = s1.compare(s2);
if (result == 0) {
    cout << "相等" << endl;
} else if (result < 0) {
    cout << "s1 < s2" << endl;  // 会执行这个
} else {
    cout << "s1 > s2" << endl;
}

// 3. 比较子串
string s5 = "Hello World";
if (s5.compare(6, 5, "World") == 0) {  // 从位置6开始比较5个字符
    cout << "子串匹配" << endl;
}

// 4. 大小写敏感比较
if (s1 == s3) {  // false，因为大小写不同
    cout << "大小写不同" << endl;
}
```

**字符串转换：**

```cpp
#include <string>
#include <sstream>  // 字符串流
#include <cstdlib>  // 用于C风格转换

// 1. 数字转字符串
int num = 123;
double pi = 3.14159;

// 方法1：使用to_string（C++11）
string s1 = to_string(num);  // "123"
string s2 = to_string(pi);   // "3.141590"

// 方法2：使用字符串流
stringstream ss;
ss << num << " " << pi;
string s3 = ss.str();  // "123 3.14159"

// 2. 字符串转数字
string str_num = "123";
string str_float = "3.1415";

// 方法1：使用stoi, stol, stof, stod（C++11）
int n1 = stoi(str_num);      // 123
double d1 = stod(str_float); // 3.1415

// 方法2：使用字符串流
stringstream ss2("456 7.89");
int n2;
double d2;
ss2 >> n2 >> d2;  // n2=456, d2=7.89

// 方法3：C风格函数（不推荐）
int n3 = atoi(str_num.c_str());  // 需要c_str()
```

**字符串与字符数组转换：**

```cpp
string s = "Hello";

// 1. string转C风格字符串
const char* cstr = s.c_str();  // 返回const char*
cout << cstr << endl;          // "Hello"

// 2. 复制到字符数组
char buffer[20];
s.copy(buffer, 5, 0);  // 从位置0复制5个字符
buffer[5] = '\0';      // 手动添加结束符
cout << buffer << endl;  // "Hello"

// 3. 从C风格字符串创建
const char* cstr2 = "World";
string s2(cstr2);  // "World"
```

**字符串流（stringstream）：**

```cpp
#include <sstream>

// 1. 格式化字符串
stringstream ss;
ss << "Name: " << "John" << ", Age: " << 25;
string info = ss.str();  // "Name: John, Age: 25"
cout << info << endl;

// 2. 字符串分割
string data = "apple,banana,orange";
stringstream ss2(data);
string fruit;
while (getline(ss2, fruit, ',')) {  // 以逗号分割
    cout << fruit << endl;
}
// 输出：
// apple
// banana
// orange

// 3. 类型转换
string num_str = "123 45.6";
stringstream ss3(num_str);
int n;
double d;
ss3 >> n >> d;  // n=123, d=45.6
```

---

## 第二部分：基本输入输出（I/O）

### 一、标准输入输出流

#### 1. cout 详解

**基本输出：**
```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 25;
    double salary = 4500.50;
    string name = "Alice";
    
    // 1. 基本输出
    cout << "Hello World!" << endl;
    
    // 2. 输出多个值
    cout << "Name: " << name << ", Age: " << age << endl;
    
    // 3. 格式化输出
    cout << "Salary: $" << salary << endl;
    
    return 0;
}
```

**格式化输出：**
```cpp
#include <iostream>
#include <iomanip>  // 格式化输出需要的头文件
using namespace std;

int main() {
    double pi = 3.141592653589793;
    int num = 255;
    
    // 1. 设置小数位数
    cout << fixed << setprecision(2);  // 固定小数点，保留2位
    cout << "Pi: " << pi << endl;       // 3.14
    
    cout << scientific << setprecision(6);  // 科学计数法，保留6位
    cout << "Pi scientific: " << pi << endl;  // 3.141593e+00
    
    // 2. 设置宽度和对齐
    cout << left << setw(10) << "Name" << setw(10) << "Age" << endl;
    cout << left << setw(10) << "Alice" << setw(10) << 25 << endl;
    cout << left << setw(10) << "Bob" << setw(10) << 30 << endl;
    
    // 3. 填充字符
    cout << setfill('*') << setw(20) << "Hello" << endl;
    // 输出：***************Hello
    
    // 4. 进制转换
    cout << dec << num << endl;   // 十进制: 255
    cout << hex << num << endl;   // 十六进制: ff
    cout << oct << num << endl;   // 八进制: 377
    
    // 5. 布尔值格式
    bool flag = true;
    cout << boolalpha << flag << endl;   // true
    cout << noboolalpha << flag << endl; // 1
    
    return 0;
}
```

#### 2. cin 详解

**基本输入：**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int age;
    double salary;
    string name;
    
    // 1. 单个输入
    cout << "请输入年龄: ";
    cin >> age;
    
    // 2. 多个输入
    cout << "请输入姓名和工资: ";
    cin >> name >> salary;  // 空格分隔
    
    cout << "姓名: " << name << ", 年龄: " << age << ", 工资: " << salary << endl;
    
    return 0;
}
```

**cin的问题和解决方案：**

**问题1：输入包含空格**
```cpp
string fullName;
cout << "请输入全名: ";
cin >> fullName;  // 如果输入"John Smith"，只会读取"John"
cout << "你输入的是: " << fullName << endl;  // 只输出"John"
```

**解决方案：使用getline**
```cpp
string fullName;
cout << "请输入全名: ";
getline(cin, fullName);  // 读取整行
cout << "你输入的是: " << fullName << endl;  // 输出"John Smith"
```

**问题2：混合使用cin和getline**
```cpp
int age;
string name;
cout << "请输入年龄: ";
cin >> age;
cout << "请输入姓名: ";
getline(cin, name);  // 问题：会直接读取换行符，不等待输入
cout << "年龄: " << age << ", 姓名: " << name << endl;
```

**解决方案：清除输入缓冲区**
```cpp
int age;
string name;
cout << "请输入年龄: ";
cin >> age;
cin.ignore(1000, '\n');  // 忽略换行符之前的所有字符
cout << "请输入姓名: ";
getline(cin, name);
cout << "年龄: " << age << ", 姓名: " << name << endl;
```

**问题3：输入类型不匹配**
```cpp
int number;
cout << "请输入一个数字: ";
cin >> number;  // 如果输入"abc"，会失败
if (cin.fail()) {
    cout << "输入错误！" << endl;
    cin.clear();  // 清除错误状态
    cin.ignore(1000, '\n');  // 清除错误输入
}
```

**完整的输入验证：**
```cpp
int getValidInt() {
    int value;
    while (true) {
        cout << "请输入一个整数: ";
        cin >> value;
        
        if (cin.fail()) {  // 输入失败
            cout << "输入错误，请重新输入！" << endl;
            cin.clear();  // 清除错误状态
            cin.ignore(1000, '\n');  // 清除错误输入
        } else {
            cin.ignore(1000, '\n');  // 清除换行符
            return value;
        }
    }
}
```

#### 3. 文件输入输出

**文件写入：**
```cpp
#include <iostream>
#include <fstream>  // 文件流头文件
using namespace std;

int main() {
    // 1. 创建输出文件流
    ofstream outFile;
    
    // 2. 打开文件
    outFile.open("data.txt");
    
    // 3. 检查是否成功打开
    if (!outFile.is_open()) {
        cout << "无法打开文件！" << endl;
        return 1;
    }
    
    // 4. 写入数据
    outFile << "学生信息" << endl;
    outFile << "姓名: 张三" << endl;
    outFile << "年龄: 20" << endl;
    outFile << "成绩: 95.5" << endl;
    
    // 5. 关闭文件
    outFile.close();
    cout << "数据已写入文件" << endl;
    
    return 0;
}
```

**文件读取：**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // 1. 创建输入文件流
    ifstream inFile;
    
    // 2. 打开文件
    inFile.open("data.txt");
    
    // 3. 检查是否成功打开
    if (!inFile.is_open()) {
        cout << "无法打开文件！" << endl;
        return 1;
    }
    
    // 4. 读取数据
    string line;
    while (getline(inFile, line)) {  // 逐行读取
        cout << line << endl;
    }
    
    // 5. 检查是否读到文件末尾
    if (inFile.eof()) {
        cout << "已读取到文件末尾" << endl;
    }
    
    // 6. 关闭文件
    inFile.close();
    
    return 0;
}
```

**更复杂的文件操作：**
```cpp
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    // 写入数据
    ofstream outFile("students.txt");
    
    outFile << left << setw(10) << "姓名" 
            << setw(10) << "年龄" 
            << setw(10) << "成绩" << endl;
    outFile << string(30, '-') << endl;
    
    outFile << left << setw(10) << "张三" 
            << setw(10) << 20 
            << fixed << setprecision(2) << 95.5 << endl;
    outFile << left << setw(10) << "李四" 
            << setw(10) << 21 
            << fixed << setprecision(2) << 88.0 << endl;
    
    outFile.close();
    
    // 读取并处理数据
    ifstream inFile("students.txt");
    string header1, header2, header3;
    string line;
    
    // 读取表头
    getline(inFile, line);  // 读取标题行
    getline(inFile, line);  // 读取分隔线
    
    // 读取数据
    string name;
    int age;
    double score;
    double totalScore = 0;
    int count = 0;
    
    while (inFile >> name >> age >> score) {
        totalScore += score;
        count++;
        cout << "学生: " << name << ", 年龄: " << age << ", 成绩: " << score << endl;
    }
    
    if (count > 0) {
        cout << "平均成绩: " << totalScore / count << endl;
    }
    
    inFile.close();
    
    return 0;
}
```

#### 4. 字符串流（stringstream）应用

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // 1. 解析CSV数据
    string csvData = "张三,20,95.5\n李四,21,88.0\n王五,19,92.5";
    stringstream ss(csvData);
    string line;
    
    cout << "解析CSV数据：" << endl;
    while (getline(ss, line)) {
        stringstream lineStream(line);
        string name, ageStr, scoreStr;
        
        getline(lineStream, name, ',');
        getline(lineStream, ageStr, ',');
        getline(lineStream, scoreStr, ',');
        
        int age = stoi(ageStr);
        double score = stod(scoreStr);
        
        cout << "姓名: " << name 
             << ", 年龄: " << age 
             << ", 成绩: " << score << endl;
    }
    
    // 2. 构建字符串
    stringstream ss2;
    ss2 << "计算结果:" << endl;
    ss2 << "总和: " << (10 + 20) << endl;
    ss2 << "平均值: " << ((10 + 20) / 2.0) << endl;
    
    cout << "\n构建的字符串：" << endl;
    cout << ss2.str() << endl;
    
    // 3. 类型转换
    string intStr = "123";
    string doubleStr = "45.67";
    
    stringstream ss3;
    ss3 << intStr << " " << doubleStr;
    
    int num1;
    double num2;
    ss3 >> num1 >> num2;
    
    cout << "\n转换结果：" << endl;
    cout << "整数: " << num1 << endl;
    cout << "浮点数: " << num2 << endl;
    
    return 0;
}
```

---

## 常见错误与调试技巧

### 字符串常见错误

**错误1：字符串索引越界**
```cpp
string s = "hello";
// cout << s[10];  // 运行时错误！
cout << s.at(10);  // 抛出std::out_of_range异常
```

**错误2：忘记初始化**
```cpp
string s;  // 空字符串
cout << s[0];  // 未定义行为！
```

**错误3：内存问题**
```cpp
// C风格字符串的常见错误
char str[10];
strcpy(str, "这个字符串太长了");  // 缓冲区溢出！

// 正确做法
strncpy(str, "这个字符串太长了", sizeof(str)-1);
str[sizeof(str)-1] = '\0';
```

### 输入输出调试技巧

**技巧1：使用cerr输出调试信息**
```cpp
cerr << "调试信息: 变量值 = " << value << endl;
// cerr不缓冲，立即输出，适合调试
```

**技巧2：检查流状态**
```cpp
cin >> value;
if (cin.fail()) {
    cerr << "输入错误！" << endl;
    cin.clear();
    cin.ignore(1000, '\n');
}
```

**技巧3：使用条件编译调试**
```cpp
#define DEBUG 1

#ifdef DEBUG
    cout << "调试: 进入函数foo()" << endl;
#endif
```

---



