#include <bits/stdc++.h>
using namespace std;

struct range
{
    int l,r;
    bool operator<(const range & rhs) const {
        return r<rhs.l;
    }
};

set<range> s;
int n;
char cmd[10];

int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%s",cmd);
        if(cmd[0]=='A'){
            range rr; int ans=0;
            scanf("%d%d",&rr.l,&rr.r);
            auto it=s.find(rr);
            while(it!=s.end()){
                ++ans;
                s.erase(it);
                it=s.find(rr);
            }
            s.insert(rr);
            printf("%d\n",ans);
        }else{
            printf("%d\n",s.size());
        }
    }
}