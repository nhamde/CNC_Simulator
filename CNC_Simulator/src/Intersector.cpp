#include "Intersector.h"
#include "SurfacePoint.h"
using namespace Geometry;

Intersector::Intersector()
{
}

Intersector::~Intersector()
{
}

SurfacePoint* Intersector::isIntersecting(Point& p1, Point& p2, double y, const vector<double>& uniqueValues)
{

    if ((uniqueValues[p1.Y()] - y) * (uniqueValues[p2.Y()] - y) <= 0) {
        double ty = (y - uniqueValues[p1.Y()]) / (uniqueValues[p2.Y()] - uniqueValues[p1.Y()]);
        double x_ = uniqueValues[p1.X()] + ty * (uniqueValues[p2.X()] - uniqueValues[p2.X()]);
        double z_ = uniqueValues[p1.Z()] + ty * (uniqueValues[p2.Z()] - uniqueValues[p2.Z()]);
        return new SurfacePoint(x_, y, z_);
    }
    return nullptr;
}

vector<SurfacePoint> Intersector::intersect( Triangle& t, double y, const Triangulation& tri)
{
    vector<SurfacePoint> intersectingPts;

    Point p1 = t.P1();
    Point p2 = t.P2();
    Point p3 = t.P3();

    SurfacePoint* ptOnEdge1 = isIntersecting(p1, p2, y, tri.uniqueNumbers);
    SurfacePoint* ptOnEdge2 = isIntersecting(p3, p2, y, tri.uniqueNumbers);
    SurfacePoint* ptOnEdge3 = isIntersecting(p1, p3, y, tri.uniqueNumbers);

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