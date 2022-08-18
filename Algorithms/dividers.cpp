#include "dividers.h"

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
