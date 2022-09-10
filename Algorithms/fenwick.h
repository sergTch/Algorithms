#pragma once 

// from 1 to n
template<class T>
class fenw_sum
{
private:
	T* arr;

	void addFromStart(T x, int idx) {
		for (; idx <= n; idx += (idx & (-idx)))
			arr[idx] += x;
	}

public:
	int n;

	fenw_sum(int n) {
		this->n = n;
		arr = new T[n + 1]();
	}

	~fenw_sum() {
		delete[] arr;
	}

	void add(T x, int idx) {
		addFromStart(x, idx);
		addFromStart(-x, idx + 1);
	}

	void add(T x, int l, int r) {
		addFromStart(x, l);
		addFromStart(-x, r + 1);
	}

	T get(int n) {
		T rez = 0;
		for (int t = n; t > 0; t -= (t & (-t)))
			rez += arr[t];

		return rez;
	}
};
