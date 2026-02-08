
#include <cstddef>
#include <stack>

using namespace std;

class MyQueue {
   private:
    stack<int> instk, outstk;
    void Inout() {
        while (!instk.empty()) {
            outstk.push(instk.top());
            instk.pop();
        }
    }

   public:
    MyQueue() {}

    void push(int x) { instk.push(x); }

    int pop() {
        if (outstk.empty()) {
            Inout();
        }
        int num = outstk.top();
        outstk.pop();
        return num;
    }

    int peek() {
        if (outstk.empty()) {
            Inout();
        }
        return outstk.top();
    }

    bool empty() { return instk.empty() && outstk.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */