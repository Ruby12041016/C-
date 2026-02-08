#include <cstddef>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        stack<ListNode*> stk;
        ListNode* now = dummy;
        while (now) {
            stk.push(now);
            now = now->next;
        }
        for (int i = 0; i < n; i++) {
            stk.pop();
        }
        ListNode* p = stk.top();
        p->next = p->next->next;
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};