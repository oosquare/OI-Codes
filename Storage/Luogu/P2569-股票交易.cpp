#include <bits/stdc++.h>
using namespace std;

namespace IO
{

    inline char mygetchar()
    {
        static char ff[100000], *A = ff, *B = ff;
        return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
                   ? EOF
                   : *A++;
    }

    template <typename T = int>
    T read()
    {
        T x = 0, s = 1;
        char c = mygetchar();
        while (c < '0' || '9' < c)
        {
            if (c == '-')
                s = -1;
            c = mygetchar();
        }
        while ('0' <= c && c <= '9')
        {
            x = (x << 1) + (x << 3) + (c ^ 48);
            c = mygetchar();
        }
        return x * s;
    }

    template <typename T = int>
    void writeln(T x)
    {
        if (x < 0)
        {
            putchar('-');
            x = -x;
        }
        static int stk[100];
        int top = 0;
        if (x == 0)
            stk[++top] = 0;
        while (x)
        {
            stk[++top] = x % 10;
            x /= 10;
        }
        while (top)
            putchar(stk[top--] + '0');
        putchar('\n');
    }

    template <typename T = int>
    void writesp(T x)
    {
        if (x < 0)
        {
            putchar('-');
            x = -x;
        }
        static int stk[100];
        int top = 0;
        if (x == 0)
            stk[++top] = 0;
        while (x)
        {
            stk[++top] = x % 10;
            x /= 10;
        }
        while (top)
            putchar(stk[top--] + '0');
        putchar(' ');
    }

    template <typename T = int>
    void write(T x, char blank[])
    {
        if (x < 0)
        {
            putchar('-');
            x = -x;
        }
        static int stk[100];
        int top = 0;
        if (x == 0)
            stk[++top] = 0;
        while (x)
        {
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

constexpr int maxt = 2000 + 10;

int t, p, w, as, bs, ap, bp;
int f[maxt][maxt], q[maxt * 10], ans;

int calc1(int i, int k) {
    return f[i - w - 1][k] + k * ap;
}

int calc2(int i, int k) {
    return f[i - w - 1][k] + k * bp;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    t = read();
    p = read();
    w = read();
    memset(f, 128, sizeof(f));
    for (int i = 1; i <= t; ++i) {
        ap = read();
        bp = read();
        as = read();
        bs = read();
        for (int j = 0; j <= as; ++j)
            f[i][j] = -j * ap;
        for (int j = 0; j <= p; ++j)
            f[i][j] = max(f[i][j], f[i - 1][j]);
        if (i <= w)
            continue;
        int front = 1, back = 0;
        for (int j = 0; j <= p; ++j) {
            while (front <= back && q[front] < j - as)
                ++front;
            while (front <= back && calc1(i, q[back]) <= calc1(i, j))
                --back;
            q[++back] = j;
            if (front <= back)
                f[i][j] = max(f[i][j], calc1(i, q[front]) - j * ap);
        }
        front = 1, back = 0;
        for (int j = p; j >= 0; --j) {
            while (front <= back && q[front] > j + bs)
                ++front;
            while (front <= back && calc2(i, q[back]) <= calc2(i, j))
                --back;
            q[++back] = j;
            if (front <= back)
                f[i][j] = max(f[i][j], calc2(i, q[front]) - j * bp);
        }
    }
    for (int i = 0; i <= p; ++i)
        ans = max(ans, f[t][i]);
    writeln(ans);
    return 0;
}