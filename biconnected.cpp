namespace CBC {
	vector<pair<int, int>> St;
	int Parent[kMaxN], Time[kMaxN], Low[kMaxN];
	vector<int> Nodes[kMaxN];
	bool Viz[kMaxN];
	int Art[kMaxN];
	int n, timer, cbc;

	void Init(int nn) {
		n = nn;

		for(int i = 1; i <= n; ++i) {
			Parent[i] = Time[i] = Low[i] = Viz[i] = Art[i] = 0;
			Nodes[i].clear();
		}

		timer = cbc = 0;
		St.clear();
	}

	void DFS(int node) {
	    Viz[node] = 1;
	    Time[node] = ++timer;
	    Low[node] = Time[node];
	 
	    for(auto vec : G[node]) {
	        if(vec == Parent[node]) continue;
	 
	        if(!Viz[vec]) {
	            Viz[vec] = 1;
	            Parent[vec] = node;
	            St.emplace_back(node, vec);

	            DFS(vec);
	 
	            Low[node] = min(Low[node], Low[vec]);
	 
	            if(Low[vec] >= Time[node]) {
	                cbc++;
	 				
	 				while(true) {
	 					auto p = St.back();
	 					St.pop_back();

	 					Nodes[cbc].push_back(p.second);

	 					if(p.first == node)
	 						break;
	 				}
	 				
	 				Nodes[cbc].push_back(node);
	            }
	        } else if(Low[vec] < Low[node]) {
	            Low[node] = Low[vec];
	        }
	    }
	}

	void MakeArticulationPoints() {
		for(int i = 1; i <= cbc; ++i) {
			for(auto node : Nodes[i])
				Art[node] += 1;
		}

		for(int i = 1; i <= n; ++i)
			Art[i] = (Art[i] >= 2);
	}
};