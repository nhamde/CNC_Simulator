#include "SurfacePoint.h"
#include <vector>

class Intersector
{
private:
	//This returns the boundary point where the intersection takes place
	Geometry::SurfacePoint* intersection(const Geometry::SurfacePoint& surfacePoint1, const Geometry::SurfacePoint& surfacePoint2, double yIntersectingPlane) ;

public:
	Intersector();
	~Intersector();
	std::vector<Geometry::SurfacePoint> intersect(const Geometry::SurfacePoint& surfacePoint1, const Geometry::SurfacePoint& surfacePoint2, const Geometry::SurfacePoint& surfacePoint3, double yIntersectingPlane);

};