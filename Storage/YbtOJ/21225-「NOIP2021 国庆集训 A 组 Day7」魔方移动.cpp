#include <bits/stdc++.h>
using namespace std;

int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int nowdir = 0, nowx = 1, nowy = 1;
string s;

void turnLeft() {
	nowdir = (nowdir - 1 + 4) % 4;
}

void turnRight() {
	nowdir = (nowdir + 1) % 4;
}

int add(int v, int delta) {
	return (v + delta + 3) % 3;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("cubewalking.in", "r", stdin);
    freopen("cubewalking.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> s;
	for (char c : s)
		if (c == 'L')
			turnLeft();
		else if (c == 'R')
			turnRight(); 	   
		else
			nowx = add(nowx, dir[nowdir][0]),
			nowy = add(nowy, dir[nowdir][1]);
	if ((nowx == 0 || nowx == 2) && (nowy == 0 || nowy == 2))
		cout << "RED" << endl;
	else if (nowx == 1 && nowy == 1)
		cout << "GREEN" << endl;
	else
		cout << "BLUE" << endl;
    return 0;
}
