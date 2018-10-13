#include <bits/stdc++.h>

using namespace std;

const int kMod = 1e9 + 7;

struct ModInt {
    long long n;

    ModInt(long long n = 0) : n(n % kMod) {}
    ModInt operator+(const ModInt& oth) { return n + oth.n; }  
    ModInt operator-(const ModInt& oth) { return n - oth.n; }
    ModInt operator*(const ModInt& oth) { return n * oth.n; }
    long long get() { return n < 0 ? n + kMod : n; }
};

ModInt lgpow(ModInt b, int e) {
    ModInt r;
    for (r = 1; e; e /= 2, b = b * b)
        if (e % 2) r = r * b;
    return r;
}
ModInt inv(ModInt x) { return lgpow(x, kMod - 2); }

vector<ModInt> BerlekampMassey(vector<ModInt> s) {
    int n = s.size();
    vector<ModInt> C(n, 0), B(n, 0);
    C[0] = B[0] = 1;

    ModInt b = 1;
    int L = 0, m = 1;

    for (int i = 0; i < n; ++i) {
        // Calculate discrepancy
        ModInt d = s[i];
        for (int j = 1; j <= L; ++j)
            d = d + C[j] * s[i - j];

        if (d.get() == 0) { ++m; continue; }
        
        // C -= d / b * B * x^m
        auto T = C; ModInt coef = d * inv(b);
        for (int j = m; j < n; ++j)
            C[j] = C[j] - coef * B[j - m];
        
        if (2 * L > i) { ++m; continue; }
        
        L = i + 1 - L;
        B = T; b = d; m = 1;
    }

    C.resize(L + 1);
    C.erase(C.begin());
    for (auto& x : C) 
        x = ModInt(0) - x;
    return C;
}
