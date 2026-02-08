#include <cstddef>
#include <queue>

using namespace std;

class MyStack {
   public:
    queue<int> q;
    MyStack() {}

    void push(int x) {
        int len = q.size();
        q.push(x);
        for (int i = 0; i < len; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int n = q.front();
        q.pop();
        return n;
    }

    int top() {
        int n = q.front();
        return n;
    }

    bool empty() { return q.empty(); }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */