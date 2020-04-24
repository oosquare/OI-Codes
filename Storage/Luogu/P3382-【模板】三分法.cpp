#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

struct func {
    vector<double> a;
    void add(double v) {
        a.push_back(v);
    }

    double operator()(double x) {
        double res = 0;
        for (int i = 0; i < a.size(); ++i)
            res = res * x + a[i];
        return res;
    }
} f;

int n;
double l, r;
constexpr double epsilon = 1e-8;

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%lf%lf", &n, &l, &r);
    for (int i = 0; i <= n; ++i) {
        double v;
        scanf("%lf", &v);
        f.add(v);
    }
    double sl = l, sr = r;
    while (abs(sr - sl) > epsilon) {
        double lmid = sl + (sr - sl) / 3, rmid = sr - (sr - sl) / 3;
        if (f(lmid) < f(rmid))
            sl = lmid;
        else
            sr = rmid;
    }
    printf("%.5lf\n", sl);
    return 0;
}