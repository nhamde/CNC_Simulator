#include "Triangulation.h"
#include "SurfacePoint.h"
using namespace Geometry;
using namespace std;

class Intersector
{
public:
	Intersector();
	~Intersector();
	SurfacePoint* isIntersecting(Point& p1, Point& p2, double y, const vector<double>& uniqueValues);
	vector<SurfacePoint> intersect( Triangle& t, double y, const Triangulation&);

};