#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class suffixTree{

public:

	class node {
	public:
		int64_t start;
		int64_t* end;
		int64_t idx = -1;

		map<int64_t, node*> child;
		node* suffixLink = nullptr;

		int64_t size();

		node(int64_t s, int64_t* e);
		~node();
	};

private:

	int64_t remain = 0;
	int64_t actLen = 0;
	node* actNode = nullptr;
	node* lastNew = nullptr;
	char actEdge = 0;

	bool goDown(node* next);
	void extend();
	void set_idxs(node* nd, int64_t depth);

public:

	string s;
	int64_t end = 0;
	int64_t n;
	node* root;

	void show(node* nd, int64_t depth);
	suffixTree(const string& s);

	vector<int64_t> find_all(const string& p);
};

