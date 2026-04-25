#include <cctype>    // 包含字符处理函数，如isdigit
#include <iostream>  
#include <string>    
using namespace std;
typedef long long ll;  

bool isNumber(const string& s) {
    for (char c : s)       
        if (!isdigit(c))   // 如果发现非数字字符
            return false;  // 返回false
    return !s.empty();     // 确保字符串非空
}

int main() {
    int T;                        
    cin >> T;                     
    cin.ignore();                 // 忽略输入T后的换行符，避免影响getline读取
    while (T--) {                
        string s;                 // 存储输入的表达式字符串
        getline(cin, s);          // 读取整行字符串
        int xPos = s.find('x');   // 查找第一个'x'的位置
        int eqPos = s.find('=');  // 查找'='的位置

        // 检查是否只有一个'x'
        if (s.find('x', xPos + 1) != string::npos) {
            cout << "FormatError\n";  // 多个'x'，格式错误
            continue;
        }

        // 格式检查：确保字符串包含'x'和'='，且'x'不在开头，'='不在结尾，'x'在'='之前
        if (xPos == string::npos || eqPos == string::npos || xPos == 0 ||
            eqPos == s.length() - 1 || xPos > eqPos) {
            cout << "FormatError\n";  
            continue;                 
        }

        // 分割字符串为三个部分：A、B、C
        string A_str = s.substr(0, xPos);  // 提取A部分（'x'之前的字符串）
        string B_str = s.substr(
            xPos + 1, eqPos - xPos - 1);  // 提取B部分（'x'和'='之间的字符串）
        string C_str = s.substr(eqPos + 1);  // 提取C部分（'='之后的字符串）

        // 检查A、B、C是否都为数字
        if (!isNumber(A_str) || !isNumber(B_str) || !isNumber(C_str)) {
            cout << "FormatError\n"; 
            continue;                
        }

        // 将字符串转换为长整型，并判断A*B是否等于C
        ll A = stoll(A_str), B = stoll(B_str),
           C = stoll(C_str);  // 转换为long long类型
        if (A * B == C)
            cout << "Accepted\n"; 
        else
            cout << "wrongAnswer\n";  
    }
    return 0;
}

/*string::find(char c, size_t pos)函数会从指定位置pos开始查找字符c，如果找到则返回其位置，否则返回string::npos。
在找到第一个'x'的位置后，使用s.find('x',xPos +1)从该位置之后继续查找是否还有其他'x'。如果返回的不是string::npos，说明存在多个'x'，直接输出"FormatError"。*/
