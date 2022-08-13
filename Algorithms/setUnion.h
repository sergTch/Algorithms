#pragma once

#include <vector>

using namespace std;


// from 0 to n - 1
class setUnion
{
private:
	vector<size_t> parent;
	vector<size_t> size;
	size_t n;

public:
	setUnion(size_t n) :
		parent(n),
		size(n),
		n(n)
	{
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			size[i] = 1;
		}
	}

	size_t find_set(size_t v) {
		if (v == parent[v])
			return v;
		return parent[v] = find_set(parent[v]);
	}

	void union_sets(size_t a, size_t b) {
		a = find_set(a);
		b = find_set(b);

		if (a != b) {
			if (size[a] < size[b])
				swap(a, b);

			parent[b] = a;
			size[a] += size[b];
		}
	}

	vector<size_t> get_full(size_t a) {
		a = find_set(a);
		vector<size_t> arr;

		for (int i = 0; i < n; i++)
			if (find_set(i) == a)
				arr.push_back(i);

		return arr;
	}

	size_t count_sets() {
		size_t rez = 0;
		for (int i = 0; i < n; i++) {
			rez += (i == parent[i]);
		}
		return rez;
	}

	size_t getSize(size_t a) {
		return size[find_set(a)];
	}
};

