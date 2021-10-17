#include <bits/stdc++.h>
using namespace std;

constexpr int maxl = 100 + 10;
constexpr int oo = 0x3f3f3f3f;

int t, l;
string prog[maxl];

bool check() {
    bool vis[26];
    stack<char> st;
    memset(vis, 0, sizeof(vis));

    for (int i = 1; i <= l; ++i) {
        istringstream iss(prog[i]);
        string str;
        iss >> str;

        if (str == "F") {
            string var;
            iss >> var;

            if (vis[var[0] - 'a'])
                return false;

            st.push(var[0]);
            vis[var[0] - 'a'] = true;
        } else {
            if (st.empty())
                return false;

            vis[st.top() - 'a'] = false;
            st.pop();
        }
    }

    if (!st.empty())
        return false;

    return true;
}

int get(const string &s, const string &e) {
    if (s == "n" && e == "n")
        return 1;
    if (s != "n" && e == "n")
        return 2;
    if (s == "n" && e != "n")
        return 0;
    if (stoi(s) > stoi(e))
        return 0;
    return 1;
}

string calc() {
    int res = 0, now = 0;
    stack<int> cy;

    for (int i = 1; i <= l; ++i) {
        istringstream iss(prog[i]);
        string str;
        iss >> str;

        if (str == "F") {
            string var, start, end;
            iss >> var >> start >> end;

            if (!cy.empty() && cy.top() == 0)
                cy.push(0);
            else
                cy.push(get(start, end));
            
            if (cy.top() == 2) {
                ++now;
                res = max(res, now);
            }
        } else {
            if (cy.top() == 2)
                --now;

            cy.pop();
        }
    }
    string str;
    if (res == 0)
        str = "O(1)";
    else
        str = "O(n^"s + to_string(res) + ")"s;
    return str;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;

    for (int i = 1; i <= t; ++i) {
        while (cin.peek() == '\n')
            cin.get();

        string ans;
        getline(cin, ans, '\n');
        int pos = ans.find_first_of(' ');
        l = stoi(ans.substr(0, pos));
        ans = ans.substr(pos + 1, ans.size() - pos - 1);

        for (int j = 1; j <= l; ++j)
            getline(cin, prog[j]);

        if (!check())
            cout << "ERR" << endl;
        else if (calc() == ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}