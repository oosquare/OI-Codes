#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

typedef long long ll;
ll f[25][12];
int digit[25];
int startpos;

ll DP(int pos,int before,bool limit){
    if(pos==-1)
        return 1;

    if(!limit&&f[pos][before]!=-1)
        return f[pos][before];
    int up=limit?digit[pos]:9;
    ll ans=0;

    for(int i=0;i<=up;++i){
        if((pos==startpos&&i!=4)||(pos==startpos-1&&i!=9))
            continue;
        if((pos>=startpos&&before==4&&i==9)) continue;
        ans+=DP(pos-1,i,limit&&i==up);
    }
    if(!limit)
        f[pos][before]=ans;
    return ans;
}

ll solve(){
    char d[100];
    ll ans=0;
    scanf("%s",d);
    int l=strlen(d);
    for(int i=0;i<l;++i){
        digit[i]=d[l-i-1]-'0';
    }
    for(int i=l-1;i>=1;--i){
        memset(f,-1,sizeof(f));
        startpos=i;
        ans+=DP(l-1,11,true);
    }
    return ans;
}

int main(int argc, char *argv[]) {
    freopen("lucky.in", "r", stdin);
    freopen("lucky.out", "w", stdout);
    
    printf("%lld\n",solve());

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
