// @author: Rafid Bin Mostofa

#include <bits/stdc++.h>

using namespace std;

typedef long double Tf;
typedef Tf Ti;	// int/ll for exactness

const Tf PI = acos(-1);
const Tf EPS = 1e-9;

// compares two floating values x and y 
inline int dcmp(Tf x, Tf y = 0) {
	return fabs(x - y) < EPS ? 0 : (x < y ? -1 : 1);
}

typedef struct Pt {
	Ti x, y;
	Pt(Ti x = 0, Ti y = 0) : x(x), y(y) { }

	bool operator == (const Pt& p) const { return !dcmp(x, p.x) and !dcmp(y, p.y); }
	bool operator != (const Pt& p) const { return !(*this == p); }
	bool operator < (const Pt& p) const { return dcmp(x, p.x) < 0 or (!dcmp(x, p.x) and dcmp(y, p.y) < 0); }
	bool operator > (const Pt& p) const { return p < *this; }

	Pt operator + (const Pt& p) const { return Pt(x + p.x, y + p.y); }
	Pt operator - (const Pt& p) const { return Pt(x - p.x, y - p.y); }
	Pt operator * (const auto v) const { return Pt(x * v, y * v); }
	Pt operator / (const auto v) const { return Pt(x / v, y / v); }

	friend istream& operator >> (istream& is, Pt& p) { return is >> p.x >> p.y; }
	friend ostream& operator << (ostream& os, const Pt& p) { return os << "(" << p.x << ", " << p.y << ")"; }
} Vec;

Ti cross(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }

typedef struct Seg {
	Pt a, b;
	Seg() { }
	Seg(Pt p, Pt q) : a(p), b(q) { }
} Line;

// 1 if c is left of a-b, -1 if right, 0 if on
int ccw(Pt a, Pt b, Pt c) { return dcmp(cross(b - a, c - a)); }

bool lines_parallel(Line p, Line q) { return !dcmp(cross(p.b - p.a, q.b - q.a)); }
bool lines_collinear(Line p, Line q) { return !ccw(p.a, p.b, q.a) and !ccw(p.a, p.b, q.b); }

Pt line_line_intersection(Line p, Line q) {
	Vec u = p.a - q.a, v = p.b - p.a, w = q.b - q.a;
	Tf k = (Tf) cross(w, u) / cross(v, w);
	return p.a + v * k;
}

typedef vector<Pt> Poly;

Tf polygon_area(Poly p) {
	Tf ret = 0;
	for(int i = 0; i < (int) p.size() - 1; ++i)
		ret += cross(p[i] - p[0], p[i + 1] - p[0]);
	return fabs(ret / 2);
}

int main() {
	int t, tc = 0;
	cin >> t;

	while(t--) {
		int n, w;
		cin >> n >> w;

		Poly pts(n);
		for(Pt& pt : pts) {
			cin >> pt;
		}

		sort(pts.begin(), pts.end());
		
		Poly polished;
		for(int i=0; i<(int) pts.size(); ++i) {
			if(i > 0 and !dcmp(pts[i].x, pts[i-1].x)) {
				polished.back().y = max(pts[i].y, polished.back().y);
			}
			else {
				polished.push_back(pts[i]);
			}
		}

		Tf res = 0;

		for(int i=0; i<(int) polished.size(); ++i) {
			Pt left = (i > 0 ? polished[i-1] : Pt(0, 0));
			Pt right = (i+1 < (int) polished.size() ? polished[i+1] : Pt(w, 0));

			auto base = [](Pt p) -> Pt {
				return Pt(p.x, 0);
			};

			res += polygon_area(Poly{ base(left), polished[i], base(right) });

			if(i > 0) {
				Pt intersection = line_line_intersection(Line(base(left), polished[i]), Line(left, base(polished[i])));
				res -= polygon_area(Poly{ base(left), intersection, base(polished[i]) });
			}
		}

		cout << fixed << setprecision(10) << res << "\n";
	}
	
	return 0;
}
