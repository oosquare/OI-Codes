#include <bits/stdc++.h>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

constexpr int maxn = 1000 + 10;
multiset<int> to[maxn];
stack<int> sequence;
bool exist[maxn];
int n, degree[maxn];

void hierholzer(int x) {
    for (auto i = to[x].begin(); i != to[x].end(); i = to[x].begin()) {
        int y = *i;
        to[x].erase(i);
        to[y].erase(x);
        hierholzer(y);
    }
    sequence.push(x);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    int ss = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i) {
        char pair[5];
        scanf("%s", pair);
        int p0 = (int)pair[0], p1 = (int)pair[1];
        to[p0].insert(p1);
        to[p1].insert(p0);
        ++degree[p0];
        ++degree[p1];
        ss = min(p0, p1);
        exist[p0] = exist[p1] = true;
    }
    int s = -1, e = -1;
    for (int i = 1; i <= 256; ++i) {
        if (!exist[i])
            continue;
        if (degree[i] % 2) {
            if (s == -1)
                s = i;
            else if (e == -1)
                e = i;
            else {
                printf("No Solution\n");
                return 0;
            }
        }
    }
    if (s == -1)
        s = ss;
    hierholzer(s);
    while (!sequence.empty()) {
        printf("%c", (char)sequence.top());
        sequence.pop();
    }
    return 0;
}