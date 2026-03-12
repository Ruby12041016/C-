#include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
   public:
    string simplifyPath(string path) {
        vector<string> stk;
        istringstream ss(path);
        string s;
        while (getline(ss, s, '/')) {
            if (s.empty() || s == ".") {
                continue;
            }
            if (s != "..") {
                stk.push_back(s);
            } else if (!stk.empty()) {
                stk.pop_back();
            }
        }
        string result;
        for (string& str : stk) {
            result += "/";
            if (!str.empty()) {
                result += str;
            }
        }
        if (stk.empty()) {
            return "/";
        }
        return result;
    }
};