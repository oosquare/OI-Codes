#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 5e5 + 10;

struct EqualCompare {
	bool operator()(double a, double b) {
		return abs(a - b) < 1e-10;
	}
};

vector<int> to[maxn];
double k[maxn];
int n, a[maxn], ans, len;
double tmp[maxn];

void link(int x, int y) {
	to[x].push_back(y);
	to[y].push_back(x);
}

void calc(int x, int fa) {
	for (int y : to[x]) {
		if (y == fa)
			continue;
		k[y] = k[x] + log(to[x].size() - (x == 1 ? 0 : 1));
		calc(y, x);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#else
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
#endif
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		link(a, b);		
	}
	calc(1, 0);
	for (int i = 1; i <= n; ++i) {
		double val = k[i] + log(a[i]);
		tmp[i] = val;
	}
	sort(tmp + 1, tmp + 1 + n);
	EqualCompare eq;
	ans = 1, len = 1;
	for (int i = 2; i <= n; ++i) {
		if (eq(tmp[i], tmp[i - 1])) {
			++len;
			ans = max(ans, len);
		} else {
			len = 1;
		}
	}
	ans = n - ans;
	cout << ans << endl;
	return 0;
} 
