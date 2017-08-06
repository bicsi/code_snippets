struct NTTHelper {
	int N, P, G, invN, invG;
	int MIN_V = 398127391;

	void Compute(int n) {
		assert(n == (n & -n));

		N = n;
		P = getPrime(N);
		G = getGenerator(N, P);
		invN = inv(N, P);
		invG = inv(G, P);

		assert(1LL * N * invN % P == 1);
		assert(1LL * G * invG % P == 1);
	}

	void Output(ostream &out) {
		out << "Number is: " << N << '\n';
		out << "Prime is: " << P << '\n';
		out << "Generator is: " << G << '\n';
		out << "N inverse is: " << invN << '\n';
		out << "G inverse is: " << invG << '\n';
	}

	int lgpow(int b, int e, int p) {
		int r = 1;
		while(e) {
			if(e % 2) r = 1LL * r * b % p;
			b = 1LL * b * b % p;
			e /= 2;
		}
		return r;
	}

	int inv(int x, int p) {
		return lgpow(x, p - 2, p);
	}

	bool isPrime(int p) {
		for(int d = 2; d * d <= p; ++d)
			if(p % d == 0)
				return false;
		return true;
	}

	int getPrime(int n) {
		int p = MIN_V + n - MIN_V % n + 1;
		assert((p - 1) % n == 0);

		while(true) {
			if(isPrime(p))
				return p;
			p += n;
		}
	}

	int getGenerator(int n, int p) {
		for(int g = 2; true; ++g) {

			if(lgpow(g, n, p) != 1)
				continue;

			for(int d = 2; d < n; d *= 2)
				if(lgpow(g, d, p) == 1)
					continue;

			return g;
		}
	}
};
