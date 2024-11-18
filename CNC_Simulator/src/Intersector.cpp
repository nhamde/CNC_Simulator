#include "Intersector.h"
#include "SurfacePoint.h"
using namespace Geometry;

Intersector::Intersector()
{
}

Intersector::~Intersector()
{
}

SurfacePoint* Intersector::intersection(SurfacePoint& p1, SurfacePoint& p2, double y)
{
    if ((p1.Y() - y) * (p2.Y() - y) <= 0) 
    {
        double ty = (y - p1.Y()) / (p2.Y() - p1.Y());
        double x = p1.X() + ty * (p2.X() - p1.X());
        double z = p1.Z() + ty * (p2.Z() - p1.Z());

        return new SurfacePoint(x, y, z);
    }
    return nullptr;
}

vector<SurfacePoint> Intersector::intersect(Triangle& t, double y, const Triangulation& tri)
{
    vector<SurfacePoint> intersectingPts;

    SurfacePoint sp1 = tri.getRealPoint(t.P1());
    SurfacePoint sp2 = tri.getRealPoint(t.P2());
    SurfacePoint sp3 = tri.getRealPoint(t.P3());

    cout << sp1 << sp2 << sp3 << endl;

    SurfacePoint* ptOnEdge1 = intersection(sp1, sp2, y);
    SurfacePoint* ptOnEdge2 = intersection(sp3, sp2, y);
    SurfacePoint* ptOnEdge3 = intersection(sp1, sp3, y);

    auto addUniquePoint = [&intersectingPts](SurfacePoint* pt) 
        {
            if (pt) 
            {
                if (find(intersectingPts.begin(), intersectingPts.end(), *pt) == intersectingPts.end()) 
                {
                    intersectingPts.push_back(*pt);
                }
            }
        };

    addUniquePoint(ptOnEdge1);
    addUniquePoint(ptOnEdge2);
    addUniquePoint(ptOnEdge3);

    return intersectingPts;
}