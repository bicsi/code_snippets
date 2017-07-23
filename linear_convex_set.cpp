class LinearConvexSet {
    using T = long long;

    struct SetElem {
        T a, b;
        mutable const SetElem* next = nullptr;

        bool is_query;

        SetElem(T query_x) : b(query_x), is_query(true) {}
        SetElem(T a, T b) : a(a), b(b), is_query(false) {}

        T eval(T x) const { return a * x + b; }

        bool operator< (const SetElem &rhs) const {
            assert(!rhs.is_query);
            if (is_query) {
                if (rhs.next == nullptr) return true;
                return rhs.eval(b) > rhs.next->eval(b);
            } else return (a != rhs.a) ? a < rhs.a : b < rhs.b;
        }
    };

    set<SetElem> data;

    bool is_bad(set<SetElem>::iterator it) {
        if (it == data.begin() || next(it) == data.end())
            return false;

        auto prv = prev(it), nxt = next(it);
        return (it->b - prv->b) * (nxt->a - it->a)
            <= (it->b - nxt->b) * (prv->a - it->a);
    }

    void erase(set<SetElem>::iterator it) {
        if (it != data.begin())
            prev(it)->next = it->next;
        data.erase(it);
    }
public:
    void Insert(T slope, T intercept) {
        auto p = data.insert(SetElem(slope, intercept));
        if (!p.second) return;

        auto it = p.first;
        if (it != data.begin()) prev(it)->next = &(*it);
        if (next(it) != data.end()) it->next = &(*next(it));

        if (is_bad(it)) erase(it);
        else {
            while (it != data.begin()) {
                auto prv = prev(it);
                if (is_bad(prv)) {
                    erase(prv);
                } else break;
            }
            while (next(it) != data.end()) {
                auto nxt = next(it);
                if (is_bad(nxt)) {
                    erase(nxt);
                } else break;
            }
        }
    }

    T EvaluateMax(T x) {
        SetElem ret(x);
        auto it = data.upper_bound(ret);
        return it->eval(x);
    }
};
