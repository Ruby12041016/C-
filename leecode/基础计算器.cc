#include <cstddef>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
   public:
    int calculate(string s) {
        int len = s.size();
        vector<int> v;
        int num = 0;
        char sign = '+';
        for (int i = 0; i < len; i++) {
            if (isdigit(s[i])) {
                num = num * 10 + int(s[i] - '0');
            }
            if (!isdigit(s[i]) && s[i] != ' ' || i == len - 1) {
                switch (sign) {
                    case '+':
                        v.push_back(num);
                        break;
                    case '-':
                        v.push_back(-num);
                        break;
                    case '*':
                        v.back() *= num;
                        break;
                    case '/':
                        v.back() /= num;
                        break;
                }
                sign = s[i];
                num = 0;
            }
        }
        return accumulate(v.begin(), v.end(), 0);
    }
};