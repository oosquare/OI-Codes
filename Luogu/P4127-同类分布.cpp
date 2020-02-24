#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll f[20][201][201];
int digit[20];
ll l,r;
int mmod;

ll DP(int pos,int sum,int mod,int limit){
    if(pos==-1) return mod==0&&sum==mmod?1:0;
    if(!limit&&f[pos][sum][mod]!=-1)
        return f[pos][sum][mod];
    int up=limit?digit[pos]:9;
    ll ans=0;
    for(int i=0;i<=up;++i){
        ans+=DP(pos-1,sum+i,(mod*10+i)%mmod,limit&&i==up);
    }
    if(!limit)
        f[pos][sum][mod]=ans;
    return ans;
}

ll solve(ll in){
    int len=0;
    while(in){
        digit[len++]=in%10;
        in/=10;
    }
	ll ans=0;
	for(int i=1;i<=len*9;++i){
		mmod=i;
		memset(f,-1,sizeof(f));
    	ans+=DP(len-1,0,0,true);
	}
    return ans;
}

int main(){
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",solve(r)-solve(l-1));
    return 0;
}