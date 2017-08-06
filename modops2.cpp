/**
 * Implementation of encapsulated modulo operations
 *
 * Recommended usage: using MI = ModInt<MOD_WANTED>
 * Intialize: MI my_mod_int(100)
 * Get underlying integer with my_mod_int.get()
 *
 * To use factorials and combinatorics, do:
 *  MI::build_factorials(MAX_VALUE)
 * and get computations with:
 *  MI::get_fact(n)
 *  MI::get_comb(n, k)
 **/
template<int KMod>
struct ModInt {
private:
    int m_data;
    static vector<ModInt<KMod>> facts, i_facts;

public:
    ModInt(int x = 0) : m_data(x % KMod) {}
    ModInt(long long x) : m_data(x % KMod) {}

    int get() {
        int ret = m_data;
        if (ret < 0) ret += KMod;
        return ret;
    }

    ModInt pow(int e) {
        ModInt r(1), b(m_data);
        while (e) {
            if (e % 2) r = r * b;
            b = b * b;
            e /= 2;
        }
        return r;
    }
    ModInt inv() {
        assert(m_data != 0);
        return this->pow(KMod - 2);
    }

    ModInt operator+(const ModInt &oth) { return ModInt(m_data + oth.m_data); }
    ModInt operator-(const ModInt &oth) { return ModInt(m_data - oth.m_data); }
    ModInt operator*(const ModInt &oth) { return ModInt(1LL * m_data * oth.m_data); }
    ModInt operator/(const ModInt &oth) { return *this * oth.inv(); }

    static void build_factorials(int maxx) {
        facts.resize(maxx + 1);
        i_facts.resize(maxx + 1);

        facts[0] = 1;
        for (int i = 1; i <= maxx; ++i)
            facts[i] = facts[i - 1] * ModInt(i);

        i_facts[maxx] = facts[maxx].inv();
        for (int i = maxx - 1; i >= 0; --i)
            i_facts[i] = i_facts[i + 1] * ModInt(i + 1);
    }

    static ModInt get_fact(int n) {
        assert(n < (int)facts.size());
        return facts[n];
    }

    static ModInt get_comb(int n, int k) {
        return get_fact(n) * i_facts[k] * i_facts[n - k];
    }
};
template<int KMod> vector<ModInt<KMod>> ModInt<KMod>::facts;
template<int KMod> vector<ModInt<KMod>> ModInt<KMod>::i_facts;

using MI = ModInt<(int)(1e9 + 7)>;
