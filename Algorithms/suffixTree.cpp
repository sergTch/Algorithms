#include "suffixTree.h"
#include <queue>
#include <algorithm>

inline int64_t suffixTree::node::size() {
	return *end - start;
}

suffixTree::node::node(int64_t s, int64_t* e) : start(s), end(e) { }

suffixTree::node::~node() {
	if (idx < 0)
		delete end;
	for (auto& i : child)
		delete i.second;
}

bool suffixTree::goDown(node* next)
{
	if (actLen >= next->size()) {
		actEdge = s[end - actLen + next->size()];
		actLen -= next->size();
		actNode = next;
		return true;
	}

	return false;
}

void suffixTree::extend() {
	remain++;
	lastNew = nullptr;

	while (remain > 0) {
		actEdge = s[end - actLen];
		
		if (actNode->child.find(actEdge) == actNode->child.end()) {
			actNode->child[actEdge] = new node(end, &end);
			
			if (lastNew && lastNew != root)
				lastNew->suffixLink = actNode;
			lastNew = actNode;
		}
		else {
			node* next = actNode->child[actEdge];

			if (goDown(next))
				continue;

			if (s[next->start + actLen] == s[end]) {
				actLen++;
				
				if (lastNew && lastNew != root)
					lastNew->suffixLink = actNode;
				lastNew = actNode;

				break;
			}
			else {
				node* split = new node(next->start, new int64_t(next->start + actLen));
				next->start += actLen;

				actNode->child[actEdge] = split;
				split->child[s[next->start]] = next;
				split->child[s[end]] = new node(end, &end);

				if (lastNew)
					lastNew->suffixLink = split;

				lastNew = split;
			}
		}

		if (actNode == root && actLen > 0) {
			actEdge = s[end - remain + 1];
			actLen--;
		}
		if (actNode != root) {
			actNode = actNode->suffixLink;
		}
		remain--;
	}
}

void suffixTree::set_idxs(node* nd, int64_t depth) {
	if (nd->child.size() == 0)
		nd->idx = n - depth - nd->size();
	else {
		for (auto& i : nd->child)
			set_idxs(i.second, depth + nd->size());
	}
}

void suffixTree::show(node* nd, int64_t depth){
	for (int64_t i = 1; i < depth; i++)
		cout << "  ";
	for (int64_t i = nd->start; i < *nd->end; i++)
		cout << s[i];
	if (nd->child.size() == 0)
		cout << " " << nd->idx;
	//else
	//	cout << endl << nd << " " << nd->suffixLink;
	cout << endl;
	for (auto& i : nd->child)
		show(i.second, depth + 1);
}

suffixTree::suffixTree(const string& s) {
	//this->s = s;
	this->s = s + '\0';
	n = this->s.size();
	root = new node(0, new int64_t());

	actNode = root;

	for (end = 0; end < n; end++) {
		extend();
	}
	n = s.size();
	end = s.size();
	set_idxs(root, 0);
}

vector<int64_t> suffixTree::find_all(const string& p)
{
	vector<int64_t> rez;
	node* nd = root;
	int64_t t = 0;

	for (int64_t i = 0; i < p.size(); i++) {
		if (t == nd->size()) {
			if (nd->child.find(p[i]) == nd->child.end())
				return vector<int64_t>();
			nd = nd->child[p[i]];
			t = 0;
		}
		if (s[nd->start + t] != p[i])
			return vector<int64_t>();
		t++;
	}

	t = nd->size() - t;

	queue<node*> que;
	que.push(nd);

	while (!que.empty()) {
		nd = que.front();
		que.pop();

		if (nd->child.size())
			for (auto& i : nd->child)
				que.push(i.second);
		else
			rez.push_back(nd->idx);
	}

	sort(rez.begin(), rez.end());

	return rez;
}
