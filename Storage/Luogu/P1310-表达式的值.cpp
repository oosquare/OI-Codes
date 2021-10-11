#include <bits/stdc++.h>
using namespace std;

constexpr int maxl = 100000 + 10;
constexpr int mod = 10007;

char expr[maxl];
int l, n, f[maxl][2];
stack<char> op;

void calc(char op, int i, int j) {
    if (op == '+') {
        f[i][1] = (f[i][0] * f[j][1] % mod + f[i][1] * (f[j][0] + f[j][1]) % mod) % mod;
        f[i][0] = f[i][0] * f[j][0] % mod;
    } else {
        f[i][0] = (f[i][0] * (f[j][0] + f[j][1]) % mod + f[i][1] * f[j][0] % mod) % mod;
        f[i][1] = f[i][1] * f[j][1] % mod;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> l;
    cin >> (expr + 1);
    expr[l + 1] = ')', expr[l + 2] = '\0';
    op.push('(');
    n = 1;
    f[1][0] = f[1][1] = 1;
    for (int i = 1; i <= l + 1; ++i) {
        if (expr[i] == '(') {
            op.push('(');
        } else if (expr[i] == ')') {
            for (; op.top() != '('; op.pop(), --n)
                calc(op.top(), n - 1, n);
            op.pop();
        } else {
            for (; op.top() != '(' && op.top() <= expr[i]; op.pop(), --n)
                calc(op.top(), n - 1, n);
            op.push(expr[i]);
            ++n;
            f[n][0] = f[n][1] = 1;            
        }
    }
    cout << f[n][0] << endl;
    return 0;
}