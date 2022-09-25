#pragma once
#include <vector>

using namespace std;

class linesHull {
public:

	// y = kx + b
	class line {
	private:
		int64_t k, b;
	public:
		line(int64_t k, int64_t b);

		double intersect(line l) const;
		int64_t operator()(int64_t x);
	};

private:
	vector<double> pos;
	vector<line> lines;

public:
	linesHull(line l);

	void addLine(line l);

	int64_t operator()(int64_t x);
};
