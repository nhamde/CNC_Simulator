#include "Intersector.h"
#define TOLERANCE 0.0000001
using namespace Geometry;

Intersector::Intersector()
{
}

Intersector::~Intersector()
{
}

SurfacePoint* Intersector::intersection(const SurfacePoint& p1, const SurfacePoint& p2, double yValAtXZPlane)
{
    // check if the edge intersects the y-axis of the plane
    if ((p1.Y() - yValAtXZPlane) * (p2.Y() - yValAtXZPlane) <= 0)
    {
        double interpolatingConst = (yValAtXZPlane - p1.Y()) / (p2.Y() - p1.Y());   // Interpolating Intersection Point
        double x = p1.X() + interpolatingConst * (p2.X() - p1.X());
        double z = p1.Z() + interpolatingConst * (p2.Z() - p1.Z());

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
        return new SurfacePoint(x, yValAtXZPlane, z);
    }
    return nullptr; //if no intersection is there then return nullptr
}

vector<SurfacePoint> Intersector::intersect(SurfacePoint& sp1, SurfacePoint& sp2, SurfacePoint& sp3, double yValAtXZPlane)
{
    vector<SurfacePoint> intersectingPts;

    SurfacePoint* ptOnEdge1 = intersection(sp1, sp2, yValAtXZPlane);
    SurfacePoint* ptOnEdge2 = intersection(sp3, sp2, yValAtXZPlane);
    SurfacePoint* ptOnEdge3 = intersection(sp1, sp3, yValAtXZPlane);

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