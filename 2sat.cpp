/**
 * 2SAT Solver
 *
 * Usage:
 *
 * Add edges with AddEdge(u, v)
 * where u < 0 if not |u| and u > 0 if |u|
 * (edges are of type u -> v), and call Solve().
 *
 * The answer is in TwoSAT::Sol. If there is
 * no solution, no_sol will be set to true.
 *
 * Also, keep in mind the 1-indexing of literals!
 **/
class TwoSAT {
	vector<vector<int>> G, G_T;
	vector<int> Viz;
	vector<bool> Sol, True;
	vector<int> Stack;
	bool no_sol;
	int n;

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

		Sol[node / 2] = ((node & 1) ^ 1);

		// Whatever implies false is false
		for(auto vec : G_T[node]) {
			if(!Viz[vec])
				dfs_backward(vec);
		}
	}

	int get_node(int x) {
		if (x > 0) return 2 * (x - 1) + 1;
		return 2 * (-x - 1);
	}

public:
	TwoSAT(int n) : G(2 * n), G_T(2 * n), Viz(2 * n),
		Sol(n, 0), True(2 * n, 0), n(n) {
		Stack.reserve(2 * n);
	}

	void add_edge(int a, int b) {
		a = get_node(a); b = get_node(b);
		G[a].push_back(b);
		G_T[b].push_back(a);
	}

	pair<bool, vector<bool>> solve() {
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

		return {!no_sol, Sol};
	}
};
