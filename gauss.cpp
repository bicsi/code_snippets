void diag() {
    for(var step=1; step<=n; step++) {
        if(eq(A[step][step], 0.0)) {
            var i;
            for(i=step+1; i<=n && eq(A[i][step], 0); i++);
 
            if(i > n) continue;
 
            swap(A[i], A[step]);
        }
 
        for(var i=m+1; i>=step; i--) {
           A[step][i] /= A[step][step];
        }
 
        for(var i=step+1; i<=n; i++) {
            double inm = A[i][step];
            for(var j=step; j<=m+1; j++) {
                A[i][j] -= A[step][j] * inm;
            }
        }
 
    }
}
 
void findX() {
    for(var i=n; i>=1; i--) {
        double rez = A[i][m+1];
        for(var j=m; j>i; j--) {
            rez -= A[i][j]*X[j];
        }
        X[i] = rez;
    }
}