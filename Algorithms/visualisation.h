#pragma once
#include<bitset>
#include<vector>
#include<map>
#include<iostream>

using namespace std;

template<size_t t>
void show_bits(const bitset<t>& bx) {
	cout << bx << endl;
}

template <typename T>
void show_vec(const vector<T>& v, const string spliter = " ") {
	for (const T& i : v)
		cout << i << spliter;
	cout << endl;
}

template <typename T1, typename T2>
void show_map(const map<T1, T2>& m, const string spliter = " ") {
	for (const pair<T1, T2>& i : m)
		cout << i.first << ':' << i.second << spliter;
	cout << endl;
}