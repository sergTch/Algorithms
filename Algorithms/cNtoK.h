#pragma once

#include <vector>
#include "numbers.h"

using namespace std;

class cNtoK
{
private:
	int64_t mod;
	vector<int64_t> fact;
	vector<int64_t> rfact;

public:
	cNtoK(int64_t m) {
		mod = m;
	}

	cNtoK(int64_t m, int64_t bsize) {
		mod = m;
		fillBuf(bsize + 1);
	}

	void fillBuf(int64_t n) {
		n++;
		int64_t size = fact.size();
		if (size >= n)
			return;

		fact.resize(n);
		rfact.resize(n);

		if (size == 0) {
			size = 1;
			fact[0] = 1;
			rfact[0] = 1;
		}

		for (int i = size; i < n; i++) {
			fact[i] = fact[i - 1] * i % mod;
			rfact[i] = binPow(fact[i], mod - 2, mod);
		}
	}

	int64_t operator()(int64_t n, int64_t k) {
		if (k > n)
			return 0;

		if (n >= fact.size())
			fillBuf(n);

		return fact[n] * rfact[k] % mod * rfact[n - k] % mod;
	}
};

