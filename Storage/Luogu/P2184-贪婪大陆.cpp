#include <iostream>
using namespace std;

int n,m;
const int lim=5e4+10;
typedef long long ll;

ll arr1[lim],arr2[lim];

int lowbit(int n){
    return n&(-n);
}

void update(ll arr[],int in,int val){
    while(in<=n){
        arr[in]+=val;
        in+=lowbit(in);
    }
}

ll sum(ll arr[],int pos){
    ll ans=0;
    for(;pos;pos-=lowbit(pos)){
        ans+=arr[pos];
    }
    return ans;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1){
            update(arr1,b,1);
            update(arr2,c,1);
        }else{
            cout<<sum(arr1,c)-sum(arr2,b-1)<<endl;
        }
    }
    
}
