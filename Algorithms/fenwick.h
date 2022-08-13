#pragma once 

// from 1 to n
template<class T>
class fenw_sum
{
private:
	T* arr;

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
		for (; idx <= n; idx += (idx & (-idx)))
			arr[idx] += x;
	}

	void add(T x, int l, int r) {
		add(x, l);
		add(-x, r);
	}

	T get(int n) {
		T rez = 0;
		for (int t = n; t > 0; t -= (t & (-t)))
			rez += arr[t];

		return rez;
	}

	T get(int l, int r) {
		return get(r - 1) - get(l - 1);
	}
};
