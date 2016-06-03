
#define MAXN 10001
 
int L[MAXN], R[MAXN];
bool Viz[MAXN];
vector<int> G[MAXN];
 
bool match(int i) {
    if(Viz[i]) return false;
    Viz[i] = 1;
 
    for(auto vec : G[i]) {
        if(!R[vec]) {
            L[i] = vec;
            R[vec] = i;
            return true;
        }
    }
 
    for(auto vec : G[i]) {
        if(match(R[vec])) {
            L[i] = vec;
            R[vec] = i;
            return true;
        }
    }
    return false;
 
}
 
 
void solve() {
    bool ok = 1;
 
    while(ok) {
        ok = 0;
 
        memset(Viz, 0, sizeof(Viz));
 
        for(int i=1; i<=n; i++) {
            if(!L[i])
                ok |= match(i);
        }
    }
}