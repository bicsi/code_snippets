//
// 2SAT Solver
//
// Usage:
//
// Add edges with AddEdge(u, xu, v, xv)
// where xu == 1 if u and xu == 0 if not u.
// (edges are of type u -> v), and call Solve().
//
// The answer is in TwoSAT::Sol. If there is
// no solution, no_sol will be set to true.
// 
// Also, keep in mind the 0-indexing of literals!
//

struct TwoSAT {

	vector<vector<int>> G, G_T;
	vector<int> Viz;
	vector<bool> Sol, True;
	vector<int> Stack;
	bool no_sol;
	int n;

	TwoSAT(int n) : n(n), G(2 * n), G_T(2 * n), Viz(2 * n), 
		Sol(n, 0), True(2 * n, 0) {

		Stack.reserve(2 * n);
	}

	void AddEdge(int a, bool pa, int b, bool pb) {
		G[2 * a + pa].push_back(2 * b + pb);
		G_T[2 * b + pb].push_back(2 * a + pa);
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

		// Set node's truth value to false		
		if(True[node])
			no_sol = true;
		Viz[node] = true;
		True[node ^ 1] = true;

		Sol[node / 2] = (node & 1 ^ 1);
		
		// Whatever implies false is false
		for(auto vec : G_T[node]) {
			if(!Viz[vec])
				dfs_backward(vec);
		}
	}

	void Solve() {
		fill(Viz.begin(), Viz.end(), 0);
		for(int i = 0; i < 2 * n; ++i) {
			if(!Viz[i])
				dfs_forward(i);
		}

		no_sol = false;
		fill(Viz.begin(), Viz.end(), 0);
		for(int i = 2 * n - 1; i >= 0; --i) {
			if(!Viz[Stack[i]] && !Viz[Stack[i] ^ 1])
				dfs_backward(Stack[i]);
		}
	}
};



