// Strongly connected components decomposition algorithm
// 
// Usage: 
// Initialize with constructor as the number of nodes
// and add edges accordingly with the AddEdge(u, v) method.
// Then just run Reduce()
//
// ATTENTION: The reduced DAG may contain duplicate edges

struct SCCWrapper {

	int n;
	vector<vector<int>> G, G_T;
	vector<bool> Viz;
	vector<int> Stack;


	vector<int> SCC;           // SCC[i] gives the scc id of node i
	vector<vector<int>> Nodes; // Nodes[i] is the list of nodes in scc i
	vector<vector<int>> G_R;   // The reduced DAG (MAY CONTAIN DUPLICATE EDGES)
	int scc;                   // Strongly connected component count

	SCCWrapper(int n) : n(n), Viz(n), G(n), G_T(n), SCC(n) {
		Stack.reserve(n);
		scc = 0;
	};

	void AddEdge(int a, int b) {
		G[a].push_back(b);
		G_T[b].push_back(a);
	}

	void dfs_forward(int node) {
		Viz[node] = true;
		for(auto vec : G[node]) {
			if(!Viz[vec])
				dfs_forward(vec);
		}
		Stack.push_back(node);
	}

	void dfs_backward(int node) {
		Viz[node] = true;
		SCC[node] = scc;
		Nodes[scc].push_back(node);

		for(auto vec : G_T[node]) {
			if(!Viz[vec])
				dfs_backward(vec);
		}
	}

	void Reduce() {
		fill(Viz.begin(), Viz.end(), 0);
		for(int i = 0; i < n; ++i)
			if(!Viz[i])
				dfs_forward(i);

		assert(Stack.size() == n);

		fill(Viz.begin(), Viz.end(), 0);
		for(int i = n - 1; i >= 0; --i)
			if(!Viz[Stack[i]]) {
				Nodes.push_back(vector<int>());
				dfs_backward(Stack[i]);
				++scc;
			}

		G_R.resize(scc);
		for(int i = 0; i < n; ++i) {
			for(auto vec : G[i])
				G_R[SCC[i]].push_back(SCC[vec]);
		}
	}

};

