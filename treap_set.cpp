

namespace TreapSet { 
    
    struct Node {
        int l, r, k, sz;
    };
    Node T[1000005];
    int root = 0, nodes = 0;
     
    void update(int a) {
        if(a) T[a].sz = T[T[a].l].sz + T[T[a].r].sz + 1
    }
     
    void split(int root, int k, int &l, int &r) {
        if(root == 0) l = r = 0;
        else {
            if(T[root].k >= k) {
                split(T[root].l, k, l, T[root].l);
                r = root;
            } else {
                split(T[root].r, k, T[root].r, r);
                l = root;
            }
        }
     
        update(root);
    }
     
    void join(int l, int r, int &root) {
        if(l == 0 || r == 0) root = l + r;
        else {
            if(rand() % (T[l].sz + T[r].sz) < T[l].sz) {
                join(l, T[r].l, T[r].l);
                root = r;
            } else {
                join(T[l].r, r, T[l].r);
                root = l;
            }
        }
     
        update(root);
    }
     
    void ins(int &root, int k) {
        if(root == 0 || rand() % T[root].sz == 0) {
            ++nodes;
            T[nodes].k = k;
            split(root, k, T[nodes].l, T[nodes].r);
            root = nodes;
        } else {
            if(T[root].k >= k) ins(T[root].l, k);
            else ins(T[root].r, k);
        }
     
        update(root);
    }
     
    void ers(int &root, int k) {
        if(root == 0) return;
        if(T[root].k == k) {
            join(T[root].l, T[root].r, root);
        } else {
            if(T[root].k > k) ers(T[root].l, k);
            else ers(T[root].r, k);
        }
     
        update(root);
    }
     
    int fnd(int &root, int k) {
        if(root == 0) return 0;
        if(T[root].k == k) return root;
        if(T[root].k > k) return fnd(T[root].l, k);
        return fnd(T[root].r, k);
    }
     
    void dump(int node) {
        if(node == 0) return;
        dump(T[node].l);
        cerr << T[node].k << " ";
        dump(T[node].r);
    }

};