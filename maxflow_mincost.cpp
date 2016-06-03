struct Flow {
    const static int MAX_EDGES = 10000;
    const static int MAX_NODES = 1000;
    const int INF = 1e9 + 50;
 
    int S = MAX_NODES - 2, D = MAX_NODES - 1;
 
    int G[MAX_NODES];
    struct Edge {
        int vec, flow, cap, cost, rev, nxt;
    };
    Edge E[MAX_EDGES];
    int edges = 0;
 
    int ParentNode[MAX_NODES], ParentEdge[MAX_NODES], Dist[MAX_NODES];
    bool InQ[MAX_NODES];
    queue<int> Q;
 
    Flow() {
        Reset();
    }
 
    void setSource(int s) {
        S = s;
    }
    void setSink(int d) {
        D = d;
    }
 
    void _addEdge(int a, int b, int cap, int cost, int rev) {
        ++edges;
        E[edges] = (Edge) {b, 0, cap, cost, rev, G[a]};
        G[a] = edges;
    }
    void AddEdge(int a, int b, int cap, int cost) {
        _addEdge(a, b, cap, cost, edges + 2);
        _addEdge(b, a, 0, -cost, edges);
    }
 
    bool Bellman() {
        memset(ParentNode, 0, sizeof(ParentNode));
 
        Dist[S] = 0;
        Q.push(S);
 
 
        while(!Q.empty()) {
            int top = Q.front();
            InQ[top] = 0;
            Q.pop();
 
            for(int i=G[top]; i; i=E[i].nxt) {
                int vec = E[i].vec;
                if(E[i].flow < E[i].cap && (ParentNode[vec] == 0 || Dist[vec] > Dist[top] + E[i].cost)) {
                    Dist[vec] = Dist[top] + E[i].cost;
                    ParentNode[vec] = top;
                    ParentEdge[vec] = i;
 
                    if(!InQ[vec]) {
                        Q.push(vec);
                        InQ[vec] = 1;
                    }
                }
            }
        }
 
        return ParentNode[D] != 0;
    }
 
    void Reset() {
        edges = 0;
        memset(G, 0, sizeof(G));
    }
 
    int MFMC() {
        int cost = 0, flow = 0;
 
        while(Bellman()) {
            int M = INF;
 
            for(int node = D; node != S; node = ParentNode[node]) {
                int ei = ParentEdge[node];
                M = min(M, E[ei].cap - E[ei].flow);
            }
 
            for(int node = D; node != S; node = ParentNode[node]) {
                int ei = ParentEdge[node],
                    ri = E[ei].rev;
 
                E[ei].flow += M;
                E[ri].flow -= M;
 
                cost += E[ei].cost * M;
            }
 
            flow += M;
        }
 
        return cost;
    }
 
};