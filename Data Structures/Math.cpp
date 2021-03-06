int binaryExpo(int base, int power, int mod) {
	if (power == 0) {
		return 1;
	}
	int subAnswer = binaryExpo(base, power / 2, mod);
	int ans = subAnswer * subAnswer;
	ans %= mod;
	if (power % 2 == 1) {
		ans *= base;
		ans %= mod;
	}
	return ans;
}

int mod_add(int a, int b, int m) {
	a = a % m;
	b = b % m;
	return (((a + b) % m) + m) % m;
}

int mod_mul(int a, int b, int m) {
	a = a % m;
	b = b % m;
	return (((a * b) % m) + m) % m;
}

int mod_sub(int a, int b, int m) {
	a = a % m;
	b = b % m;
	return (((a - b) % m) + m) % m;
}

int expo(int a, int b, int mod) {
	int res = 1;
	while (b > 0) {
		if (b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b = b >> 1;
	}
	return res;
}

int mminvprime(int a, int b) {
	return expo(a, b - 2, b);
}

int mod_div(int a, int b, int m) {
	a = a % m;
	b = b % m;
	return (mod_mul(a, mminvprime(b, m), m) + m) % m;
}