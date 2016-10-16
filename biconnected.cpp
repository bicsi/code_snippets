namespace CBC {
	vector<int> Stack;
	int Depth[kMaxN], Time[kMaxN], Low[kMaxN];
	vector<int> Nodes[kMaxN];
	int Art[kMaxN];
	int n, cbc;

	void Init(int nn) {
		n = nn;

		for(int i = 1; i <= n; ++i) {
			Time[i] = Low[i] = Art[i] = 0;
			Nodes[i].clear();
		}

		cbc = 0;
		Stack.clear();
	}

	void DFS(int node) {
		static int timer;

		Stack.push_back(node);
		Low[node] = Time[node] = ++timer;

		for(auto vec : G[node]) {
			if(!Time[vec]) {
				Depth[vec] = Depth[node] + 1;
				DFS(vec);
				Low[node] = min(Low[node], Low[vec]);

				if(Low[vec] >= Time[node]) {
					auto &To = Nodes[++cbc];
					do {
						To.push_back(Stack.back());
						Stack.pop_back();
					} while(To.back() != vec);
					To.push_back(node);
				}
			} else if(Depth[vec] < Depth[node] - 1) {
				Low[node] = min(Low[node], Time[vec]);
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