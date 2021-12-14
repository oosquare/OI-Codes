#include <cstdio>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';

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
        x = -x;
        putchar('-');
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 1000 + 10;
constexpr int maxm = 100 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, m[maxn], id;
int val[maxn][maxm];
int pi[maxm];

void preprocess(int pattern[], int len) {
    for (int i = 1; i <= len; ++i)
        pi[i] = 0;

    for (int i = 2, j = 0; i <= len; ++i) {
        while (j && pattern[i] != pattern[j + 1])
            j = pi[j];

        if (pattern[i] == pattern[j + 1])
            ++j;

        pi[i] = j;
    }
}

bool match(int target[], int pattern[], int tlen, int plen) {
    for (int i = 1, j = 0; i <= tlen; ++i) {
        while (j && target[i] != pattern[j + 1])
            j = pi[j];

        if (target[i] == pattern[j + 1])
            ++j;

        if (j == plen)
            return true;
    }

    return false;
}

bool check(int len) {
    for (int i = 1; i + len - 1 <= m[id]; ++i) {
        preprocess(val[id] + i - 1, len);
        bool valid = true;

        for (int j = 1; j <= n; ++j) {
            if (j == id)
                continue;

            if (!match(val[j], val[id] + i - 1, m[j], len)) {
                valid = false;
                break;
            }
        }

        if (valid)
            return true;
    }

    return false;
}

int main() {
    n = read();

    for (int i = 1; i <= n; ++i) {
        m[i] = read();

        for (int j = 1; j <= m[i]; ++j)
            val[i][j] = read();

        for (int j = 1; j < m[i]; ++j)
            val[i][j] = val[i][j + 1] - val[i][j];

        --m[i];
        
        if (!id || m[id] < m[i])
            id = i;
    }

    int l = 1, r = m[id], ans = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    write(ans + 1);
    return 0;
}