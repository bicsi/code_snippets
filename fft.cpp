typedef complex<double> Complex;
const double PI = 4 * atan(1.0);

const int N = (1 << 16);
Complex P[N], Q[N], R[N];

void FFT(Complex In[], Complex Out[], int n, int step, bool r) {
    if(n == 1) {
        Out[0] = In[0];
    } else {
        FFT(In, Out, n/2, step*2, r);
        FFT(In+step, Out+n/2, n/2, step*2, r);

        Complex eps(cos(2*PI/n), sin(2*PI/n)),
                w(1, 0);
        if(r) eps = conj(eps);

        for(int i=0; i<n/2; i++) {
            Complex aux = w * Out[i+n/2];
            Out[i+n/2] = Out[i] - aux;
            Out[i] = Out[i] + aux;
            w *= eps;
        }
    }
}



void Mul(Complex A[], Complex B[], Complex R[]) {
    FFT(A, R, N, 1, 0);
    FFT(B, A, N, 1, 0);

    for(int i = 0; i < N; ++i) {
        B[i] = A[i] * R[i];
        B[i] /= N;
    }

    FFT(B, R, N, 1, 1);
}
