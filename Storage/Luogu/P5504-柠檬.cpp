#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 100000 + 10;
constexpr int maxs = 10000 + 10;

struct Stack {
    vector<int> st;

    int size() const { return st.size(); }

    int top(int rank = 1) const { return st[st.size() - rank]; }

    void pop() { st.pop_back(); }

    void push(int val) { st.push_back(val); }  
};

ll f[maxn], s[maxn], c[maxn], d[maxn];
int n, cnt[maxs];
Stack stk[maxs];

template <typename T>
T square(T x) {
    return x * x;
}

ll x(int i) {
    return d[i];
}

ll y(int i) {
    return f[i - 1] + 1LL * s[i] * square(1LL * d[i]);
}

ll calc(int i, int j) {
    return f[j - 1] + s[i] * square(c[i] - d[j]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        c[i] = ++cnt[s[i]];
        d[i] = c[i] - 1;
    }
    for (int i = 1; i <= n; ++i) {
        Stack &st = stk[s[i]];
        while (st.size() >= 2 && 
            (y(st.top(1)) - y(st.top(2))) * (x(i) - x(st.top(1))) <= 
            (y(i) - y(st.top(1))) * (x(st.top(1)) - x(st.top(2))))
            st.pop(); //维护上凸壳
        st.push(i);
        while (st.size() >= 2 && calc(i, st.top(1)) <= calc(i, st.top(2)))
            st.pop(); //去掉不够优的决策
        f[i] = calc(i, st.top()); //根据DP方程计算
    }
    cout << f[n] << endl;
    return 0;
}