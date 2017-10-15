struct Frac {
    long long a, b;
};

// Does binary search on fractions having an upper bound on
// the numerator, given a predicate pred. The predicate should
// monotonous function going from negative to 0 to positive.
// The function will find a random fraction f for which pred(f) = 0.
// Complexity: O(log(max_num))
template<typename Predicate>
Frac FracBinarySearch(long long max_num, Predicate pred) {
    Frac lo{0, 1}, hi{1, 1}; // set to {1, 0} for [0...max_num)
    int sign = 1;
    
    if (pred(lo) == 0) return lo;    
    while (true) {    
        int adv = 0;
        bool down = false;

        for (int step = 1; step; down ? step /= 2 : step *= 2) {
            adv += step;

            Frac mid{lo.a * adv + hi.a, lo.b * adv + hi.b};
            if (mid.a > max_num or mid.b > max_num) {
                adv -= step; down = true; continue;
            }

            long long res = pred(mid);
            if (res == 0) return mid;
            if (res * sign < 0) { adv -= step; down = true; }
        }  

        hi.a += lo.a * adv; 
        hi.b += lo.b * adv;
        sign = -sign;
        swap(lo, hi);
    }
}
