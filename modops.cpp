const int kMod = 1e9 + 7;

// @region ModOps

int add(int a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
	return a;
}
int sub(int a, int b) {
	a -= b;
	if(a < 0) a += kMod;
	return a;
}
int mul(int a, int b) {
	return 1LL * a * b % kMod;
}
int lgpow(int b, int e) {
	int r = 1;
	while(e) {
		if(e % 2) 
			r = mul(r, b);
		b = mul(b, b);
		e /= 2;
	}
	return r;
}
int inv(int x) {
	int ret = lgpow(x, kMod - 2);
	assert(mul(ret, x) == 1);
	return ret;
}