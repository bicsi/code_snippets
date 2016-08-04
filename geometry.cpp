
typedef complex<double> Point;
#define x real()
#define y imag()
const double kEps = 1e-9;


// Dot and cross product of two vectors
double dot(Point a, Point b) {
	return real(conj(a) * b);
}
double cross(Point a, Point b) {
	return imag(conj(a) * b);
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



