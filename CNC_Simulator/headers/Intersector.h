#include "SurfacePoint.h"
#include <vector>

class Intersector
{
private:
	//This returns the boundary point where the intersection takes place
	Geometry::SurfacePoint* intersection(const Geometry::SurfacePoint& p1, const Geometry::SurfacePoint& p2, double yIntersectingPlane);

public:
	Intersector();
	~Intersector();
	std::vector< Geometry::SurfacePoint> intersect(const Geometry::SurfacePoint& p1, const Geometry::SurfacePoint& p2, const Geometry::SurfacePoint& p3, double yIntersectingPlane);

};