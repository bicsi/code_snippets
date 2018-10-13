struct CentroidDecomposer {
	int n;
	vector<set<int>> G;
	vector<int> Size;
	// Depth and parent in the centroid tree
	vector<int> CD, CP;

	CentroidDecomposer(int n) :
		n(n), G(n), Size(n), CD(n), CP(n) {}

	void AddEdge(int a, int b) {
		G[a].insert(b);
		G[b].insert(a);
	}

	int rec_size, rec_centr;
	void ComputeSizeAndCentroid(int node, int par) {
		Size[node] = 1;
		int max_size = 0;

		for(auto vec : G[node])
			if(vec != par) {
				ComputeSizeAndCentroid(vec, node);
				Size[node] += Size[vec];
				max_size = max(max_size, Size[vec]);
			}

		max_size = max(max_size, rec_size - Size[node]);
		if(2 * max_size <= rec_size)
			rec_centr = node;
	}

	void DoUsefulDFS(int node, int par, int cd) {
		Size[node] = 1;
		for(auto vec : G[node])
			if(vec != par) {
				DoUsefulDFS(vec, node, cd);
				Size[node] += Size[vec];
			}
	}

	void RecDecomp(int node, int size, int cp, int cd) {
		// node -> centroid(node)
		rec_size = size;
		ComputeSizeAndCentroid(node, -1);
		node = rec_centr;
		
		CP[node] = cp;
		CD[node] = cd;

		// You can do whichever DFS you want here
		DoUsefulDFS(node, -1, cd);

		for(auto vec : G[node]) {
			G[vec].erase(node);
			RecDecomp(vec, Size[vec], node, cd + 1);
		}
	}

	void Decompose(int root = 0) {
		RecDecomp(root, n, -1, 0);
		for(auto x : CD)
			assert(x <= __lg(n) + 1);
	}
};
