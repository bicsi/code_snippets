class FFTSolver {
    using Complex = complex<double>;
    const double kPi = 4.0 * atan(1.0);

    int __lg(int n) { return n == 1 ? 0 : 1 + __lg(n / 2);  }

    int rev_bit(int num, int lg) {
        int ret = 0;
        for (int i = 0; i < lg; ++i)
            if (num & (1 << i))
                ret |= (1 << (lg - i - 1));
        return ret;
    }

    vector<Complex> fft(vector<Complex> V, bool invert) {
        int n = V.size(), lg = __lg(n);

        for (int i = 0; i < n; ++i) {
            int rev = rev_bit(i, lg);
            if (i < rev)
              swap(V[i], V[rev]);
        }

        for (int step = 2; step <= n; step *= 2) {
            const double ang = 2 * kPi / step;
            Complex eps(cos(ang), sin(ang));
            if (invert) eps = conj(eps);

            for (int i = 0; i < n; i += step) {
                Complex w = 1;
                for (int a = i, b = i + step / 2; b < i + step; ++a, ++b) {
                    Complex aux = w * V[b];
                    V[b] = V[a] - aux;
                    V[a] = V[a] + aux;
                    w *= eps;
                }
            }
        }

        return V;
    }

    vector<Complex> transform(vector<Complex> V) {
        int n = V.size();
        vector<Complex> ret(n);
        Complex div_x = Complex(0, 1) * (4.0 * n);

        for (int i = 0; i < n; ++i) {
            int j = (n - i) % n;
            ret[i] = (V[i] + conj(V[j]))
                * (V[i] - conj(V[j]))
                / div_x;
        }

        return ret;
    }

  public:
    vector<int> Multiply(vector<int> A, vector<int> B) {
        int n = A.size() + B.size() - 1;
        vector<int> ret(n);
        while (n != (n & -n)) ++n;

        A.resize(n); B.resize(n);
        vector<Complex> V(n);
        for (int i = 0; i < n; ++i) {
            V[i] = Complex(A[i], B[i]);
        }

        V = fft(V, false);
        V = transform(V);
        V = fft(V, true);

        for (int i = 0; i < (int)ret.size(); ++i)
            ret[i] = round(real(V[i]));
        return ret;
    }
};

