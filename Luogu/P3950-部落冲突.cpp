#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

template <typename T>
void read(T &number) {
    number = 0;
    int symbol = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            symbol *= -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        number = (number << 3) + (number << 1) + c ^ '0';
        c = getchar();
    }
    number *= symbol;
}

#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)

const int maxn = 4000001;

int tree[maxn], tag[maxn];
int rev[maxn], dep[maxn], sze[maxn], dfn[maxn], top[maxn], son[maxn], father[maxn];
int n, m, root, x, y, z, a[maxn], war1[maxn], war2[maxn], tot;
int cnt, from[maxn], to[maxn], Next[maxn], head[maxn];
char opt;

void add(int x, int y) {
    cnt++;
    from[cnt] = x;
    to[cnt] = y;
    Next[cnt] = head[x];
    head[x] = cnt;
}

void pushdown(int rt, int l, int r) {
    if (tag[rt]) {
        tag[ls(rt)] += tag[rt];
        tag[rs(rt)] += tag[rt];
        int mid = (l + r) >> 1;
        tree[ls(rt)] += (mid - l + 1) * tag[rt];
        tree[rs(rt)] += (r - mid) * tag[rt];
        tag[rt] = 0;
    }
}

void update(int rt, int l, int r, int x, int y, int val) {
    if (l > y || r < x)
        return;
    if (l >= x && r <= y) {
        tag[rt] += val;
        tree[rt] += (r - l + 1) * val;
        return;
    } else {
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(ls(rt), l, mid, x, y, val);
        if (y > mid)
            update(rs(rt), mid + 1, r, x, y, val);
        tree[rt] = tree[ls(rt)] + tree[rs(rt)];
    }
}

int query(int rt, int l, int r, int x, int y) {
    if (l > y || r < x)
        return 0;
    if (l >= x && r <= y) {
        return tree[rt];
    } else {
        pushdown(rt, l, r);
        int mid = (l + r) >> 1, sum = 0;
        if (x <= mid)
            sum += query(ls(rt), l, mid, x, y);
        if (y > mid)
            sum += query(rs(rt), mid + 1, r, x, y);
        return sum;
    }
}

int dfs1(int x) {
    sze[x] = 1;
    dep[x] = dep[father[x]] + 1;
    for (int i = head[x]; i != -1; i = Next[i]) {
        int v = to[i], big = 0;
        if (father[x] == v)
            continue;
        father[v] = x;
        big = dfs1(v);
        sze[x] += big;
        if (big > sze[son[x]])
            son[x] = v;
    }
    return sze[x];
}

void dfs2(int x) {
    if (son[x]) {
        dfn[son[x]] = ++dfn[0];
        top[son[x]] = top[x];
        rev[dfn[0]] = son[x];
        dfs2(son[x]);
    }
    for (int i = head[x]; i != -1; i = Next[i]) {
        int v = to[i];
        if (!top[v]) {
            dfn[v] = ++dfn[0];
            top[v] = v;
            rev[dfn[0]] = v;
            dfs2(v);
        }
    }
}

void modifytree(int x, int y, int z) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy])
            swap(x, y), swap(fx, fy);
        update(1, 1, dfn[0], dfn[fx], dfn[x], z);
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(1, 1, dfn[0], dfn[x], dfn[y], z);
    update(1, 1, dfn[0], dfn[x], dfn[x], -z);
}

int querytree(int x, int y) {
    int fx = top[x], fy = top[y], ans = 0;
    while (fx != fy) {
        if (dep[fx] < dep[fy])
            swap(x, y), swap(fx, fy);
        ans += query(1, 1, dfn[0], dfn[fx], dfn[x]);
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans += query(1, 1, dfn[0], dfn[x], dfn[y]);
    ans -= query(1, 1, dfn[0], dfn[x], dfn[x]);
    return ans;
}

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////

    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    root = 1;
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs1(root);
    dfn[root] = ++dfn[0];
    rev[dfn[0]] = root;
    top[root] = root;
    dfs2(root);
    for (int i = 1; i <= m; i++) {
        scanf("%s", &opt);
        if (opt == 'C') {
            scanf("%d%d", &x, &y);
            war1[++tot] = x;
            war2[tot] = y;
            modifytree(x, y, 1);
        }
        if (opt == 'U') {
            scanf("%d", &x);
            modifytree(war1[x], war2[x], -1);
        }
        if (opt == 'Q') {
            scanf("%d%d", &x, &y);
            int q = querytree(x, y);
            if (q == 0)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", etime - stime);
    if (etime - stime >= TIME_LIMIT) {
        printf("<<< Warning >>> Time lsimited Exceeded\n");
    }
#endif
    return 0;
}

//
//        ^ y
//       1|                            y = sin x (0 < x < 2π)
//  - - - | - - - + - - - - - - - - - - - - - -
//        |  +         +
// -------+---------------+---------------+----------> x
//       O|               π  +         +  2π
//  - - - | - - - - - - - - - - - + - - - - - -
//      -1|
//        |
//