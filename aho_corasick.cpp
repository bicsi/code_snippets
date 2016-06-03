struct AhoCorasick {
 
    struct Node {
        int cnt, bad, adj, parent;
        char c;
        map<char, int> leg;
    };
    vector<Node> T;
    int root = 1, nodes = 1;

    AhoCorasick(int sz) {
        T.resize(sz);
    }

    int addWord(const string &word) {
        int node = root;
        for(auto c : word) {
            
            auto &nxt = T[node].leg[c];

            if(nxt == 0) {
                nxt = ++nodes;
                T[nodes].parent = node;
                T[nodes].c = c;
            }

            node = nxt;
        }
     
        return node;
    }
     
    queue<int> Q;
    void buildBad() {
     
        Q.push(root);
        while(!Q.empty()) {
            int node = Q.front();
            Q.pop();
     
            
            int bad = T[T[node].parent].bad;
            char c = T[node].c;
 
            while(bad && T[bad].leg.find(c) == T[bad].leg.end()) 
                bad = T[bad].bad;

            T[node].bad = (node == root) ? 0 : (bad) ? T[bad].leg[c] : root;

            for(auto p : T[node].leg)
                Q.push(p.second);
        }
    }

    void parseText(const string &text) {
        int node = root;

        for(auto c : text) {
            while(node && T[node].leg.find(c) == T[node].leg.end())
                node = T[node].bad;
            node = node ? T[node].leg[c] : root;

            // Here you go
        }
    }
};

