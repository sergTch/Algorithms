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

	class position {
	public:
		int64_t start = 0;
		int64_t len = 0;
		int64_t actIdx = 0;
		node* actNode = nullptr;
		node* lastNew = nullptr;
		char actEdge = 0;

		const suffixTree& st;

		position(const suffixTree& st);

		void setEdge();
		node* nextNode();
		void goDown();

		bool addChar(const char& ch);
		void next();
	};

private:
	
	void extend(position& pos);
	void set_idxs(node* nd, int64_t depth);

public:

	string s;
	int64_t n;
	node* root;

	void show(node* nd, int64_t depth);
	suffixTree(const string& s);

	vector<int64_t> find_all(const string& p) const;
	
	//largest common substring
	int64_t LCS(const string& s, int64_t* idx1 = nullptr, int64_t* idx2 = nullptr) const;
};

