class HeavyLight {
    struct Node {
        int jump, subsize, depth, lin, parent;
        vector<int> leg;
    };
    vector<Node> T;
    bool processed;

public:

    HeavyLight(int n) : T(n) {}

    void AddEdge(int a, int b) {
        T[a].leg.push_back(b);
        T[b].leg.push_back(a);
    }

    void Preprocess() {
        dfs_sub(0, -1);
        dfs_jump(0, 0);
        processed = true;
    }

    // Gets the position in the HL linearization
    int GetPosition(int node) {
        assert(processed);
        return T[node].lin;
    }

    // Gets an array of ranges of form [li...ri)
    // that correspond to the ranges you would need
    // to query in the underlying structure
    vector<pair<int, int>> GetPathRanges(int a, int b) {
        assert(processed);

        vector<pair<int, int>> ret;
        while (T[a].jump != T[b].jump) {
            if (T[T[a].jump].depth < T[T[b].jump].depth)
                swap(a, b);

            ret.emplace_back(T[T[a].jump].lin, T[a].lin + 1);
            a = T[T[a].jump].parent;
        }

        if (T[a].depth < T[b].depth) swap(a, b);
        ret.emplace_back(T[b].lin, T[a].lin + 1);

        return ret;
    }

private:

    int dfs_sub(int x, int par) {
        auto &node = T[x];
        node.subsize = 1;
        node.parent = par;

        if (par != -1) {
            node.leg.erase(find(node.leg.begin(), node.leg.end(), par));
            node.depth = 1 + T[par].depth;
        }

        for (auto vec : node.leg)
            node.subsize += dfs_sub(vec, x);

        return node.subsize;
    }

    int timer = 0;
    void dfs_jump(int x, int jump) {
        auto &node = T[x];
        node.jump = jump;
        node.lin = timer++;

        iter_swap(node.leg.begin(), max_element(node.leg.begin(), node.leg.end(),
            [&](int a, int b) { return T[a].subsize < T[b].subsize; }));

        for (auto vec : node.leg)
            dfs_jump(vec, vec == node.leg.front() ? jump : vec);
    }
};
