#include "Triangulation.h"
#include "SurfacePoint.h"
using namespace Geometry;
using namespace std;

class Intersector
{
private:
	//This returns the boundary point where the intersection takes place
	SurfacePoint* intersection(const SurfacePoint& p1, const SurfacePoint& p2, double yValAtXZPlane);

public:
	Intersector();
	~Intersector();
	vector<SurfacePoint> intersect(SurfacePoint& sp1, SurfacePoint& sp2, SurfacePoint& sp3, double y);

};