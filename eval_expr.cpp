struct EvalExpr {
 
    stack<char> Ops;
    stack<int> Nums;
     
    void SolveOp() {
     
        char op = Ops.top(); Ops.pop();
     
        int b = Nums.top(); Nums.pop();
        int a = Nums.top(); Nums.pop();
     
        // cerr << a << " " << op << " " << b << '\n';
     
        if(op == '+') return Nums.push(a + b);
        if(op == '-') return Nums.push(a - b);
        if(op == '*') return Nums.push(a * b);
        if(op == '/') return Nums.push(a / b);
        if(op == '%') return Nums.push(a % b);
    }
     
    int getPriority(char c) {
        if(c == '+' || c == '-') return 1;
        if(c == '*' || c == '/' || c == '%') return 2;
        return -1;
    }
     
     
    int comp(char c[]) {
        Ops.push('$'); // VALUARE
     
        int i = 0;
        while(c[i]) {
     
            if(c[i] == '(') {
                Ops.push(c[i]);
            } else if(c[i] == ')') {
                while(Ops.top() != '(')
                    SolveOp();
                Ops.pop();
            } else {
                int p = getPriority(c[i]);
                if(p >= 1) {
                    //Operator
                    while(getPriority(Ops.top()) >= p)
                        SolveOp();
     
                    Ops.push(c[i]);
                } else {
                    int a = 0;
                    while(isdigit(c[i])) {
                        a = a * 10 + c[i] - '0';
                        i++;
                    }
                    Nums.push(a);
                    i--;
                }
            }
     
            i++;
        }
     
        while(Ops.size() > 1)
            SolveOp();
        return Nums.top();
    }
};