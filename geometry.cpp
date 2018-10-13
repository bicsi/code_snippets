#include <bits/stdc++.h>

using namespace std;

namespace Geometry {

    const double kEps = 1e-9;
    const double kPI = 4.0 * atan(1.0);

    using Point = complex<double>;
    #define x real()
    #define y imag()
    auto compare = [] (const Point &a, const Point &b) {
        if(abs(a.x - b.x) < kEps) return a.y < b.y;
        return a.x < b.x;
    };
    istream& operator>>(istream &is, Point &p) {
        double a, b;
        is >> a >> b;
        p = Point(a, b);
        return is;
    }


    // Dot and cross product of two vectors
    double dot(Point a, Point b) {
        return real(conj(a) * b);
    }
    double cross(Point a, Point b) {
        return imag(conj(a) * b);
    }

    // Distance between two points
    double dist(Point a, Point b) {
        return abs(a - b);
    }

    // Rotates a point counter-clockwise with angle theta
    // (in radians)
    Point RotateCCW(Point a, double theta) {
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

    // Checks if lines (a, b) and (c, d) are parallel or coincide
    bool LinesParallelOrCoincide(Point a, Point b, Point c, Point d) { 
        return abs(cross(b - a, d - c)) < kEps;
    }
    bool LinesCoincide(Point a, Point b, Point c, Point d) {
        return LinesParallelOrCoincide(a, b, c, d)
            && abs(cross(a - b, a - c)) < kEps
            && abs(cross(c - d, c - a)) < kEps;
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

    // Projects point p on segment [a, b]
    Point ProjectPointOnSegment(Point p, Point a, Point b) {
        // Check a == b
        double r = dot(b - a, b - a);
        if (abs(r) < kEps) return a;

        r = dot(p - a, b - a) / r;
        if (r < 0) return a;
        if (r > 1) return b;

        return a + (b - a) * r;
    }
  
    // Applies the affine transformation that takes the [p0..p1] 
    // segment to [q0..q1] to the point r.
    Point ApplyTransformation(Point p0, Point p1,
                              Point q0, Point q1, Point r) {
        Point dp = p1 - p0, dq = q1 - q0,
              num = dp * conj(dq);
        return q0 + (r - p0) * conj(num) / norm(dp);
    }


    // Returns the signed area of a (non-convex) polygon
    // Could be as well done with ints
    double SignedArea(vector<Point> &P) {
        double area = 0;
        P.push_back(P[0]);

        for (int i = 1; i < P.size(); ++i) {
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

        for (int i = 1; i < P.size(); ++i) {
            Point a = P[i - 1], b = P[i];

            if (a.x > b.x) swap(a, b);


            auto crs = cross(b - a, p - a);
            if (crs == 0 &&
                p.x >= a.x && p.x <= b.x && 
                p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y)) 
                return 0;
            
            if (a.x <= p.x && p.x < b.x && crs < 0)
                ans = -ans;
        }

        P.pop_back();
        return ans;
    }

    // Computes the intersection of line (a, b) and circle
    // (c, r) and returns 0, 1, or 2 points
    vector<Point> CircleLineIntersection (
        Point a, Point b, Point c, double r) {
        // Points cannot coincide
        assert(abs(a - b) > kEps);

        // Translate and rotate
        b -= a; c -= a;
        double theta = arg(b);
        b = RotateCCW(b, -theta);
        c = RotateCCW(c, -theta);
        assert(abs(b.y) < kEps);

        // Now intersect circle with Ox
        vector<Point> ret;

        // No intersection check
        if(c.y > r + kEps || c.y < -r - kEps) 
            return ret;

        Point proj(c.x, 0.0);
        double delta = sqrt(r * r - c.y * c.y);

        ret.push_back(a + RotateCCW(proj - delta, theta));
        if(delta > kEps)
            ret.push_back(a + RotateCCW(proj + delta, theta));

        return ret;
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
