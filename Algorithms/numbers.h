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

int64_t eulerFunc(int64_t n, map<int64_t, int64_t>* primes = nullptr);

uint64_t binPow(uint64_t a, uint64_t b);
uint64_t binPow(uint64_t a, uint64_t b, uint64_t mod);
