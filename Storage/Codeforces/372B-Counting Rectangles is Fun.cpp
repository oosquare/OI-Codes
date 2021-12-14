#include <cstdio>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 40 + 10;

int n, m, q;
int mat0[maxn][maxn], mat[maxn][maxn], h[maxn];
int st[maxn], top;

void copy(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i)
        for (int j = y1; j <= y2; ++j)
            mat[i - x1 + 1][j - y1 + 1] = mat0[i][j];
}

int solve(int n, int m) {
    int ans = 0;

    for (int i = 1; i <= m; ++i)
        h[i] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            h[j] = (mat[i][j] == 1 ? 0 : h[j] + 1);

        top = 0;
        int sum = 0;

        for (int j = 1; j <= m; ++j) {
            while (top && h[st[top]] >= h[j]) {
                sum -= (st[top] - st[top - 1]) * h[st[top]];
                --top;
            }

            st[++top] = j;
            sum += (j - st[top - 1]) * h[j];
            ans += sum;
        }
    }

    return ans;
}

int main() {
    n = read(), m = read(), q = read();

    for (int i = 1; i <= n; ++i) {
        char str[50];
        scanf("%s", str + 1);

        for (int j = 1; j <= m; ++j)
            mat0[i][j] = str[j] - '0';
    }

    while (q--) {
        int a = read(), b = read(), c = read(), d = read();
        copy(a, b, c, d);
        write(solve(c - a + 1, d - b + 1));
    }

    return 0;
}