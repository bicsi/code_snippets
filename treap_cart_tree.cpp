struct TreapCartesian {
 
    struct node {
        int sz, l, r, p, val;
        bool rev;
    };
    node T[250005];
    int nodes = 0, root = 0;
 
    #define getDelta(x) T[T[x].l].sz + 1
 
    void lazy_update(int x) {
        if(x && T[x].rev) {
            swap(T[x].l, T[x].r);
            T[x].rev = 0;
            T[T[x].l].rev ^= 1;
            T[T[x].r].rev ^= 1;
        }
    }
 
    void update(int x) {
        if(x) {
            T[x].sz = T[T[x].l].sz + T[T[x].r].sz + 1;
        }
    }
 
    void split(int x, int pos, int &l, int &r) {
        lazy_update(x);
 
        int delta = getDelta(x);
 
        if(x == 0) l = r = 0;
        else if(pos <= delta)
            split(T[x].l, pos, l, T[x].l), r = x;
        else
            split(T[x].r, pos - delta, T[x].r, r), l = x;
 
        update(x);
    }
 
    void join(int &x, int l, int r) {
        lazy_update(l);
        lazy_update(r);
 
        if(l == 0 || r == 0)
            x = (l) ? l : r;
        else if(T[l].p > T[r].p)
            join(T[l].r, T[l].r, r), x = l;
        else
            join(T[r].l, l, T[r].l), x = r;
 
        update(x);
    }
 
    void add(int &x, int pos) {
        lazy_update(x);
 
        if(x == 0) x = nodes;
        else if(T[x].p > T[nodes].p) {
            int delta = getDelta(x);
 
            if(pos <= delta)
                add(T[x].l, pos);
            else
                add(T[x].r, pos - delta);
        } else {
            split(x, pos, T[nodes].l, T[nodes].r);
            x = nodes;
        }
 
        update(x);
    }
    
    void insert(int pos, int val) {
        ++nodes;
        T[nodes].val = val;
        T[nodes].p = rand();
 
        add(root, pos);
    }
 
    void reverse(int a, int b) {
        int x, y, z;
 
        split(root, b+1, y, z);
        split(y, a, x, y);
 
        T[y].rev ^= 1;
 
        join(x, x, y);
        join(root, x, z);
    }
 
    void erase(int a, int b) {
        int x, y, z;
 
        split(root, b+1, y, z);
        split(y, a, x, y);
 
        join(root, x, z);
    }
 
    int fnd(int x, int pos) {
        lazy_update(x);
 
        int delta = getDelta(x);
        if(pos == delta) return T[x].val;
        if(pos < delta) return fnd(T[x].l, pos);
        return fnd(T[x].r, pos - delta);
    }
    int find(int pos) {
        return fnd(root, pos);
    }
 
    void dump(int x) {
        if(x) {
            lazy_update(x);
            dump(T[x].l);
            fout<<T[x].val<<" ";
            dump(T[x].r);
        }
    }
};