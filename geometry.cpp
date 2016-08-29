namespace Geometry {

	const double kEps = 1e-9;
	const double kPI = 4.0 * atan(1.0);

	typedef complex<double> Point;
	#define x real()
	#define y imag()
	auto compare = [] (const Point &a, const Point &b) {
		if(abs(a.x - b.x) < kEps) return a.y < b.y;
		return a.x < b.x;
	};


	// Dot and cross product of two vectors
	double dot(Point a, Point b) {
		return real(conj(a) * b);
	}
	double cross(Point a, Point b) {
		return imag(conj(a) * b);
	}

	// Rotates a point clocwise with angle theta
	// (in radians)
	Point RotateCW(Point a, double theta) {
		return a * polar(1.0, theta);
	}

	// Circumcenter given 3 vectors 
	// (problems when non-collinear)
	Point CircumCenter(Point a, Point b, Point c) {
		b -= a; c -= a;
		Point cen(
			c.y * norm(b) - b.y * norm(c),
			b.x * norm(c) - c.x * norm(b)
		);
		return a + cen / (2 * cross(b, c));
	}

	// Line intersection of (a, b) and (p, q)
	// given that there is a unique intersection(not parallel or same)
	Point LineIntersection(Point a, Point b, Point p, Point q) {
		double c1 = cross(p - a, b - a), c2 = cross(q - a, b - a);
		assert(abs(c1 - c2) > kEps); // undefined if parallel
		return (c1 * q - c2 * p) / (c1 - c2); 
	}

	// Projects point p on line (a, b)
	Point ProjectPointOnLine(Point p, Point a, Point b) {
		return a + (b - a) * dot(p - a, b - a) / norm(b - a);
	}

	// Returns the signed area of a (non-convex) polygon
	// Could be as well done with ints
	double SignedArea(vector<Point> &P) {
		double area = 0;
		P.push_back(P[0]);

		for(int i = 1; i < P.size(); ++i) {
			area += cross(P[i - 1], P[i]);
		}

		P.pop_back();
		return 0.5 * area;
	}

	// Checks if point p is inside (non-convex) polygon P and returns:
	//  1 if p is strictly inside P
	//  0 if p is on P
	// -1 if p is strictly outside P
	int PointInPolygon(Point p, vector<Point> &P) {
	    P.push_back(P[0]);
	    int ans = -1;

	    for(int i = 1; i < P.size(); ++i) {
	        Point a = P[i - 1], b = P[i];

	        if(a.x > b.x) swap(a, b);


	        auto crs = cross(b - a, p - a);
	        if( crs == 0 &&
	           	p.x >= a.x && p.x <= b.x && 
	          	p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y)) 
	            return 0;
	        
	        if(a.x <= p.x && p.x < b.x && crs < 0)
	            ans = -ans;
	    }

	    P.pop_back();
	    return ans;
	}

	// Computes the convex hull of a set of points
	// To make it non-strict, obviously replace the sign of the check
	// Returns a pair <upper_hull, lower_hull>
	pair<vector<Point>, vector<Point>> ConvexHull(vector<Point> P) {
		pair<vector<Point>, vector<Point>> ret;
		auto &up = ret.first;
		auto &dw = ret.second;

		sort(P.begin(), P.end(), compare);
		P.resize(unique(P.begin(), P.end()) - P.begin());

		auto det = [](Point &a, Point &b, Point &c) {
			return cross(b - a, c - a);
		};

		for(auto p : P) {
			while(up.size() >= 2 && det(up[up.size() - 2], up.back(), p) > 0)
				up.pop_back();
			up.push_back(p);

			while(dw.size() >= 2 && det(dw[dw.size() - 2], dw.back(), p) < 0)
				dw.pop_back();
			dw.push_back(p);
		}

		return ret;
	}
};
using namespace Geometry;