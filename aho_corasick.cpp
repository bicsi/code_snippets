struct AhoCorasick {
    struct Node {
        int link;
        map<char, int> leg;
    };
    vector<Node> T;
    int root = 0, nodes = 1;

    AhoCorasick(int sz) : T(sz) {}

    // Adds a word to trie and returns the end node
    int AddWord(const string &word) {
        int node = root;
        for(auto c : word) {

            auto &nxt = T[node].leg[c];

            if(nxt == 0)
                nxt = nodes++;

            node = nxt;
        }

        return node;
    }

    // Advances from a node with a character (like an automaton)
    int Advance(int node, char chr) {
        while(node != -1 && T[node].leg.count(chr) == 0)
            node = T[node].link;

        if(node == -1)
            return root;

        return T[node].leg[chr];
    }

    // Builds links
    void BuildLinks() {

        queue<int> Q;
        Q.push(root);
        T[root].link = -1;

        while(!Q.empty()) {
            int node = Q.front();
            Q.pop();

            for(auto &p : T[node].leg) {
                int vec = p.second;
                char chr = p.first;

                T[vec].link = Advance(T[node].link, chr);
                Q.push(vec);
            }
        }
    }
};
