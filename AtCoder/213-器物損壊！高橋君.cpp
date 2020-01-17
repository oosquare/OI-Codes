#include <cstdio>
#include <algorithm>
using namespace std;
int h,w,a,b,v[505][505];
int dir[2][4]={{0,0,1,-1},{1,-1,0,0}};
bool ans;
char m[505][505];

bool dfs(int y,int x,int f){
    if(y<0||y>=h||x<0||x>=w||(v[y][x]&&f>=v[y][x]))return false;
    if(m[y][x]=='g'){return true;}
    if(m[y][x]=='#'){if(f==3)return false;f++;}
    v[y][x]=f;
    for(int i=0;i<4;i++)
        if(dfs(y+dir[0][i],x+dir[1][i],f)){
        	return true;
		}
	return false;
}

int main(){
    scanf("%d%d",&h,&w);
    for(int i=0;i<h;i++){
        scanf("\n");
        for(int j=0;j<w;j++){
            scanf("%c",&m[i][j]);
            if(m[i][j]=='s')a=i,b=j;
        }
    }
    ans=dfs(a,b,1);
    if(ans){
    	printf("YES\n");
	}else{
		printf("NO\n");
	}
}