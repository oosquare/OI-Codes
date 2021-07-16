#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 700 + 10;
constexpr int mod = 1e9 + 7;

int f[maxn][maxn][3][3];
int paired[maxn];
stack<int> st;
char bra[maxn];
int n, ans;

void DP(int i, int j) {
	if (i + 1 == j) {
		f[i][j][0][1] = f[i][j][1][0] = f[i][j][0][2] = f[i][j][2][0] = 1;
		return;
	} else if (paired[i] == j) {
		DP(i + 1, j - 1);
		for (int a = 0; a <= 2; ++a) {
			for (int b = 0; b <= 2; ++b) {
				if (b != 1)
					f[i][j][0][1] += f[i + 1][j - 1][a][b], f[i][j][0][1] %= mod;
				if (a != 1)
					f[i][j][1][0] += f[i + 1][j - 1][a][b], f[i][j][1][0] %= mod;
				if (b != 2)
					f[i][j][0][2] += f[i + 1][j - 1][a][b], f[i][j][0][2] %= mod;
				if (a != 2)
					f[i][j][2][0] += f[i + 1][j - 1][a][b], f[i][j][2][0] %= mod;
			}
		}
		
	} else {
		int k = paired[i];
		DP(i, k);
		DP(k + 1, j);
		for (int a = 0; a <= 2; ++a) {
			for (int b = 0; b <= 2; ++b) {
				for (int c = 0; c <= 2; ++c) {
					for (int d = 0; d <= 2; ++d) {
						if ((b == 1 && c == 1) || (b == 2 && c == 2))
							continue;
						f[i][j][a][d] = (f[i][j][a][d] + 1LL * f[i][k][a][b] * f[k + 1][j][c][d]) % mod;
					}
				}
			}
		}	
	}
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> (bra + 1);
	n = strlen(bra + 1);
	for (int i = 1; i <= n; ++i) {
		if (bra[i] == '(')
			st.push(i);
		else {
			paired[st.top()] = i;
			st.pop();
		}
	}
	DP(1, n);
	for (int i = 0; i <= 2; ++i)
		for (int j = 0; j <= 2; ++j)
			ans = (1LL * ans + f[1][n][i][j]) % mod;
	cout << ans << endl;
	return 0;
}