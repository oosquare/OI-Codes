#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;

int n;
char a[maxn];
int s[maxn], pos[maxn];

bool cmp(int lhs, int rhs) {
    if (lhs < rhs) {
        if (pos[lhs] >= rhs)
            return true;
        else
            return a[pos[lhs] + 1] <= a[pos[lhs]];
    } else {
        if (pos[rhs] >= lhs)
            return false;
        else
            return a[pos[rhs] + 1] >= a[pos[rhs]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> (a + 1);

    for (int i = n; i >= 1; --i) {
        if (a[i] == a[i + 1])
            pos[i] = pos[i + 1];
        else
            pos[i] = i;
    }

    iota(s + 1, s + 1 + n, 1);
    sort(s + 1, s + 1 + n, cmp);
    copy(s + 1, s + 1 + n, ostream_iterator<int>(cout, " "));
    return 0;
}