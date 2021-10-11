#include <bits/stdc++.h>
using namespace std;

constexpr int maxk = 100000;

int k, n, cnt[maxk];
string str[maxk];

struct Comparer {
    bool operator()(int lhs, int rhs) {
        if (cnt[lhs] != cnt[rhs])
            return cnt[lhs] > cnt[rhs];
        return str[lhs] > str[rhs];        
    }
};

priority_queue<int, vector<int>, Comparer> q[26];

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> n;
    for (int i = 1; i <= k; ++i) {
        cin >> str[i];
        q[str[i][0] - 'a'].push(i);
    }
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        int x = q[c - 'a'].top();
        q[c - 'a'].pop();
        cout << str[x] << endl;
        ++cnt[x];
        q[c - 'a'].push(x);
    }
    return 0;
}