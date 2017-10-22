struct PalTree {
    struct Node {
        map<char, int> leg;
        int link, len, cnt;
    };
    vector<Node> T;
    int nodes = 2;

    PalTree(string str) : T(str.size() + 2) {
        T[1].link = T[1].len = 0;
        T[0].link = T[0].len = -1;

        int last = 0;
        for (int i = 0; i < (int)str.size(); ++i) {
            char now = str[i];
            
            int node = last;
            while (now != str[i - T[node].len - 1])
                node = T[node].link;
            
            if (T[node].leg.count(now)) {
                node = T[node].leg[now];
                T[node].cnt += 1;
                last = node;
                continue;
            }


            int cur = nodes++;
            T[cur].len = T[node].len + 2;
            T[node].leg[now] = cur;
            
            int link = T[node].link;
            while (link != -1) {
                if (now == str[i - T[link].len - 1] && T[link].leg.count(now)) {
                    link = T[link].leg[now];
                    break;
                }
                link = T[link].link;
            }
            if (link <= 0) link = 1;

            T[cur].link = link;
            T[cur].cnt = 1;

            last = cur;
        }

        for (int node = nodes - 1; node > 0; --node) {
            T[T[node].link].cnt += T[node].cnt;
        }
    }
};
