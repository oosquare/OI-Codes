#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int logx = 30;

struct Info {
    int dis[2], to, last = -1;

    int sumdis() {
        return dis[0] + dis[1];
    }

    string toString() {
        string res("{");
        res += to_string(sumdis());
        res += ", {";
        res += to_string(dis[0]);
        res += ", ";
        res += to_string(dis[1]);
        res += "}, ";
        res += to_string(to) + ", " + to_string(last) + "}";
        return res;
    }
};

struct City {
    int h, id;
};

City city[maxn];
Info step[maxn][logx + 1][2];
int n, m, s, x, suf[maxn][2];
map<int, int> tmp;

void getClosest() {
    for (int i = n; i >= 1; --i) {
        tmp[city[i].h] = i;
        auto it0 = tmp.lower_bound(city[i].h);
        auto it = it0;
        for (int j = 1; j <= 2; ++j) {
            if (it == tmp.begin())
                break;
            --it;
            int delta = abs(city[i].h - it->first);
            if (delta < abs(city[i].h - city[suf[i][1]].h) || suf[i][1] == 0) {
                suf[i][0] = exchange(suf[i][1], it->second);
            } else if (delta < abs(city[i].h - city[suf[i][0]].h) || suf[i][0] == 0) {
                suf[i][0] = it->second;
            }
        }
        it = it0;
        for (int j = 1; j <= 2; ++j) {
            ++it;
            if (it == tmp.end())
                break;
            int delta = abs(city[i].h - it->first);
            if (delta < abs(city[i].h - city[suf[i][1]].h) || suf[i][1] == 0) {
                suf[i][0] = exchange(suf[i][1], it->second);
            } else if (delta < abs(city[i].h - city[suf[i][0]].h) || suf[i][0] == 0) {
                suf[i][0] = it->second;
            }
        }
    }
}

int distance(int i, int j) {
    if (j == 0)
        return 0x3f3f3f3f;
    return abs(city[i].h - city[j].h);
}

void preprocess() {
    for (int i = 1; i <= n; ++i) {
        if (distance(i, suf[i][0]) == 1 && suf[i][0] != 0)
            step[i][0][0] = {{1, 0}, suf[i][0], 0};
        if (distance(i, suf[i][1]) == 1 && suf[i][1] != 0)
            step[i][0][1] = {{0, 1}, suf[i][1], 1};
    }

    for (int t = 0; t <= logx; ++t) {
        for (int i = 1; i <= n; ++i) {
            if (step[i][t - 1][0].last == -1 && (1 << t) >= distance(i, suf[i][0]) && suf[i][0] != 0) {
                step[i][t][0] = {
                    {
                        distance(i, suf[i][0]),
                        0
                    },
                    suf[i][0],
                    0
                };
            } else if (step[i][t - 1][0].last != -1) {
                auto ia = step[i][t - 1][0];
                auto ib = step[ia.to][t - 1][ia.last ^ 1];
                step[i][t][0] = {
                    {
                        ia.dis[0] + ib.dis[0],
                        ia.dis[1] + ib.dis[1]
                    },
                    ib.last != -1 ? ib.to : ia.to,
                    ib.last != -1 ? ib.last : ia.last,
                };
            } else {
                step[i][t][0].last = -1;
            }

            if (step[i][t - 1][1].last == -1 && (1 << t) >= distance(i, suf[i][1]) && suf[i][1] != 0) {
                step[i][t][1] = {
                    {
                        0,
                        distance(i, suf[i][1])
                    },
                    suf[i][1],
                    1
                };
            } else if (step[i][t - 1][1].last != -1) {
                auto ia = step[i][t - 1][1];
                auto ib = step[ia.to][t - 1][ia.last ^ 1];
                step[i][t][1] = {
                    {
                        ia.dis[0] + ib.dis[0],
                        ia.dis[1] + ib.dis[1]
                    },
                    ib.last != -1 ? ib.to : ia.to,
                    ib.last != -1 ? ib.last : ia.last,
                };
            } else {
                step[i][t][1].last = -1;
            }
        }
    }
}

Info jump(int x, int s) {
    int who = 0;
    Info res;
    res.dis[0] = res.dis[1] = 0;
    for (int t = logx; t >= 0; --t) {
        if ((1 << (t - 1)) > x)
            continue;
        auto st = step[s][t][who];
        // cout << "res : " << res.toString() << " | st : " << st.toString() << endl;
        if (st.last == -1 || st.sumdis() > x)
            continue;
        // cout << "x = " << x << " s = " << s << " t = " << t << endl;
        res.dis[0] += st.dis[0];
        res.dis[1] += st.dis[1];
        s = st.to;
        who = st.last ^ 1;
        x -= st.sumdis();
        ++t;
    }
    return res;
}

int cmp(int a, int b, int a1, int b1) {
    // a / b ?= a1 / b1 ==> a * b1 ?= a1 * b
    auto res = 1LL * a * b1 - 1LL * a1 * b;
    if (res > 0)
        return 1;
    else if (res == 0)
        return 0;
    else
        return -1;
}

void solve1() {
    int num = 0x3f3f3f3f, den = 0, id = 0;
    for (int i = 1; i <= n; ++i) {
        auto res = jump(x, i);
        if (res.dis[0] == 0 && res.dis[1] == 0)
            continue;
        int cmpres = cmp(res.dis[0], res.dis[1], num, den);
        if (cmpres == -1 || (cmpres == 0 && city[i].h > city[id].h)) {
            num = res.dis[0];
            den = res.dis[1];
            id = i;
        }
    }
    cout << id << endl;
}

void solve2() {
    auto res = jump(x, s);
    cout << res.dis[0] << " " << res.dis[1] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> city[i].h;
        city[i].id = i;
    }
    getClosest();
    preprocess();
    cin >> x;
    solve1();
    cin >> m;
    while (m--) {
        cin >> s >> x;
        solve2();
    }
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : " << suf[i][0] << " " << distance(i, suf[i][0]) << " | ";
    //     cout << suf[i][1] << " " << distance(i, suf[i][1]) << endl;
    // }
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= logx; ++j) {
    //         cout << step[i][j][0].toString() << " | ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= logx; ++j) {
    //         cout << step[i][j][1].toString() << " | ";
    //     }
    //     cout << endl;
    // }
    return 0;
}