#include <iostream>
#include <cstring>
using namespace std;
char s[1000101];
int n,x,y,ans;
int main(){
    cin>>s;
    n=strlen(s);
    for(int i=0;i<n;i++){
        if(s[i]=='p'){
            if(x>y){
                y++;
            }else{
                x++;
                ans--;
            }
        }else{
            if(x>y){
                y++;
                ans++;
            }else{
                x++;
            }
        }
    }
    cout<<ans;
}