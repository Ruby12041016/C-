#include <string>
#include <unordered_map>

using namespace std;
class Solution {
   public:
    int romanToInt(string s) {
        unordered_map<string, int> m = {
            {"I", 1},    {"IV", 3},  {"IX", 8},  {"V", 5},   {"X", 10},
            {"XL", 30},  {"XC", 80}, {"L", 50},  {"C", 100}, {"CD", 300},
            {"CM", 800}, {"D", 500}, {"M", 1000}};
        int num = m[s.substr(0, 1)];
        for (int i = 1; i < s.size(); i++) {
            string s1 = s.substr(i, 1);
            string s2 = s.substr(i - 1, 2);
            if (m.count(s2)) {
                num += m[s2];
            } else {
                num += m[s1];
            }
        }
        return num;
    }
};