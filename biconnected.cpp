namespace CBC {
	vector<pair<int, int>> St;
	int Parent[kMaxN], Disc[kMaxN], Low[kMaxN];
	vector<int> CBC[kMaxN];
	bool Viz[kMaxN], Art[kMaxN];
	int n, timer, cbc;

	void Init(int nn) {
		n = nn;

		for(int i = 1; i <= n; ++i) {
			Parent[i] = Disc[i] = Low[i] = Viz[i] = Art[i] = 0;
			CBC[i].clear();
		}

		timer = cbc = 0;
		St.clear();
	}

	void DFS(int node) {
	    Viz[node] = 1;
	    Disc[node] = ++timer;
	    Low[node] = Disc[node];
	 
	    for(vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
	        const int &vec = *it;
	        if(vec == Parent[node]) continue;
	 
	        if(!Viz[vec]) {
	            Viz[vec] = 1;
	            Parent[vec] = node;
	            St.emplace_back(node, vec);
	            DFS(vec);
	 
	            Low[node] = min(Low[node], Low[vec]);
	 
	            if(Low[vec] >= Disc[node]) {
	                cbc++;
	                Art[node] = 1;
	 
	                while(St.back() != make_pair(node, vec) ) {
	                    CBC[cbc].push_back(St.back().second);
	                    St.pop_back();
	                }
	                CBC[cbc].push_back(node);
	                CBC[cbc].push_back(vec);
	                St.pop_back();
	            }
	        } else if(Low[vec] < Low[node]) {
	            Low[node] = Low[vec];
	        }
	    }
	}

	void Start(int start) {
		if(G[start].empty()) return;
		DFS(start);

		Art[start] = 0;
		int x = G[start].back();
		for(auto y : G[start])
			if(y != x)
				Art[start] = 1;
	}
};