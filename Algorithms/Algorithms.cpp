#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<list>
#include<time.h>
#include<random>
#include<bitset>
#include<unordered_set>
#include<stdint.h>

using namespace std;

void run() {
	srand((unsigned)time(NULL));

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}

typedef pair<int64_t, int64_t> cut;
inline cut flip(cut c) { return cut(c.second, c.first); }
inline cut sortCut(cut c) { return c.first < c.second ? c : flip(c); }

void show_bits(bitset<8> bx) {
	cout << bx << endl;
}

const int64_t inf = INT64_MAX;

const int64_t MOD = 998244353;

void solve() {
	int64_t n, m, p, q, a, b, c, d, x, y, z, sum = 0, rez = 0, next, cur, prev, l, r, t, k, mx = -inf, mn = inf;

	cin >> n >> m;

	return;
}

int main() {
	run();

	int64_t test = 1;
	//cin >> test;
	int i = 1;

	while (test--) {
		//cout << "Case #" << (i++) << ": ";
		solve();
	}

	return 0;
}
