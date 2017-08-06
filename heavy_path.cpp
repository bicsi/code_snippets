template<typename T, typename Acc>
class SegmentTree {
    size_t dim;
    vector<T> data;
    Acc acc;

    void build(int node, const int &b, const int &e, const vector<T> &from) {
        if(e == b + 1) {
            data[node] = from[b];
        } else {
            int m = (b + e) / 2;
            build(node * 2, b, m, from);
            build(node * 2 + 1, m, e, from);
            data[node] = acc(data[node * 2], data[node * 2 + 1]);
        }
    }

    void update(int node, const int &b, const int &e, const int &pos, const T &x) {
        if(e == b + 1) {
            data[node] = x;
        } else {
            int m = (b + e) / 2;
            pos < m
                ? update(node * 2, b, m, pos, x)
                : update(node * 2 + 1, m, e, pos, x);
            data[node] = acc(data[node * 2], data[node * 2 + 1]);
        }
    }

    void query(int node, const int &b, const int &e, const int &l, const int &r) {
        if(b >= l && e <= r) {
            data[0] = b == l
                ? data[node]
                : acc(data[0], data[node]);
            return;
        }

        int m = (b + e) / 2;
        if(l < m) query(node * 2, b, m, l, r);
        if(r > m) query(node * 2 + 1, m, e, l, r);
    }

  public:
    SegmentTree(size_t dim, Acc acc = Acc()) :
        dim(dim), data(dim * 4), acc(acc) {}
    SegmentTree(const vector<T> &from, Acc acc = Acc()) :
        dim(from.size()), data(from.size() * 4), acc(acc)
    {
        build(1, 0, dim, from);
    }


    void Set(int pos, T value) {
        update(1, 0, dim, pos, value);
    }
    T Get(int pos) {
        return QueryRange(pos, pos + 1);
    }
    T QueryRange(int b, int e) {
        assert(b < e);
        query(1, 0, dim, b, e);
        return data[0];
    }
};

template<typename T, typename Acc>
struct HeavyLight {
    vector<vector<int>> G;
    vector<int> Jump, SubSize, Depth, Lin, Parent;
    bool processed;

    SegmentTree<T, Acc> st;
    Acc acc;

    HeavyLight(int n, Acc acc = Acc()) :
        G(n), Jump(n), SubSize(n), Depth(n), Lin(n), Parent(n), st(n, acc), acc(acc) {}

    void AddEdge(int a, int b) {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void Preprocess() {
        DFSSub(0, -1);
        DFSJump(0, 0);
        processed = true;
    }

    int GetLCA(int a, int b) {
        assert(processed);

        while (Jump[a] != Jump[b]) {
            if (Depth[Jump[a]] > Depth[Jump[b]])
                a = Parent[Jump[a]];
            else
                b = Parent[Jump[b]];
        }

        return Depth[a] > Depth[b] ? b : a;
    }

    void UpdateNode(int node, int value) {
        assert(processed);

        st.Set(Lin[node], value);
    }
    T QueryPath(int a, int b) {
        assert(processed);

        T ret; bool first;
        while (Jump[a] != Jump[b]) {
            if (Depth[Jump[a]] < Depth[Jump[b]])
                swap(a, b);

            T with = st.QueryRange(Lin[Jump[a]], Lin[a] + 1);
            ret = first ? with : acc(ret, with);
            a = Parent[Jump[a]];
            first = false;
        }

        if (Depth[a] < Depth[b]) swap(a, b);
        T with = st.QueryRange(Lin[b], Lin[a] + 1);
        ret = first ? with : acc(ret, with);

        return ret;
    }

  private:

    int DFSSub(int node, int par) {
        SubSize[node] = 1;
        Parent[node] = par;
        if (par != -1) {
            G[node].erase(find(G[node].begin(), G[node].end(), par));
            Depth[node] = 1 + Depth[par];
        }

        for (auto vec : G[node])
            SubSize[node] += DFSSub(vec, node);

        return SubSize[node];
    }

    int timer = 0;
    int DFSJump(int node, int jump) {
        Jump[node] = jump;
        Lin[node] = timer++;

        sort(G[node].begin(), G[node].end(), [&](int a, int b) {
            return SubSize[a] > SubSize[b];
        });

        for (auto vec : G[node])
            DFSJump(vec, vec == G[node].front() ? jump : vec);
    }
};
