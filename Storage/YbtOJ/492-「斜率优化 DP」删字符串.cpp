#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

typedef long long ll;

int n, ml, mr;
ll dif[maxn], sum[maxn], f[maxn], a, b, c, d;
int que1[maxn], que2[maxn], cnt[maxn][30];
int l1, r1, l2, r2, cl, cr;
char str[maxn];

ll square(ll x) {
    return x * x;
}

ll calc(int i) {
    return f[i] - c * sum[i];
}

ll X(int i) {
    return sum[i];
}

ll Y(int i) {
    return f[i] + a * square(sum[i]);
}

int getmax(int l, int r) {
    int res = 0;
    for (int i = 0; i < 26; ++i)
        res = max(res, cnt[r][i] - cnt[l - 1][i]);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> a >> b >> c >> d >> ml >> mr;
    cin >> (str + 1);
    for (int i = 1; i <= n; ++i)
        cin >> dif[i], sum[i] = sum[i - 1] + dif[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            cnt[i][j] = cnt[i - 1][j] + (str[i] - 'a' == j);

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    l1 = r1 = 1;
    l2 = 1, r2 = 0;
    cl = 0, cr = -1;
    for (int i = 1; i <= n; ++i) {
        while (l1 < r1 && 
            (Y(que1[l1 + 1]) - Y(que1[l1])) <= 
            2 * a * sum[i] * (X(que1[l1 + 1]) - X(que1[l1])))
            ++l1;
        f[i] = f[que1[l1]] + a * square(sum[i] - sum[que1[l1]]) + b;
        
        if (ml <= mr) {
            while (cl < i && getmax(cl + 1, i) > mr)
                ++cl;
            if (cr < cl)
                cr = cl;
            while (cr < i && getmax(cr + 1, i) >= ml) {
                while (l2 <= r2 && calc(que2[r2]) >= calc(cr))
                    --r2;
                que2[++r2] = cr;
                ++cr;
            }
            --cr;
            while (l2 <= r2 && que2[l2] < cl)
                ++l2;
            if (l2 <= r2)
                f[i] = min(f[i], f[que2[l2]] + c * (sum[i] - sum[que2[l2]]) + d);
        }
        if (l1 <= r1 && X(que1[r1]) == X(i)) {
            if (Y(que1[r1]) < Y(i))
                continue;
            else
                --r1;
        }
        while (l1 < r1 && 
            (Y(que1[r1 - 1]) - Y(que1[r1])) * (X(que1[r1]) - X(i)) >= 
            (Y(que1[r1]) - Y(i)) * (X(que1[r1 - 1]) - X(que1[r1])))
            --r1;
        que1[++r1] = i;
        
    }

    for (int i = 1; i <= n; ++i)
        cout << f[i] << endl;
    return 0;
}
