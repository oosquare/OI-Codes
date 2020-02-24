#include <bits/stdc++.h>
using namespace std;
int n,m,v[101],w[101],s[101],f[101];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>v[i]>>w[i]>>s[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=v[i];j--){
            for(int k=1;k<=s[i];k++){
                if(j-k*v[i]<0)break;
                f[j]=max(f[j],f[j-k*v[i]]+k*w[i]);
            }
        }
    }
    cout<<f[m]<<endl;
}