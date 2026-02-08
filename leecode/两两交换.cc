#include<cstddef>
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
class Solution {
   public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* p = dummy;
        while (p->next != NULL && p->next->next != NULL) {
            ListNode* p1 = p->next;
            ListNode* p2 = p1->next;
            p->next = p2;
            p1->next = p2->next;
            p2->next = p1;
            p = p1;
            ;
        }
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};