#pragma once
#include <iostream>
#include <queue>
#include <math.h>

template<class T, class TS>
class AVLnodeSum
{
private:
	inline void setHeightSum() {
		height = std::max((child[0]) ? child[0]->height : 0, (child[1]) ? child[1]->height : 0) + 1;
		sum = val;

		if (child[0])
			sum = sum + child[0]->sum;

		if (child[1])
			sum = sum + child[1]->sum;
	}

	inline void raiseChild(const size_t& t) {
		child[t]->parent = parent;
		if (parent)
			parent->child[pidx()] = child[t];
		parent = child[t];
		AVLnodeSum* buf = child[t]->child[t ^ 1];
		child[t]->child[t ^ 1] = this;

		child[t] = buf;
		if (buf)
			buf->parent = this;

		setHeightSum();
		parent->setHeightSum();
	}

	inline void balance() {
		if (height < 3)
			return;

		if (child[0] && child[1] && std::max(height - child[0]->height, height - child[1]->height) < 3)
			return;

		for (size_t i = 0; i < 2; i++) {
			if (child[i] && height - child[i]->height == 1) {
				if (!(child[i]->child[i] && child[i]->child[i]->height == height - 2))
					child[i]->raiseChild(i ^ 1);
				raiseChild(i);
				break;
			}
		}
	}

public:
	size_t height = 1;
	T data;
	TS val;
	TS sum;
	AVLnodeSum* parent;
	AVLnodeSum* child[2];

	~AVLnodeSum()
	{
		if (child[0])
			delete child[0];
		if (child[1])
			delete child[1];
	}

	AVLnodeSum() :
		parent(nullptr),
		child{ nullptr, nullptr },
		data()
	{
	}

	AVLnodeSum(const T& data) :
		parent(nullptr),
		child{ nullptr, nullptr }
	{
		this->data = data;
		sum = val;
	}

	AVLnodeSum(const T& data, const TS& val) :
		parent(nullptr),
		child{ nullptr, nullptr }
	{
		this->data = data;
		this->val = val;
		sum = val;
	}

	inline size_t pidx() const {
		if (parent)
			return parent->data < data;
		return 0;
	}

	void insert(const T& data) {
		if (this->data == data)
			return;

		bool t = this->data < data;

		if (!child[t]) {
			child[t] = new AVLnodeSum(data);
			child[t]->parent = this;
			setHeightSum();
			return;
		}

		child[t]->insert(data);
		setHeightSum();

		balance();
	}

	void set(const T& data, const TS& val) {
		if (this->data == data) {
			this->val = val;
			setHeightSum();
			return;
		}

		bool t = this->data < data;

		if (!child[t]) {
			child[t] = new AVLnodeSum(data, val);
			child[t]->parent = this;
			setHeightSum();
			return;
		}

		child[t]->set(data, val);
		setHeightSum();

		balance();
	}

	void erase(const T& data) {
		if (this->data == data) {
			if (height == 1) {
				parent->child[pidx()] = nullptr;
				delete this;
				return;
			}
			bool t = (child[1] && child[1]->height + 1 == height);

			T newData = child[t]->goDown(!t)->data;

			child[t]->erase(newData);
		}
		else {
			bool t = this->data < data;

			if (!child[t]) {
				return;
			}

			child[t]->erase(data);
		}
		setHeightSum();
		balance();
	}

	AVLnodeSum* find(const T& data) {
		if (this->data == data)
			return this;

		bool t = this->data < data;

		if (!child[t]) {
			return nullptr;
		}

		return child[t]->find(data);
	}

	AVLnodeSum* goDown(size_t t) {
		AVLnodeSum* node = this;

		while (node->child[t])
			node = node->child[t];

		return node;
	}

	AVLnodeSum* bound(const size_t k, const T& data) {
		if (this->data == data)
			return k ? this->next() : this->prev();

		bool t = this->data < data;

		if (!child[t]) {
			if (t != k)
				return this;
			if (t == 0)
				return prev();
			return next();
		}

		return child[t]->bound(k, data);
	}

	AVLnodeSum* next() {
		if (child[1])
			return child[1]->goDown(0);

		const AVLnodeSum* node = this;

		while (node->parent && node == node->parent->child[1]) {
			node = node->parent;
		}

		return node->parent;
	}

	AVLnodeSum* prev() {
		if (child[0])
			return child[0]->goDown(1);

		const AVLnodeSum* node = this;

		while (node->parent && node == node->parent->child[0]) {
			node = node->parent;
		}

		return node->parent;
	}
};


template<class T, class TS>
class AVLtreeSum
{
private:
	AVLnodeSum<T, TS>* root = nullptr;

public:
	~AVLtreeSum() {
		if (root)
			delete root;
	}

	void insert(const T& elem) {
		if (root == nullptr) {
			root = new AVLnodeSum<T, TS>(elem);
		}
		else {
			root->insert(elem);
		}
		while (root->parent)
			root = root->parent;
	}

	void set(const T& elem, const TS& val) {
		if (root == nullptr) {
			root = new AVLnodeSum<T, TS>(elem, val);
		}
		else {
			root->set(elem, val);
		}
		while (root->parent)
			root = root->parent;
	}

	void erase(const T& elem) {
		if (root == nullptr) {
			return;
		}
		else {
			if (elem == root->data && root->height == 1) {
				delete root;
				root = nullptr;
				return;
			}
			root->erase(elem);
		}
		while (root->parent)
			root = root->parent;
	}

	TS getSum(const T& x) {
		return getSum(x, x);
	}

	TS getSum(const T& l, const T& r) {
		if (r < l)
			return TS();

		AVLnodeSum<T, TS>* bounds[2];
		AVLnodeSum<T, TS>* common_root = root;
		size_t t;

		while (common_root && common_root->data != l && common_root->data != r) {
			t = common_root->data < l;

			if (t == (common_root->data < r)) {
				common_root = common_root->child[t];
			}
			else break;
		}

		if (!common_root)
			return TS();

		TS sum = common_root->val;

		bounds[0] = common_root->bound(0, l);
		bounds[1] = common_root->bound(1, r);

		for (t = 0; t < 2; t++) {
			if (!bounds[t]) {
				if (common_root->child[t])
					sum = sum + common_root->child[t]->sum;
			}
			else {
				if (t)
					bounds[t] = bounds[t]->prev();
				else bounds[t] = bounds[t]->next();

				bool k = true;

				while (bounds[t] != common_root) {
					if (k && bounds[t]->child[t ^ 1])
						sum = sum + bounds[t]->child[t ^ 1]->sum;
					if (k)
						sum = sum + bounds[t]->val;

					k = (t == bounds[t]->pidx());
					bounds[t] = bounds[t]->parent;
				}
			}
		}

		return sum;
	}

	inline AVLnodeSum<T, TS>* lower_bound(const T& elem) {
		return root ? root->bound(0, elem) : root;
	}

	inline AVLnodeSum<T, TS>* upper_bound(const T& elem) {
		return root ? root->bound(1, elem) : root;
	}

	inline AVLnodeSum<T, TS>* find(const T& elem) {
		return root ? root->find(elem) : root;
	}

	inline AVLnodeSum<T, TS>* start() {
		return root ? root->goDown(0) : root;
	}

	inline AVLnodeSum<T, TS>* end() {
		return root ? root->goDown(1) : root;
	}

	void show() {
		if (root) {
			std::queue<AVLnodeSum<T, TS>*> que;
			que.push(root);

			while (!que.empty()) {
				for (size_t i = 0; i < 2; i++)
					if (que.front()->child[i])
						que.push(que.front()->child[i]);

				std::cout << que.front()->data << "_s" << que.front()->sum << "_h" << que.front()->height << " ";
				que.pop();
			}
		}
		else {
			std::cout << "empty";
		}
		std::cout << std::endl;
	}

	inline size_t height() {
		return root ? root->height : 0;
	}
};

class int64_mx {
public:
	int64_t val;

	int64_mx() : val(0) {}
	int64_mx(int64_t v) : val(v) {}

	int64_mx operator+(int64_mx k) { return std::max(val, k.val); }
};
