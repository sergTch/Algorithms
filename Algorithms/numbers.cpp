#include "numbers.h"
#include <algorithm>

map<int64_t, int64_t> getPrimes(int64_t n) {
	map<int64_t, int64_t> rez;

	for (int64_t i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			rez[i]++;
			n /= i;
		}
	}

	if (n != 1)
		rez[n]++;

	return rez;
}

vector<int64_t> getDividers(const int64_t n)
{
	vector<int64_t> rez;

	for (int64_t i = 1; i * i <= n; i++) {
		if (n % i == 0)
			rez.push_back(i);
	}

	for (int64_t i = rez.size() - 2 + (rez.back() * rez.back() != n); i >= 0; i--)
		rez.push_back(n / rez[i]);

	return rez;
}

int64_t GCD(int64_t a, int64_t b)
{
	int64_t t;

	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}

	return a;
}

int64_t LCM(int64_t a, int64_t b)
{
	return a * b / GCD(a, b);
}

vector<map<int64_t, int64_t>> precalcPrimes(int64_t n)
{
	vector<map<int64_t, int64_t>> rez(n + 1);
	int64_t p;

	for (int64_t i = 2; i <= n; i++) {
		if (rez[i].size() == 0) {
			p = i;

			while (p <= n) {
				for (int64_t j = 1; j * p <= n; j++) {
					rez[j * p][i]++;
				}
				p *= i;
			}
		}
	}

	return rez;
}

int64_t eulerFunc(int64_t n, map<int64_t, int64_t>* primes)
{
	int64_t k = 1;

	for (auto i : primes ? (*primes) : getPrimes(n))
		k = k * (i.first - 1) * binPow(i.first, i.second - 1);

	return k;
}

int64_t inverseByMod(int64_t x, int64_t mod, map<int64_t, int64_t> *modPrimes)
{
	return binPow(x, eulerFunc(mod, modPrimes), mod);
}

uint64_t binPow(uint64_t a, uint64_t b) {
	uint64_t rez = 1;

	while (b > 0) {
		if (b % 2)
			rez *= a;
		a *= a;
		b /= 2;
	}

	return rez;
}

uint64_t binPow(uint64_t a, uint64_t b, uint64_t mod) {
	uint64_t rez = 1;

	while (b > 0) {
		if (b % 2)
			rez = rez * a % mod;
		a = a * a % mod;
		b /= 2;
	}

	return rez % mod;
}