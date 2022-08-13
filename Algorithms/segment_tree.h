#pragma once
#include <vector>

using namespace std;

// from 1 to n
template <typename T>
class seg_tree_max
{
private:
	T* tree;
	T* lazy;
	size_t n;
	T nil;

	inline size_t left(const size_t& idx) {
		return idx << 1;
	}
	inline size_t right(const size_t& idx) {
		return (idx << 1) | 1;
	}
	inline size_t mid(const size_t& l, const size_t& r) {
		return (l + r) >> 1;
	}
	inline T max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

	void init(size_t idx, size_t tl, size_t tr, vector<T>& arr) {
		lazy[idx] = nil;
		if (tr == tl)
			tree[idx] = arr[tr - 1];
		else {
			init(left(idx), tl, mid(tl, tr), arr);
			init(right(idx), mid(tl, tr) + 1, tr, arr);
			tree[idx] = max(tree[left(idx)], tree[right(idx)]);
		}
	}

	inline void pushDown(const size_t& idx, const size_t& tl, const size_t& tr) {
		if (lazy[idx] == nil)
			return;
		tree[idx] = lazy[idx];

		if (tl != tr) {
			lazy[left(idx)] = lazy[idx];
			lazy[right(idx)] = lazy[idx];
		}

		lazy[idx] = nil;
	}

	T query(size_t idx, size_t tl, size_t tr, size_t l, size_t r) {
		pushDown(idx, tl, tr);

		if (tl > r || tr < l || l > r)
			return nil;
		if (tl >= l && tr <= r)
			return tree[idx];
		return max(query(left(idx), tl, mid(tl, tr), l, r),
			query(right(idx), mid(tl, tr) + 1, tr, l, r));
	}

	void update(size_t idx, size_t tl, size_t tr, size_t l, size_t r, T elem) {
		pushDown(idx, tl, tr);

		if (tl > r || tr < l || l > r)
			return;

		if (tl >= l && tr <= r) {
			lazy[idx] = elem;
			pushDown(idx, tl, tr);
			return;
		}

		update(left(idx), tl, mid(tl, tr), l, r, elem);
		update(right(idx), mid(tl, tr) + 1, tr, l, r, elem);
		tree[idx] = max(tree[left(idx)], tree[right(idx)]);
	}

public:

	seg_tree_max(size_t n, T nil) : n(n) {
		this->nil = nil;
		tree = new T[n * 4];
		lazy = new T[n * 4];

		for (int i = 0; i < n * 4; i++) {
			tree[i] = nil;
			lazy[i] = nil;
		}
	}

	seg_tree_max(vector<T>& arr, T nil) : n(arr.size()) {
		this->nil = nil;
		tree = new T[n * 4];
		lazy = new T[n * 4];

		if (arr.size())
			init(1, 1, n, arr);
	}

	~seg_tree_max() {
		if (tree)
			delete[] tree;
		if (lazy)
			delete[] lazy;
	}

	T query(size_t l, size_t r) {
		return query(1, 1, n, l, r);
	}

	T query(size_t idx) {
		return query(1, 1, n, idx, idx);
	}

	void update(size_t l, size_t r, T elem) {
		update(1, 1, n, l, r, elem);
	}

	void update(size_t idx, T elem) {
		update(1, 1, n, idx, idx, elem);
	}
};

template <typename T>
class lazy_seg_tree_sum
{
private:
	T* tree;
	T* lazy;

	size_t n;
	T nil;

	inline size_t left(const size_t& idx) {
		return idx << 1;
	}
	inline size_t right(const size_t& idx) {
		return (idx << 1) | 1;
	}
	inline size_t mid(const size_t& l, const size_t& r) {
		return (l + r) >> 1;
	}

	void init(size_t idx, size_t tl, size_t tr, vector<T>& arr) {
		lazy[idx] = nil;
		if (tr == tl)
			tree[idx] = arr[tr - 1];
		else {
			init(left(idx), tl, mid(tl, tr), arr);
			init(right(idx), mid(tl, tr) + 1, tr, arr);
			tree[idx] = tree[left(idx)] + tree[right(idx)];
		}
	}

	inline void pushDown(const size_t& idx, const size_t& tl, const size_t& tr) {
		if (lazy[idx] == nil)
			return;

		tree[idx] += lazy[idx] * (tr - tl + 1);

		if (tl != tr) {
			lazy[left(idx)] += lazy[idx];
			lazy[right(idx)] += lazy[idx];
		}

		lazy[idx] = nil;
	}

	T query(size_t idx, size_t tl, size_t tr, size_t l, size_t r) {
		pushDown(idx, tl, tr);

		if (tl > r || tr < l || l > r)
			return nil;
		if (tl >= l && tr <= r)
			return tree[idx];
		return query(left(idx), tl, mid(tl, tr), l, r) +
			query(right(idx), mid(tl, tr) + 1, tr, l, r);
	}

	void update(size_t idx, size_t tl, size_t tr, size_t l, size_t r, T elem) {
		pushDown(idx, tl, tr);

		if (tl > r || tr < l || l > r)
			return;

		if (tl >= l && tr <= r) {
			lazy[idx] = elem;
			pushDown(idx, tl, tr);
			return;
		}

		update(left(idx), tl, mid(tl, tr), l, r, elem);
		update(right(idx), mid(tl, tr) + 1, tr, l, r, elem);
		tree[idx] = tree[left(idx)] + tree[right(idx)];
	}

public:

	lazy_seg_tree_sum(size_t n, T nil) : n(n) {
		this->nil = nil;
		tree = new T[n * 4];
		lazy = new T[n * 4];

		for (int i = 0; i < n * 4; i++) {
			tree[i] = nil;
			lazy[i] = nil;
		}
	}

	lazy_seg_tree_sum(vector<T>& arr, T nil) : n(arr.size()) {
		this->nil = nil;
		tree = new T[n * 4];
		lazy = new T[n * 4];

		if (arr.size())
			init(1, 1, n, arr);
	}

	~lazy_seg_tree_sum() {
		if (tree)
			delete[] tree;
		if (lazy)
			delete[] lazy;
	}

	T query(size_t l, size_t r) {
		return query(1, 1, n, l, r);
	}

	T query(size_t idx) {
		return query(1, 1, n, idx, idx);
	}

	void add(size_t l, size_t r, T elem) {
		update(1, 1, n, l, r, elem);
	}

	void add(size_t idx, T elem) {
		update(1, 1, n, idx, idx, elem);
	}
};


template <typename T>
class seg_tree_sum
{
private:
	T* tree;
	size_t n;
	T nil;

	inline size_t left(const size_t& idx) {
		return idx << 1;
	}
	inline size_t right(const size_t& idx) {
		return (idx << 1) | 1;
	}
	inline size_t mid(const size_t& l, const size_t& r) {
		return (l + r) >> 1;
	}

	void init(size_t idx, size_t tl, size_t tr, vector<T>& arr) {
		if (tr == tl)
			tree[idx] = arr[tr - 1];
		else {
			init(left(idx), tl, mid(tl, tr), arr);
			init(right(idx), mid(tl, tr) + 1, tr, arr);
			tree[idx] = tree[left(idx)] + tree[right(idx)];
		}
	}

	T query(size_t idx, size_t tl, size_t tr, size_t l, size_t r) {
		if (tl > r || tr < l || l > r)
			return nil;
		if (tl >= l && tr <= r)
			return tree[idx];
		return query(left(idx), tl, mid(tl, tr), l, r) +
			query(right(idx), mid(tl, tr) + 1, tr, l, r);
	}

	void update(size_t idx, size_t tl, size_t tr, size_t l, size_t r, T elem) {
		if (tl > r || tr < l || l > r)
			return;

		update(left(idx), tl, mid(tl, tr), l, r, elem);
		update(right(idx), mid(tl, tr) + 1, tr, l, r, elem);
		tree[idx] = tree[left(idx)] + tree[right(idx)];
	}

public:

	seg_tree_sum(size_t n, T nil) : n(n) {
		this->nil = nil;
		tree = new T[n * 4];

		for (int i = 0; i < n * 4; i++) {
			tree[i] = nil;
		}
	}

	seg_tree_sum(vector<T>& arr, T nil) : n(arr.size()) {
		this->nil = nil;
		tree = new T[n * 4];

		if (arr.size())
			init(1, 1, n, arr);
	}

	~seg_tree_sum() {
		if (tree)
			delete[] tree;
	}

	T query(size_t l, size_t r) {
		return query(1, 1, n, l, r);
	}

	T query(size_t idx) {
		return query(1, 1, n, idx, idx);
	}

	void update(size_t l, size_t r, T elem) {
		update(1, 1, n, l, r, elem);
	}

	void update(size_t idx, T elem) {
		update(1, 1, n, idx, idx, elem);
	}
};