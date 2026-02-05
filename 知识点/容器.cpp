// 练习1：统计单词频率

#include <iostream>
#include <map>
#include <sstream>
#include <string>
    
using namespace std;

int main() {
    string text = "apple banana apple orange banana apple";

    map<string, int> wordCount;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        wordCount[word]++;  
    }

    cout << "单词频率统计:" << endl;
    for (const auto& [w, count] : wordCount) {
        cout << w << ": " << count << endl;
    }

    return 0;
}
