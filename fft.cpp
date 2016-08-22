#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 205;
const int kMaxS = (1 << 16);
const int N = kMaxS;


typedef complex<double> Complex;
const double PI = 4 * atan(1.0);

Complex AuxA[N], AuxB[N];
 
 
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
    FFT(A, AuxA, N, 1, 0);
    FFT(B, AuxB, N, 1, 0);
 
    for(int i=0; i<N; i++) {
        AuxA[i] = AuxA[i] * AuxB[i];
        AuxA[i] /= N;
    }
 
    FFT(AuxA, R, N, 1, 1);
}

int Viz[kMaxN], Size[kMaxN], Weight[kMaxN];

Complex Prob[kMaxN][kMaxS], New[kMaxS];
double A[kMaxS], Ways[kMaxN];
double NewA[kMaxS];

int n, total;

vector<int> G[kMaxN];



void dfs(int node) {
    //cerr << "At node #" << node << '\n';
    Viz[node] = 1;
    Ways[node] = 1.0;
    
    Prob[node][Weight[node]] = 1.0;

    Size[node] = Weight[node];
    

    for(auto vec : G[node]) {
        if(!Viz[vec]) {
            dfs(vec);
            Ways[node] *= (1.0f + Ways[vec]);
            
            // Probability to take vec
            double prob_skip = 1.0f / (1.0f + Ways[vec]);

            // Do FFT instead?

            //cerr << "Multiplying...\n";
            //for(int i = 0; i <= Size[node]; ++i) cerr << Prob[node][i] << " "; cerr << endl;
            //for(int i = 0; i <= Size[vec]; ++i) cerr << Prob[vec][i] << " "; cerr << endl;
            //cerr << endl;
            
            
            
            if(1LL * Size[node] * Size[vec] < 10 * N * log(N)) {
                memset(NewA, 0, sizeof(NewA));
                for(int i = 0; i <= Size[node]; ++i) {
                    for(int j = 0; j <= Size[vec]; ++j)
                        NewA[i + j] += Prob[node][i].real() * Prob[vec][j].real();
                }
                for(int i = 0; i <= Size[node] + Size[vec]; ++i)
                    New[i] = NewA[i];
            } else {
                Mul(Prob[vec], Prob[node], New);
            }
            
            //for(int i = 0; i <= Size[node] + Size[vec]; ++i)
            //    cerr << New[i] << " "; cerr << endl;
            
            
            Size[node] += Size[vec];
            for(int i = 0; i <= Size[node]; ++i)
                Prob[node][i] = prob_skip * Prob[node][i] + (1.0f - prob_skip) * New[i];
        }
    }

    //cerr << "Done node #" << node << '\n';
}

void Reset() {
    memset(Viz, 0, sizeof(Viz));
    memset(Size, 0, sizeof(Size));
    memset(Weight, 0, sizeof(Weight));
    memset(Prob, 0, sizeof(Prob));
    memset(Ways, 0, sizeof(Ways));
    memset(A, 0, sizeof(A));
    
    for(int i = 1; i <= n; ++i)
        G[i].clear();
}

int main() {
    int t;
    cin >> t;
    cerr << fixed << setprecision(2);
    while(t--) {
        cin >> n;
        Reset();
        
        int s = 0;
        for(int i = 1; i <= n; ++i) {
            cin >> Weight[i];
            s += Weight[i];
        }

        
        for(int i = 0; i <= s; ++i) {
            cin >> A[i];
        }
        
        for(int i = 2; i <= n; ++i) {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        
        dfs(1);

        //for(int i = 1; i <= n; ++i) cerr << Size[i] << " "; cerr << endl;
        
        double total = 0;
        for(int i = 1; i <= n; ++i) {
            total += Ways[i];
        }
        
        double ans = 0;
        for(int i = 1; i <= n; ++i) {
            double coef = Ways[i] / total;
            double now = 0.0;
            
            for(int j = 0; j <= Size[i]; ++j)
                now += A[j] * real(Prob[i][j]);
            ans += now * coef;
        }
        
        //for(int i = 1; i <= n; ++i, cerr << endl)
        //    for(int j = 0; j <= Size[i]; ++j)
        //        cerr << Prob[i][j] << " ";
        
        cout << fixed << setprecision(12) << ans << '\n';
    }
    return 0;
}
