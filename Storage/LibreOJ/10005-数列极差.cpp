#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

constexpr int maxn = 50000 + 10;

int n, a[maxn];

template <typename T> int calc(T q) {
    for (int i = 1; i <= n; ++i)
        q.push(a[i]);

    for (int i = 1; i < n; ++i) {
        int x = q.top();
        q.pop();
        int y = q.top();
        q.pop();
        q.push(x * y + 1);
    }

    return q.top();
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    using MaxQueue = priority_queue<int>;
    using MinQueue = priority_queue<int, vector<int>, greater<int>>;
    cout << calc(MinQueue()) - calc(MaxQueue()) << endl;

    return 0;
}