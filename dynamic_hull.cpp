template<typename T>
struct DynamicHull { 
 
    typedef pair<T, T> Point;
    #define x first
    #define y second
    #define det(A, B, C) 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x)
 
 
    set<Point> Up, Dw;
    set<Point>::iterator aux, cur, pred, succ;
 
    static bool bad(set<Point> &Set, set<Point>::iterator it) {
        if(it == Set.begin()) return false;
        if(++it == Set.end()) return false;
 
        auto C = *it--, B = *it--, A = *it;
        return det(A, B, C) <= 0;
    }
 
    void chk_succ(set<Point> &Set) {
        succ = cur; succ++;
        if(succ == Set.end()) return;
 
        while(bad(Set, succ))
            Set.erase(aux = succ++);
    }
 
    void chk_pred(set<Point> &Set) {
        if(cur == Set.begin()) return;
        pred = cur; pred--;
 
        while(bad(Set, pred))
            Set.erase(aux = pred--);
    }
 
    void ins(Point P, set<Point> &Set) {
 
        cur = Set.insert(P).first;
        if(Set.size() <= 2) return;
        if(bad(Set, cur)) { Set.erase(cur); return; }
 
        chk_pred(Set);
        chk_succ(Set);
    }
 
    void insertPoint(T a, T b) {
        ins(Point(a, b), Up);
        ins(Point(-a, -b), Dw);
    }
 
    #undef first
    #undef second
    #undef det
};
