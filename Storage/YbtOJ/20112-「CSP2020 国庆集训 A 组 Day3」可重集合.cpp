#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;

int arr[maxn], cnt[maxn], mx, n, now, ans;

int main() {
    freopen("multiset.in", "r", stdin);
    freopen("multiset.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &arr[i]), ++cnt[arr[i]], mx = max(mx, arr[i]); // ç»è®¡æ¯ä¸ªæ°çä¸ªæ°ä»¥åæå¤§å¼
    now = cnt[0];
    for (int i = 1; i <= mx; ++i) {
        ++ans;
        now = (now + 1) / 2; // å°å·²ç»åä¸º 0 çæ°çä¸ªæ°é¤ä»¥ 2ï¼ è¡¨ç¤ºåå¹¶
        now += cnt[i]; // å ä¸ç°å¨è¢«åä¸º 0 çæ°
    }
    for (; now > 1; now = (now + 1) / 2)
        ++ans; // åå¹¶æææ°
    printf("%d\n", ans);
    return 0;
}
