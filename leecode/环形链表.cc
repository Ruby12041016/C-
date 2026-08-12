#include <cstddef>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
   public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }
};

// 快慢指针：对于链表来说，如果在链表中引入两个以不同速度（一个比另一个快一倍）前进的指针，在链表存在环的情况下，这两个指针必定会相遇。
