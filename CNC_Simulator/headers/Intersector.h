#include "Triangulation.h"
#include "SurfacePoint.h"
using namespace Geometry;
using namespace std;

class Intersector
{
public:
	Intersector();
	~Intersector();
	SurfacePoint* intersection(SurfacePoint& p1, SurfacePoint& p2, double y);
	vector<SurfacePoint> intersect(Triangle& t, double y, const Triangulation&);

};