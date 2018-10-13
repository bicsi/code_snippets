namespace Treap {
    struct Node {
        int key, priority;
        int left, right, lazy;
        int subsize;
    };
    vector<Node> T(1);

    int pull(int node) {
        if (node == 0) return 0;

        const int& left = T[node].left;
        const int& right = T[node].right;

        T[node].subsize = T[left].subsize + T[right].subsize + 1;
        return node;
    }

    void push(int node) {
        int& lazy = T[node].lazy;
        if (node == 0 or lazy == 0) return;

        T[T[node].left].lazy += lazy;
        T[T[node].right].lazy += lazy;
        lazy = 0;
    }

    // Splits into < key and >= key
    pair<int, int> Split(int node, int key) {
        push(node);
        if (node == 0) return {0, 0};

        int l, r;
        if (T[node].key < key) {
            tie(l, r) = Split(T[node].right, key);
            T[node].right = l;
            return {pull(node), r};
        } else {
            tie(l, r) = Split(T[node].left, key);
            T[node].left = r;
            return {l, pull(node)};
        }
    }

    int Join(int node1, int node2) {
        push(node1); push(node2);
        if (!node1) return node2;
        if (!node2) return node1;

        if (T[node1].priority > T[node2].priority) {
            T[node1].right = Join(T[node1].right, node2);
            return pull(node1);
        } else {
            T[node2].left = Join(node1, T[node2].left);
            return pull(node2);
        }
    }

    int Single(int key) {
        int node = T.size();
        T.push_back(Node{key, rand(), 0, 0, 0});
        return pull(node);
    }
}
