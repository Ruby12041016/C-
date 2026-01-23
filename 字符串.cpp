// 1. 字符串反转
//  编写函数实现字符串反转
//  输入："hello"
//  输出："olleh"
//  要求：不能使用标准库的reverse函数
// 2. 回文判断
// 判断一个字符串是否是回文
// 回文：正读反读都一样
// 例如："racecar"是回文，"hello"不是
// 要求：忽略大小写和标点符号
// 例如："A man, a plan, a canal: Panama"是回文
// 3. 字符串压缩
// 实现简单的字符串压缩
// 输入："aaabbbcccaaa"
// 输出："a3b3c3a3"
// 如果压缩后没有变短，返回原字符串
// 输入："abc"
// 输出："abc"（因为"a1b1c1"比"abc"长）

#include <iostream>
#include <string>
#include<cctype>
#include<sstream>

using namespace std;

string reverseString(const string& str){
    string reversed;
    int len = str.length();
    reversed.reserve(len);
    for (int i = len - 1; i >= 0; i--) {
        reversed.push_back(str[i]);
    }
    return reversed;
}

int isPalindrome(const string& s){
    int left = 0;
    int right = s.length() - 1;
    while(left<right){
        while(left<right&&!isalnum(s[left])){
            left++;
        }
        while (left < right && !isalnum(s[right])) {
            right--;
        }
        if(tolower(s[left]!=tolower(s[right]))){
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

string press(const string& s){
    int len = s.length();
    if(len<=1){
        return s;
    }
    stringstream ss;
    int count = 1;
    char current = s[0];
    for(int i = 1; i < len;i++){
        if(s[i]==current){
            count++;
        }else{
            ss << current << count;
            current = s[i];
            count = 1;
        }
    }
    ss << current << count;
    string result = ss.str();
    return (result.length() < len) ? result : s;
}

int main() {
    string str;
    cout << "请输入一个字符串：";
    getline(cin, str);
    cout << "反转后：" << reverseString(str) << endl;

    cout << "请输入一个字符串: ";
    getline(cin, str);
    if (isPalindrome(str)) {
        cout << "是回文字符串" << endl;
    } else {
        cout << "不是回文字符串" << endl;
    }

    cout << "请输入要压缩的字符串: ";
    getline(cin, str);
    string compressed = press(str);
    cout << "压缩结果: " << compressed << endl;

    return 0;
}