#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 500001;
int n, L, C[maxn], l[maxn];
ll sum[maxn], f[maxn];
int stk[maxn], top;

inline ll calculate(int from, int to) {
    ll x = to - from + sum[to] - sum[from] - 1;
    return f[from] + (x - L) * (x - L);
}

int search(int x) {
    int left = 1, right = top;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (l[stk[mid]] == x)
            return mid;
        else if (l[stk[mid]] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return right;
}

int main() {
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &C[i]);
        sum[i] = sum[i - 1] + C[i];
    }
    for (int i = 1; i <= n; ++i) l[i] = n + 1;
    memset(stk, 0x3f, sizeof(stk));
    l[0] = 1;
    stk[++top] = 0;
    for (int i = 1; i <= n; ++i) {
        f[i] = calculate(stk[search(i)], i);
        while (top != 0 && i < l[stk[top]] && calculate(i, l[stk[top]]) < calculate(stk[top], l[stk[top]])) {
            --top;
        }
        if (top == 0) {
            stk[++top] = i;
            l[i] = i;
            continue;
        }
        int left = l[stk[top]], right = n;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (calculate(stk[top], mid) < calculate(i, mid))
                left = mid + 1;
            else
                right = mid - 1;
        }
        if (calculate(stk[top], left) < calculate(i, left))
            continue;
        stk[++top] = i;
        l[i] = left;
    }
    printf("%lld\n", f[n]);
    return 0;
}