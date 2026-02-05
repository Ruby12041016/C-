#include <cstddef>

class MyLinkedList {
   private:
    struct LinkNode {
        int val;
        struct LinkNode* next;
        LinkNode(int val) : val(val), next(NULL) {}
        LinkNode(int val, struct LinkNode* next) : val(val), next(next) {}
    };
    struct LinkNode* dummyNode;
    int size;

   public:
    MyLinkedList() {
        dummyNode = new LinkNode(0);
        size = 0;
    }

    int get(int index) {
        if (index > size - 1 || index < 0) {
            return -1;
        }
        LinkNode* p = dummyNode->next;
        while (index--) {
            p = p->next;
        }
        return p->val;
    }

    void addAtHead(int val) {
        struct LinkNode* newnode = new LinkNode(val, dummyNode->next);
        dummyNode->next = newnode;
        size++;
    }

    void addAtTail(int val) {
        LinkNode* p = dummyNode;
        while (p->next != NULL) {
            p = p->next;
        }
        struct LinkNode* newnode = new LinkNode(val, NULL);
        p->next = newnode;
        size++;
    }

    void addAtIndex(int index, int val) {
        if (index > size || index < 0) {
            return;
        }
        LinkNode* p = dummyNode;
        while (index--) {
            p = p->next;
        }
        struct LinkNode* newnode = new LinkNode(val, p->next);
        p->next = newnode;
        size++;
    }

    void deleteAtIndex(int index) {
        if (index > size - 1 || index < 0) {
            return;
        }
        LinkNode* p = dummyNode;
        while (index--) {
            p = p->next;
        }
        LinkNode* q = p->next;
        p->next = p->next->next;
        delete q;
        q = NULL;
        size--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */