#include "SurfacePoint.h"
#include <vector>

class Intersector
{
private:
	//This returns the boundary point where the intersection takes place
	SurfacePoint* intersection(const Geometry::SurfacePoint& p1, const Geometry::SurfacePoint& p2, double yIntersectingPlane) ;

public:
	Intersector();
	~Intersector();
	std::vector<SurfacePoint> intersect(const Geometry::SurfacePoint& sp1, const Geometry::SurfacePoint& sp2, const Geometry::SurfacePoint& sp3, double yIntersectingPlane);

};