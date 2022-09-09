#pragma once

#include <map>
#include <vector>

using namespace std;

map<int64_t, int64_t> getPrimes(const int64_t n);
vector<int64_t> getDividers(const int64_t n);

//greatest common divider
int64_t GCD(int64_t a, int64_t b);

//least common multiple
int64_t LCM(int64_t a, int64_t b);

//split each int to n into primes
vector<map<int64_t, int64_t>> precalcPrimes(int64_t n);

//find inverse to x element
// inverse (x) * x % mod == 1
int64_t inverseByMod(int64_t x, int64_t mod, map<int64_t, int64_t>* modPrimes = nullptr);

int64_t binPow(int64_t a, int64_t b);
int64_t binPow(int64_t a, int64_t b, int64_t mod);
