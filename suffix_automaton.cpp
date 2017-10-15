struct SuffixAutomaton {
    struct Node {
        int link, len;
        map<char, int> leg;
    };
    vector<Node> T;
    int last = 0, nodes = 1;

    SuffixAutomaton(int sz) {
        T.resize(2 * sz + 1);
        T[0].link = -1;
        T[0].len = 0;
    }

    // Adds another character to the automaton
    int ConsumeChar(char c) {
        // Add state for whole string
        int cur = nodes++;
        T[cur].len = T[last].len + 1;
        T[cur].link = 0;

        int node = last;

        // Add transitions to all suffixes which do not have one already
        while (node != -1 && !T[node].leg.count(c)) {
            T[node].leg[c] = cur;
            node = T[node].link;
        }

        if (node != -1) {
            // We found double-edge
            int old = T[node].leg[c];

            if (T[old].len == T[node].len + 1) {
                // Just set a new link
                T[cur].link = old;
            } else {
                // We have to split one edge
                int clone = nodes++;

                T[clone].leg = T[old].leg;
                T[clone].len = T[node].len + 1;
                T[clone].link = T[old].link;

                // Set the "good" links
                T[old].link = T[cur].link = clone;

                // Rewire classes pointing to old
                while (node != -1 && T[node].leg[c] == old) {
                    T[node].leg[c] = clone;
                    node = T[node].link;
                }
            }
        }

        last = cur;
        return cur;
    }
};
