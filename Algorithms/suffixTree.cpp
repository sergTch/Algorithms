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

void suffixTree::extend(position& pos) {
	pos.len++;
	pos.lastNew = nullptr;

	while (pos.len > 0) {
		pos.goDown();
		node* next = pos.nextNode();

		if (!next) {
			pos.actNode->child[pos.actEdge] = new node(n, &n);
			
			if (pos.lastNew && pos.lastNew != root)
				pos.lastNew->suffixLink = pos.actNode;
			pos.lastNew = pos.actNode;
		}
		else {
			if (s[next->start + pos.actIdx] == s[n]) {
				pos.actIdx++;
				
				if (pos.lastNew && pos.lastNew != root)
					pos.lastNew->suffixLink = pos.actNode;
				pos.lastNew = pos.actNode;

				break;
			}
			else {
				node* split = new node(next->start, new int64_t(next->start + pos.actIdx));
				next->start += pos.actIdx;

				pos.actNode->child[pos.actEdge] = split;
				split->child[s[next->start]] = next;
				split->child[s[n]] = new node(n, &n);

				if (pos.lastNew)
					pos.lastNew->suffixLink = split;

				pos.lastNew = split;
			}
		}

		pos.next();
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
	cout << "  " << nd->start << " - " << *nd->end;
	if (nd->child.size() == 0)
		cout << "  " << nd->idx;
	//else
	//	cout << endl << nd << " " << nd->suffixLink;
	cout << endl;
	for (auto& i : nd->child)
		show(i.second, depth + 1);
}

suffixTree::suffixTree(const string& s) {
	//this->s = s;
	this->s = s + '\0';
	root = new node(0, new int64_t());

	//actNode = root;
	position pos(*this);

	for (n = 0; n < this->s.size(); n++) {
		extend(pos);
	}

	n = s.size();
	set_idxs(root, 0);
}

vector<int64_t> suffixTree::find_all(const string& p) const
{
	vector<int64_t> rez;
	position pos(*this);

	for (auto& i : p)
		if (!pos.addChar(i))
			return rez;

	queue<node*> que;
	node* nd;
	que.push(pos.nextNode());

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

// Largest Common Substring
// idx1 index in tree string
// idx2 index in input string
// len  length of substring
int64_t suffixTree::LCS(const string& s, int64_t* idx1, int64_t* idx2) const
{
	int64_t len = 0;
	position pos(*this);

	for (int64_t i = 0; i < s.size(); i++) {
		if (pos.addChar(s[i])) {
			if (len < pos.len) {
				len = pos.len;
				if (idx1) *idx1 = pos.start;
				if (idx2) *idx2 = i - len + 1;
			}
		}
		else if (pos.len > 0) {
			pos.next();
			i--;
		}
	}
	return len;
}

suffixTree::position::position(const suffixTree& st) : st(st) { actNode = st.root; }

void suffixTree::position::setEdge()
{
	actEdge = st.s[start + len - 1 - actIdx];
}

inline suffixTree::node* suffixTree::position::nextNode()
{
	if (len == 0)
		return st.root;
	setEdge();
	if (actNode->child.find(actEdge) != actNode->child.end())
		return actNode->child[actEdge];
	else 
		return nullptr;
}

bool suffixTree::position::addChar(const char& ch)
{
	node* next = nextNode();

	if (next->size() <= actIdx + 1 && next->child.find(ch) != next->child.end()) {
		start = next->child[ch]->start - len;
		actIdx = 0;
		actEdge = ch;
		actNode = next;
		len++;
		return true;
	}
	if (next->size() > actIdx + 1 && st.s[start + len] == ch) {
		actIdx++;
		len++;
		return true;
	}

	return false;
}

void suffixTree::position::goDown()
{
	node* next = nextNode();

	while (next && actIdx >= next->size()) {
		actIdx -= next->size();
		actNode = next;

		next = nextNode();
	}
}

void suffixTree::position::next()
{
	if (actNode == st.root && actIdx > 0) {
		actIdx--;
		setEdge();
	}
	if (actNode != st.root) {
		actNode = actNode->suffixLink;
	}
	len--;
	start++;
	if (len)
		goDown();
}
