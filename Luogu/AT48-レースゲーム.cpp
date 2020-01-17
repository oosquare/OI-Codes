#include <bits/stdc++.h>
using namespace std;
const double inf = 1e17;
const int lim = 2e5 + 5;
int n, s, e;
int l[lim], r[lim];
double ans = 0;

template <typename T>
T read() {
	T number=0,symbol=1;
	char c=getchar();
	while(!isdigit(c)) {
		if(c=='-') symbol*=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		number=number*10+c-'0';
		c=getchar();
	}
	return number*symbol;
}

double dis(double a, double b) {
	return sqrt(a * a + b * b);
}

int main() {
	n = read<int>();
	s = read<int>();
	e = read<int>();
	for (int i = 0; i <= n; i++){
		l[i] = read<int>();
		r[i] = read<int>();
	}
	l[n] = r[n] = e;
	int nowy = 0;
	double nowx = s;
	while (nowy < n) {
		double leftarc = -inf, rightarc = inf;
		int ly = nowy, ry = nowy;
		for (int y = nowy + 1; y <= n; y++) {
			double larc = (l[y] - nowx) / (y - nowy), rarc = (r[y] - nowx) / (y - nowy);
			if (larc > leftarc) {
				leftarc = larc;
				ly = y;
			}
			if (rarc < rightarc) {
				rightarc = rarc;
				ry = y;
			}
			if (leftarc >= rightarc) {
				if (ly < ry) {
					ans += dis(l[ly] - nowx, ly - nowy);
					nowy = ly;
					nowx = l[ly];
				} else {
					ans += dis(r[ry] - nowx, ry - nowy);
					nowy = ry;
					nowx = r[ry];
				}
				break;
			}
		}
	}
	printf("%0.14lf", ans);
	return 0;
}