#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
 
const int MAX_N=100100;
 
int n;
 
int per(int nod) {
    if(nod>n) {
        return nod-n;
    }
    return nod+n;
}
 
vector<int> A[2*MAX_N];
vector<int> B[2*MAX_N];
 
int st[2*MAX_N];
bool viz[2*MAX_N];
bool val[2*MAX_N];
 
void dfs1(int nod) {
    viz[nod]=true;
    for(vector<int>::iterator it=A[nod].begin(); it!=A[nod].end(); it++) {
        if(!viz[*it]) {
            dfs1(*it);
        }
    }
    st[++st[0]]=nod;
    //printf("%d ",nod>n?-(nod-n):nod);
}
 
bool no_sol=false;
void dfs2(int nod) {
    //printf("%d ",nod>n?-(nod-n):nod);
    if(val[nod]) {
        no_sol=true;
    }
    viz[nod]=true;
    val[per(nod)]=true;
    for(vector<int>::iterator it=B[nod].begin(); it!=B[nod].end(); it++) {
        if(!viz[*it]) {
            dfs2(*it);
        }
    }
}
 
int main() {
    freopen("2sat.in","r",stdin);
    freopen("2sat.out","w",stdout);
     
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) {
        int a,b;
        scanf("%d%d",&a,&b);
         
        if(a<0) {
            a=n-a;
        }
        if(b<0) {
            b=n-b;
        }
 
        A[per(a)].push_back(b);
        A[per(b)].push_back(a);
        B[b].push_back(per(a));
        B[a].push_back(per(b));
    }
 
    for(int i=1;i<=2*n;i++) {
        if(!viz[i]) {
            dfs1(i);
        }
    }
    memset(viz,0,sizeof(viz));
    for(int i=2*n;i>=1;i--) {
        if(!viz[st[i]]&&!viz[per(st[i])]) {
            dfs2(st[i]);
        }
    }
 
    if(no_sol) {
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;i++) {
        printf("%d ",val[i]);
    }
 
    return 0;
}