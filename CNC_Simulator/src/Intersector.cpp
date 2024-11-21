#include "Intersector.h"
#define TOLERANCE 0.0000001
using namespace Geometry;

Intersector::Intersector()
{
}

Intersector::~Intersector()
{
}

SurfacePoint* Intersector::intersection(const SurfacePoint& p1, SurfacePoint& p2, double yValue)
{
    // check if the edge intersects the y-axis of the plane
    if ((p1.Y() - yValue) * (p2.Y() - yValue) <= 0)
    {
        double ty = (yValue - p1.Y()) / (p2.Y() - p1.Y());   // Interpolating Intersection Point
        double x = p1.X() + ty * (p2.X() - p1.X());
        double z = p1.Z() + ty * (p2.Z() - p1.Z());

        double roundedX = std::round(x);
        if (std::abs(roundedX - x) <= TOLERANCE)
        {
            x = roundedX;
        }
        double roundedZ = std::round(z);
        if (std::abs(roundedZ - z) <= TOLERANCE)
        {
            z = roundedZ;
        }
        return new SurfacePoint(x, yValue, z);
    }
    return nullptr; //if no intersection is there then return nullptr
}

vector<SurfacePoint> Intersector::intersect(Triangle& t, double y, const Triangulation& tri)
{
    vector<SurfacePoint> intersectingPts;

    SurfacePoint sp1 = tri.getRealPoint(t.P1());
    SurfacePoint sp2 = tri.getRealPoint(t.P2());
    SurfacePoint sp3 = tri.getRealPoint(t.P3());

    SurfacePoint* ptOnEdge1 = intersection(sp1, sp2, y);
    SurfacePoint* ptOnEdge2 = intersection(sp3, sp2, y);
    SurfacePoint* ptOnEdge3 = intersection(sp1, sp3, y);

    // Lambda function to add a unique intersection point to the result vector
    auto addUniquePoint = [&intersectingPts](SurfacePoint* pt) 
        {
            if (pt) 
            {
                // Check if the point is already in the list to avoid duplicates
                if (find(intersectingPts.begin(), intersectingPts.end(), *pt) == intersectingPts.end()) 
                {
                    intersectingPts.push_back(*pt);
                }
            }
        };

    // Add the intersection points of each edge if they are valid and unique
    addUniquePoint(ptOnEdge1);
    addUniquePoint(ptOnEdge2);
    addUniquePoint(ptOnEdge3);

    //  Deleting pointers to avoid memory leak
    delete ptOnEdge1;
    delete ptOnEdge2;
    delete ptOnEdge3;

    return intersectingPts;
}