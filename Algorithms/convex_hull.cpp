#include "convex_hull.h"

linesHull::line::line(int64_t k, int64_t b) :k(k), b(b) {}

double linesHull::line::intersect(line l) const
{
	return double(l.b - b) / (k - l.k);
}

int64_t linesHull::line::operator()(int64_t x)
{
	return k * x + b;
}

linesHull::linesHull(line l) :pos(1, -1e18), lines(1, l) {}

void linesHull::addLine(line l)
{
	while (true) {
		double t = l.intersect(lines.back());
		if (pos.back() >= t) {
			lines.pop_back();
			pos.pop_back();
		} else {
			lines.push_back(l);
			pos.push_back(t);
			return;
		}
	}
}

int64_t linesHull::operator()(int64_t x)
{
	int64_t l = 0, r = lines.size(), t;

	while (r - l > 1) {
		t = (l + r) / 2;

		if (pos[t] <= x)
			l = t;
		else
			r = t;
	}

	return lines[l](x);
}
