class Treap {

    int key, subsize;
    unsigned priority;
    Treap *left, *right;

    static Treap *nill;
    static bool initialized;

    Treap* pull() {
        subsize = (this != nill) + left->subsize + right->subsize;
        return this;
    }

    static void initialize() {
        if (initialized) return;
        initialized = true;

        nill->left = nill->right = nill;
        nill->priority = 0;
        nill->subsize = 0;
    }

    int get_key();

    Treap() {}

public:
    static Treap* Nill() { initialize(); return nill;  }
    static Treap* Singleton(int key) {
        initialize();
        Treap* ret = new Treap();
        ret->key = key;
        ret->priority = rand() * RAND_MAX + rand();
        ret->left = ret->right = nill;
        return ret->pull();
    }

    pair<Treap*, Treap*> Split(int key) {
        if (this == nill) return {nill, nill};

        if (get_key() > key) {
            auto p = left->Split(key);
            left = p.second;
            p.second = this->pull();
            return p;
        } else {
            auto p = right->Split(key);
            right = p.first;
            p.first = this->pull();
            return p;
        }
    }

    Treap* Join(Treap *rhs) {
        if (this == nill) return rhs;
        if (rhs == nill) return this;

        if (priority > rhs->priority) {
            right = right->Join(rhs);
            return this->pull();
        } else {
            rhs->left = Join(rhs->left);
            return rhs->pull();
        }
    }

    bool Find(int key) {
        if (this == nill) return false;
        if (get_key() == key) return true;
        if (get_key() > key) return left->Find(key);
        return right->Find(key);
    }

    void Dump() {
        if (this == nill) return;
        left->Dump();
        cerr << get_key() << " ";
        right->Dump();
    }
};
Treap* Treap::nill = new Treap();
bool Treap::initialized = false;

int Treap::get_key() {
    return key;
    // return left->subsize + 1;
}

Treap* Insert(Treap *root, int key) {
    Treap* single = Treap::Singleton(key);
    auto p = root->Split(key);
    return p.first->Join(single)->Join(p.second);
}
Treap* Erase(Treap *root, int key) {
    auto p = root->Split(key);
    auto q = p.second->Split(key + 1);
    return p.first->Join(q.second);
}
