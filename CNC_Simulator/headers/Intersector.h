#include "Triangulation.h"
using namespace Geometry;
using namespace std;

class Intersector
{
private:
	//This returns the boundary point where the intersection takes place
	SurfacePoint* intersection(const SurfacePoint& p1, SurfacePoint& p2, double yValue);

public:
	Intersector();
	~Intersector();
	vector<SurfacePoint> intersect(Triangle& t, double y, const Triangulation&);

};