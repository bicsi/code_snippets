struct ETT {
    struct Node {
        int pri;
        int l = 0, r = 0;
        int sz = 0, par = 0;
        Node(int pri = 0) : pri(pri) {}
    };
    int n, m = 0;
    vector<map<int, int>> G;
    vector<Node> T;
    
    ETT(int n) : n(n), G(n), T(1) {}
 
    int pull(int node) {
        if (node == 0) return node;
        T[node].sz = 1 + T[T[node].l].sz + T[T[node].r].sz;
        T[T[node].l].par = T[T[node].r].par = node;
        return node;
    }
    
    int join(int l, int r) {
        if (l == 0 || r == 0) return l + r;
        if (T[l].pri > T[r].pri) {
            T[l].r = join(T[l].r, r);
            return pull(l);
        } else {
            T[r].l = join(l, T[r].l);
            return pull(r);
        }
    }
 
    pair<int, int> expose(int node) {
        int l = T[node].l, r = T[node].r;
        T[node].l = T[node].r = 0; 
        pull(node);
        while (T[node].par) {
            int par = T[node].par;
            T[node].par = 0;
            if (T[par].l == node) {
                T[par].l = r;
                r = pull(par);
            } else {
                assert(T[par].r == node);
                T[par].r = l;
                l = pull(par);
            }
            node = par;
        }
        T[l].par = T[r].par = 0;
        return {l, r};
    }
 
    int reroot(int node) {
        if (G[node].empty()) return 0;
        int ret = G[node].begin()->second;
        int l, r; tie(l, r) = expose(ret);
        ret = join(ret, r);
        ret = join(ret, l);
        return ret;
    }
 
    int add_edge(int a, int b) {
        int ret = T.size();
        G[a][b] = ret;
        T.emplace_back(rand());
        return pull(ret);
    }
 
    void Link(int a, int b) {
        int na = reroot(a), nb = reroot(b);
        int ab = add_edge(a, b), ba = add_edge(b, a);
        na = join(na, ab);
        na = join(na, nb);
        na = join(na, ba);
    }
    void Cut(int a, int b) {
        int ab = G[a][b], ba = G[b][a];
        reroot(a);
        join(expose(ab).first, expose(ba).second);
        G[a].erase(b);
        G[b].erase(a);
    }
    int Size(int node) { return 1 + T[reroot(node)].sz / 2; }
};