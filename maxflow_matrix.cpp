namespace MaxFlow {
    const int MAX_NODES = 1005;
 
    int SRC = 0, DEST = 1;
    int nodes = 2;
 
    int F[MAX_NODES][MAX_NODES], C[MAX_NODES][MAX_NODES];
    int Parent[MAX_NODES];
    queue<int> Q;
    vector<int> G[MAX_NODES];
 
    void init(int n, int s = -1, int d = -1) {
        if(s == -1) s = ++n;
        if(d == -1) d = ++n;
 
        SRC = s; DEST = d;
        nodes = n;
 
        for(int i=1; i<=nodes; i++) {
            for(auto vec : G[i]) {
                C[i][vec] = F[i][vec] = 0;
            }
            G[i].clear();
        }
    }
 
    void addEdge(int a, int b, int cap) {
        G[a].push_back(b);
        G[b].push_back(a);
        C[a][b] += cap;
    }
 
    bool bfs() {
        memset(Parent, 0, sizeof(Parent));
        Parent[SRC] = -1;
        Q.push(SRC);
 
        while(!Q.empty()) {
            int node = Q.front();
            Q.pop();
 
            for(auto vec : G[node]) {
                if(!Parent[vec] && F[node][vec] < C[node][vec]) {
                    Parent[vec] = node;
                    Q.push(vec);
                }
            }
        }
 
        return Parent[DEST] != 0;
    }
 
 
    int maxFlow() {
        int flow = 0;
        while(bfs()) {
            for(auto x : G[DEST]) {
                if(Parent[x] == 0) continue;
 
                int M = C[x][DEST] - F[x][DEST];
                for(int node = x; node != SRC; node = Parent[node]) {
                    M = min(M, C[Parent[node]][node] - F[Parent[node]][node]);
                }
 
                F[x][DEST] += M; F[DEST][x] -= M;
                for(int node = x; node != SRC; node = Parent[node]) {
                    F[Parent[node]][node] += M;
                    F[node][Parent[node]] -= M;
                }
 
                flow += M;
            }
        }
 
        return flow;
    }
};