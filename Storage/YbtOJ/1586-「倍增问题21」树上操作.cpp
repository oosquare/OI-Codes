// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2013 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <Licenses - GNU Project - Free Software Foundation>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

using namespace std;

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
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

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int N = 3e5 + 5;

int n, m, rt = 1;
int a[N];
struct Edge {
    int nxt, to;
} edge[N << 1];
int head[N], tot;
int cnt, dfn[N], id[N], d[N], siz[N], f[N][19];

inline void add_e(int x, int y) {
    edge[++tot] = {head[x], y};
    head[x] = tot;
}

inline void dfs(int u, int fa) {
    dfn[u] = ++cnt, id[cnt] = u;
    d[u] = d[fa] + 1, siz[u] = 1;
    f[u][0] = fa;
    for (int i = 1; i <= 17; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
}

inline int LCA(int x, int y) {
    if (d[x] > d[y]) swap(x, y);
    for (int i = 17; i >= 0; i--)
        if (d[x] <= d[f[y][i]]) y = f[y][i];
    if (x == y) return x;
    for (int i = 17; i >= 0; i--)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

inline int step(int x, int k) {
    for (int i = 0; i <= 17; i++)
        if ((1 << i) & k) x = f[x][i];
    return x;
}

long long t1[N << 5], t2[N << 5];

inline int lowbit(int x) { return x & (-x); }

void add(int k, long long v) {
    long long v1 = k * v;
    while (k <= n) {
        t1[k] += v, t2[k] += v1;
        k += lowbit(k);
    }
}

long long getsum(long long *t, int k) {
    long long ret = 0;
    while (k) {
        ret += t[k];
        k -= lowbit(k);
    }
    return ret;
}

void add1(int l, int r, long long v) {
    add(l, v), add(r + 1, -v);
}

long long getsum1(int l, int r) {
    return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
           (getsum(t2, r) - getsum(t2, l - 1));
}

void init() {
    for (int i = 1; i <= n; ++i)
        add1(i, i, a[id[i]]);
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i < n; i++) {
        int u = read(), v = read();
        add_e(u, v), add_e(v, u);
    }
    dfs(1, 0);
    init();
    while (m--) {
        int opt, x, y, val;
        opt = read();
        switch (opt) {
            case 1: {
                rt = read();
                break;
            }
            case 2: {
                x = read(), y = read(), val = read();
                int p1 = LCA(x, rt), p2 = LCA(x, y), p3 = LCA(y, rt);
                int p = p1;
                if (d[p] < d[p2]) p = p2;
                if (d[p] < d[p3]) p = p3;
                if (p == rt)
                    add1(1, n, val);
                else if (LCA(rt, p) == p) {
                    int s = step(rt, d[rt] - d[p] - 1);
                    add1(1, n, val);
                    add1(dfn[s], dfn[s] + siz[s] - 1, -val);
                } else
                    add1(dfn[p], dfn[p] + siz[p] - 1, val);
                break;
            }
            case 3: {
                x = read();
                if (x == rt)
                    writeln(getsum1(1, n));
                else if (LCA(rt, x) == x) {
                    int s = step(rt, d[rt] - d[x] - 1);
                    writeln(getsum1(1, n) -
                                getsum1(dfn[s], dfn[s] + siz[s] - 1));
                } else
                    writeln(getsum1(dfn[x], dfn[x] + siz[x] - 1));
                break;
            }
        }
    }
    return 0;
}
