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
    void reorderList(ListNode* head) {
        if (!head || !head->next)
            return;
        stack<ListNode*> stk;
        ListNode* p = head;
        while (p != NULL) {
            stk.push(p);
            p = p->next;
        }
        if (stk.size() <= 2) {
            return;
        }
        int len = stk.size() / 2;
        p = head;
        ListNode* topnode = stk.top();
        while (len--) {
            ListNode* temp = p->next;
            if (temp == topnode) {
                break;
            }
            p->next = stk.top();
            stk.pop();
            p->next->next = temp;
            p = temp;
        }
        p->next = NULL;
    }
};