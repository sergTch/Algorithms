#include "str_algo.h"
#include <iostream>

vector<int64_t> prefix(const string& s) {
	int64_t n = s.size();
	int64_t k;
	vector<int64_t> pf(n);

	for (int64_t i = 1; i < n; i++) {
		k = pf[i - 1];
		while (s[i] != s[k] && k > 0)
			k = pf[k - 1];
		pf[i] = k + (s[i] == s[k]);
	}

	return pf;
}

vector<int64_t> find_all(const string& s, const string& p) {
	int64_t n = s.size();
	int64_t m = p.size();
	int64_t k = (p[0] == s[0]);
	vector<int64_t> pf = prefix(p);
	vector<int64_t> rez;

	if (m == k)
		rez.push_back(0);

	for (int64_t i = 1; i < n; i++) {
		if (k == m)
			k = pf[k - 1];

		while (s[i] != p[k] && k > 0)
			k = pf[k - 1];
		
		k += (s[i] == p[k]);
		
		if (k == m)
			rez.push_back(i + 1 - m);
	}

	return rez;
}

vector<int64_t> z_func(const string& s)
{
	int64_t n = s.size();
	int64_t idx = 0;
	vector<int64_t> rez(n);

	for (int64_t i = 1; i < n; i++) {
		if (idx + rez[idx] - i > 0)
			rez[i] = min(rez[i - idx], rez[idx] + idx - i);

		while (i + rez[i] < n && s[i + rez[i]] == s[rez[i]])
			rez[i]++;
		
		if (idx + rez[idx] < i + rez[i])
			idx = i;
	}

	return rez;
}
