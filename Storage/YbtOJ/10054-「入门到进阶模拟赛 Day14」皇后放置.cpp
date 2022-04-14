/*
#include <bits/stdc++.h>
using namespace std;

namespace IO {

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

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

const int maxn = 9 + 9;
int n, ans, fg[maxn];
bool row[30], col[30], dia[30];
char c[maxn][maxn];
vector<int> q;
set<vector<int>> t;

void check(int sum) {
    if (sum < ans)
        return;
    if (sum > ans)
        ans = sum, t.clear();
    t.insert(q);
    return;
}

void DFS(int r, int sum) {
    if (r > maxn) {
        check(sum);
        return;
    }
    for (int i = 1; i <= r; i++)
        if (!row[r] && !col[i] && !dia[abs(r - i)]) {
            row[r] = 1;
            col[i] = 1;
            dia[abs(r - i)] = 1;
            q.push_back(r * (r - 1) / 2 + i);
            DFS(r + 1, sum + 1);
            q.pop_back();
            row[r] = 0;
            col[i] = 0;
            dia[abs(r - i)] = 0;
        }
    DFS(r + 1, sum);
}

int main() {
    freopen("queen.in", "r", stdin);
    freopen("queen.out", "w", stdout);
    n = IO::read();
    for (int i = 1; i <= n; i++) {
        scanf("%s", c[i] + 1);
        for (int j = 1; j <= i; j++)
            if (c[i][j] == '*')
                row[i] = 1, col[j] = 1, dia[abs(i - j)] = 1;
    }
    DFS(1, 0);
    IO::writeln(ans);
    IO::writeln(t.size());
    return 0;
}
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 9 + 9;
int n, ans, fg[maxn];
bool row[30], col[30], dia[30];
char c[maxn][maxn];
vector<int> q;
set<vector<int>> t;

void check(int sum) {
    if (sum < ans)
        return;
    if (sum > ans)
        ans = sum, t.clear();
    t.insert(q);
    return;
}

void DFS(int r, int sum) {
    if (r > n) {
        check(sum);
        return;
    }
    for (int i = 1; i <= r; i++)
        if (!row[r] && !col[i] && !dia[abs(r - i)]) {
            row[r] = 1;
            col[i] = 1;
            dia[abs(r - i)] = 1;
            q.push_back(r * (r - 1) / 2 + i);
            DFS(r + 1, sum + 1);
            q.pop_back();
            row[r] = 0;
            col[i] = 0;
            dia[abs(r - i)] = 0;
        }
    DFS(r + 1, sum);
}

int main() {
    freopen("queen.in", "r", stdin);
    freopen("queen.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", c[i] + 1);
        for (int j = 1; j <= i; j++)
            if (c[i][j] == '*')
                row[i] = 1, col[j] = 1, dia[abs(i - j)] = 1;
    }
    DFS(1, 0);
    printf("%d\n%d\n", ans, t.size());
    return 0;
}
