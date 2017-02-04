template<typename T, typename Acc>
class SegmentTree {
	size_t dim;
	vector<T> data;
	Acc acc;

	void build(int node, const int &b, const int &e, const vector<T> &from) {
		if(e == b + 1) {
			data[node] = from[b];
		} else {
			int m = (b + e) / 2;
			build(node * 2, b, m, from);
			build(node * 2 + 1, m, e, from);
			data[node] = acc(data[node * 2], data[node * 2 + 1]);
		}
	}

	void update(int node, const int &b, const int &e, const int &pos, const T &x) {
		if(e == b + 1) {
			data[node] = x;
		} else {
			int m = (b + e) / 2;
			pos < m
				? update(node * 2, b, m, pos, x)
				: update(node * 2 + 1, m, e, pos, x);
			data[node] = acc(data[node * 2], data[node * 2 + 1]);
		}
	}

	void query(int node, const int &b, const int &e, const int &l, const int &r) {
		if(b >= l && e <= r) {
			data[0] = b == l 
				? data[node] 
				: acc(data[0], data[node]);
			return;
		}

		int m = (b + e) / 2;
		if(l < m) query(node * 2, b, m, l, r);
		if(r > m) query(node * 2 + 1, m, e, l, r);
	}

  public:
	SegmentTree(size_t dim, Acc acc = Acc()) : 
		dim(dim), data(dim * 4), acc(acc) {}
	SegmentTree(const vector<T> &from, Acc acc = Acc()) :
		dim(from.size()), data(from.size() * 4), acc(acc)
	{
		build(1, 0, dim, from);
	}

	
	void Set(int pos, T value) {
		update(1, 0, dim, pos, value);
	}
	T Get(int pos) {
		return QueryRange(pos, pos + 1);
	}
	T QueryRange(int b, int e) {
		assert(b < e);
		query(1, 0, dim, b, e);
		return data[0];
	}
};