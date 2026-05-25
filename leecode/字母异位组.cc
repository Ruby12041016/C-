#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
   public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& s : strs) {
            string key = s;     //复制一份
            sort(key.begin(), key.end());
            mp[key].push_back(s);  // 存原始字符串
        }
        vector<vector<string>> res;
        for (auto& p : mp) {
            res.push_back(move(
                p.second));  // 把哈希表里存好的每一个分组，转移到最终结果里。
        }
        return res;
    }
};

/*给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
示例 1:
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
解释：
在 strs 中没有字符串可以通过重新排列来形成 "bat"。
字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。*/

/*思路：
如果两个字符串从小到大排序后相等，那么两个字符串就互为字母异位词，否则不是。
例如 aab,aba,baa 排序后都是 aab，所以 aab,aba,baa 互为字母异位词。

用哈希表分组，把排序后的字符串当作哈希表的key，排序前的字符串加到对应的列表中（哈希表的 value）。最后把哈希表的所有 value 加到一个列表中返回。
*/
