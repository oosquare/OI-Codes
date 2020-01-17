#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
ull n,s;

bool check(ull x){
    ull y=x;
    while(x>0){
        y-=x%10; x/=10;
    }
    return y>=s;
}

int main(){
    cin>>n>>s;
    ull l=0,r=n,ans=0x7fffffffll;
    while(l<=r){
        ull mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<(ans==0x7fffffffll?0:n-ans+1);
}