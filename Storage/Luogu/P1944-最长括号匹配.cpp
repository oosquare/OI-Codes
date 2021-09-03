#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000000 + 10;

char b[maxn];
int n, ans, id, f[maxn];
stack<int> s;

bool match(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (b + 1);
    n = strlen(b + 1);
    for (int i = 1; i <= n; ++i) {
        if (b[i] == '(' || b[i] == '[') {
            s.push(i);
        } else {
            int l = i - f[i - 1] - 1;
            if (l < 1 || !match(b[l], b[i]))
                continue;
            f[i] = i - l + 1 + f[l - 1];
            if (ans < f[i]) {
                ans = f[i];
                id = i;
            }
        }
    }
    for (int i = id - ans + 1; i <= id; ++i)
        cout << b[i];
    cout << endl;
    return 0;
}