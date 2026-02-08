#include <cstddef>
#include <stack>

using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
   public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        stack<ListNode*> stk1;
        stack<ListNode*> stk2;
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while (p1) {
            stk1.push(p1);
            p1 = p1->next;
        }
        while (p2) {
            stk2.push(p2);
            p2 = p2->next;
        }
        ListNode* intersectVal = NULL;
        while (!stk1.empty() && !stk2.empty() && stk1.top() == stk2.top()) {
            intersectVal = stk1.top();
            stk1.pop();
            stk2.pop();
        }
        return intersectVal;
    }
};