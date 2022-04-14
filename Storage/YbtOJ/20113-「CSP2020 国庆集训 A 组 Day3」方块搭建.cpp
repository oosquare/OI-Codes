#include <bits/stdc++.h>

using namespace std;
const long long inf = (long long)2e18;
const int N = 1234567;

int h[N];
vector<int> ev[N];
long long ans[N];
long long sum[N];

int main() {
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
    int n;
    long long m;
    scanf("%d %lld", &n, &m);
    int rleft = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", h + i);
        rleft = max(rleft, h[i]);
    }
    int rright = (int)1.01e9;
    while (rleft < rright) {
        int mid = (rleft + rright + 1) >> 1;
        for (int i = 0; i < n; i++) ans[i] = 0;
        for (int rot = 0; rot < 2; rot++) {
            sum[0] = h[0];
            for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + h[i]; // è®¡ç®åæ¥çæ¹åæ°
            for (int i = 0; i < n; i++) ev[i].clear();
            for (int i = 0; i < n; i++) { // æå¥ç¬¦åæ¡ä»¶çå
                int j = i + mid - h[i];
                if (j < n) ev[j].push_back(i);
            }
            int mx = -1;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < (int)ev[i].size(); j++) {
                    mx = max(mx, ev[i][j]);
                }
                if (mx >= 0) { // è®¡ç®éè¦çæ¹å
                    int from = mid - 1;
                    int to = mid - (i - mx) + 1;
                    ans[i] += (to + from) * 1LL * (from - to + 1) / 2;
                    ans[i] -= (sum[i - 1] - sum[mx]);
                } else
                    ans[i] += inf;
            }
            for (int i = 0; i < n - i - 1; i++) { // ååäº¤æ¢ï¼ç­ä»·äºå·¦å³ä¸¤è¾¹ååä¸æ¬¡
                swap(h[i], h[n - i - 1]);
                swap(ans[i], ans[n - i - 1]);
            }
        }
        bool found = false;
        for (int i = 0; i < n; i++) {
            ans[i] += mid - h[i]; // å ä¸ä¸æ¹çæ¹åæ°
            if (ans[i] <= m) {
                found = true;
                break;
            }
        }
        if (found)
            rleft = mid;
        else
            rright = mid - 1;
    }
    printf("%d\n", rleft);
    return 0;
}
