class MinStack {
  public:
    stack<int> data, minv;
    MinStack() {}

    void push(int x) {
        data.push(x);
        if (minv.empty()) {
            minv.push(x);
        } else {
            int l = minv.top();
            minv.push(min(l, x));
        }
    }

    void pop() {
        data.pop();
        minv.pop();
    }

    int top() { return data.top(); }

    int getMin() { return minv.top(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */