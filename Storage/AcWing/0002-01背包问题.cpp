#include <bits/stdc++.h>
using namespace std;
int n,v;
int cost[1001],val[1001];
int f[1001];

int main(){
    cin>>n>>v;
    for(int i=1;i<=n;++i){
        cin>>cost[i]>>val[i];
    }
    f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=cost[i];j--){
            f[j]=max(f[j],f[j-cost[i]]+val[i]);
        }
    }
    cout<<f[v]<<endl;
}