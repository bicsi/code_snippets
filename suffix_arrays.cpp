struct SuffixArrays {
    const static int MAXN = 100005;

    int Sort[MAXN];
    int Class[17][MAXN];
    pair<int, int> Aux[MAXN];
    int n;
     
    void build_array(char str[], int n) {
        // Always declare twice the size
        this->n = n;

        for(int i=1; i<=n; i++)
            Sort[i] = i;
        sort(Sort+1, Sort+n+1, [](int a, int b) {return str[a] < str[b];});
        for(int i=1; i<=n; i++)
            Class[0][Sort[i]] = Class[0][Sort[i-1]] + (str[Sort[i]] != str[Sort[i-1]]);
     
        for(int i=1; (1 << i) <= (n << 1); i++) {
            for(int j=1; j<=n; j++)
                Aux[j] = {Class[i-1][j], Class[i-1][j + (1 << (i-1))]};
            sort(Sort+1, Sort+n+1, [](int a, int b) { return Aux[a] < Aux[b]; });
            for(int j=1; j<=n; j++)
                Class[i][Sort[j]] = Class[i][Sort[j-1]] + (Aux[Sort[j]] != Aux[Sort[j-1]]);
        }
    }
     
    int lcp(int i, int j) {
        int step, sol = 0;
        i = Sort[i]; j = Sort[j];
     
        for(step=0; (1<<step) <= n; step++);
        for(; step>=0; step--) {
            if(Class[step][i] == Class[step][j]) {
                sol += (1 << step);
                i += (1 << step);
                j += (1 << step);
            }
        }
        //cerr<<sol;
        return sol;
    }
};