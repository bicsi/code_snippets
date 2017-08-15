class SegmTree {
    vector<int> T;
    int n;

public:

    SegmTree(int n) : T(4 * n), n(n) {}

    void Update(int pos, int val) {
        for (T[pos += n] = val; pos > 1; pos /= 2)
            T[pos / 2] = max(T[pos], T[pos ^ 1]);
    }

    int Query(int b, int e) {
        int res = 0;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) res = max(res, T[b++]);
            if (e % 2) res = max(res, T[--e]);
        }
        return res;
    }
};
