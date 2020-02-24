#include <bits/stdc++.h>
using namespace std;
int f[1001],w[1001],d[1001];
int n,v;
int main(){
    cin>>n>>v;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>d[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=w[i];j<=v;j++){
            f[j]=max(f[j],f[j-w[i]]+d[i]);
        }
    }
    cout<<f[v]<<endl;
}