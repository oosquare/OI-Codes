#include<bits/stdc++.h>
#define I int
#define B bool
#define F for
#define V void
#define R return
#define CO constexpr
#define EL else
#define CT continue
#define BK break;
#define D id
#define ST std::
#define M if
CO I MN=2000+10;CO I IN=0x3f3f3f3f;struct N{V it(I n){so=0;sk=n+1;tt=1;}V lk(I x,I y,I c,I w){G[++tt]={hd[x],y,c,w};hd[x]=tt;G[++tt]={hd[y],x,0,-w};hd[y]=tt;}I S(){R so;}I T(){R sk;}ST pair<I,I>m(){I fl=0,c=0;while(s())fl+=df(so,IN,c);R{fl,c};}struct E{I n,t,c,w;};E G[MN*100];I hd[MN*5],cur[MN*5],tt;I d[MN*5];B v[MN*5];I so,sk;B s(){ST queue<I>q;F(I i=so;i<=sk;++i){d[i]=IN;v[i]=false;}q.push(so);d[so]=0;while(!q.empty()){I x=q.front();q.pop();cur[x]=hd[x];v[x]=false;F(I i=hd[x],y;y=G[i].t,i;i=G[i].n){M(G[i].c<=0||d[y]<=d[x]+G[i].w)CT;d[y]=d[x]+G[i].w;M(v[y])CT;v[y]=true;q.push(y);}}R d[sk]!=IN;}I df(I x,I in,I&c){M(x==sk)R in;I r=0;v[x]=true;F(I&i=cur[x],y;y=G[i].t,i;i=G[i].n){M(v[y]||G[i].c<=0||d[y]!=d[x]+G[i].w)CT;I f=df(y,ST min(G[i].c,in-r),c);M(f>0){G[i].c-=f;G[i^1].c+=f;c+=f*G[i].w;r+=f;M(r==in)BK}}M(r!=in)v[x]=false;R r;}};enum P{E,S,L,A,T,C};I n,m,tt[2];N G;I mt[MN][MN];CO I op[4]={2,3,0,1};CO I pc[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};CO P tp[16]={E,S,S,A,S,L,A,T,S,A,L,T,A,T,T,C};I D(I x,I y,I d=-1){R(x-1)*m+y+(d+1)*n*m;}I cl(I x,I y){R(x+y)%2;}V lk(I col,I x0,I x,I c,I w){M(col)G.lk(x0,x,c,w);EL G.lk(x,x0,c,w);}V lS(I x,I y){I s=mt[x][y];F(I i=0;i<4;++i){M(!((s>>i)&1))CT;lk(cl(x,y),D(x,y),D(x,y,i),1,0);lk(cl(x,y),D(x,y,i),D(x,y,op[i]),1,2);F(I j=0;j<4;++j){M(j==i||j==op[i])CT;lk(cl(x,y),D(x,y,i),D(x,y,j),1,1);}}}V lL(I x,I y){I s=mt[x][y];F(I i=0;i<4;++i){M(!((s>>i)&1))CT;lk(cl(x,y),D(x,y),D(x,y,i),1,0);}}V lA(I x,I y){I s=mt[x][y];F(I i=0;i<4;++i){M(!((s>>i)&1))CT;lk(cl(x,y),D(x,y),D(x,y,i),1,0);lk(cl(x,y),D(x,y,i),D(x,y,op[i]),1,1);}}V lT(I x,I y){I s=mt[x][y];I d;F(I i=0;i<4;++i){M(!((s>>i)&1)){d=i;CT;}lk(cl(x,y),D(x,y),D(x,y,i),1,0);}F(I i=0;i<4;++i){M(i==op[d])lk(cl(x,y),D(x,y,i),D(x,y,d),1,2);EL M(i!=d)lk(cl(x,y),D(x,y,i),D(x,y,d),1,1);}}V lC(I x,I y){F(I i=0;i<4;++i)lk(cl(x,y),D(x,y),D(x,y,i),1,0);}I main(){freopen("data.in","r",stdin);freopen("data.out","w",stdout);ST ios::sync_with_stdio(false);ST cin>>n>>m;F(I i=1;i<=n;++i)F(I j=1;j<=m;++j)ST cin>>mt[i][j];G.it(n*m*5);F(I i=1;i<=n;++i){F(I j=1;j<=m;++j){M(!pc[mt[i][j]])CT;tt[cl(i,j)]+=pc[mt[i][j]];M(cl(i,j))G.lk(G.S(),D(i,j),pc[mt[i][j]],0);EL G.lk(D(i,j),G.T(),pc[mt[i][j]],0);}}F(I i=1;i<=n;++i){F(I j=1;j<=m;++j){switch(tp[mt[i][j]]){case S:lS(i,j);BK case L:lL(i,j);BK case A:lA(i,j);BK case T:lT(i,j);BK case C:lC(i,j);BK default:BK}}}F(I i=1;i<=n;++i)F(I j=1;j<m;++j)lk(cl(i,j),D(i,j,1),D(i,j+1,3),1,0);F(I i=1;i<n;++i)F(I j=1;j<=m;++j)lk(cl(i,j),D(i,j,2),D(i+1,j,0),1,0);auto[f,c]=G.m();M(f==tt[0]&&tt[0]==tt[1])ST cout<<c<<ST endl;EL ST cout<<-1<<ST endl;R 0;}
