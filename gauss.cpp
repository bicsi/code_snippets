namespace Gauss {
    // Transforms a matrix into its row echelon form
    // Returns a vector of pivots (for each variable)
    // or -1 if free variable
    vector<int> ToRowEchelon(vector<vector<double>> &M) {
        int cons = M.size(), vars = M[0].size() - 1;
        vector<int> pivot(vars, -1);

        int cur = 0;
        for (int var = 0; var < vars; ++var) {
            if (cur >= cons) continue;
          
            for (int con = cur + 1; con < cons; ++con)
                if(M[con][var] > M[cur][var])
                    swap(M[con], M[cur]);
          
          if (abs(M[cur][var]) > kEps) {
                pivot[var] = cur;
                double aux = M[cur][var];

                for (int i = 0; i <= vars; ++i)
                    M[cur][i] /= aux;

                for (int con = 0; con < cons; ++con) {
                    if (con != cur) {
                        double mul = M[con][var];
                        for (int i = 0; i <= vars; ++i) {
                            M[con][i] -= mul * M[cur][i];
                        }

                        assert(M[con][var] < kEps);
                    }   
                }
                ++cur;
            }
        }

        return pivot;
    }  

    // Returns the solution of a system
    // Will not check if feasible
    // Will change matrix
    vector<double> SolveSystem(vector<vector<double>> &M) {
        int vars = M[0].size() - 1;
        auto pivs = ToRowEchelon(M);

        vector<double> solution(pivs.size());
        for(int i = 0; i < solution.size(); ++i)
            solution[i] = (pivs[i] == -1) ? 0.0 : M[pivs[i]][vars];
    }
};
