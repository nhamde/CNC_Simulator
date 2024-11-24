#include "BoundingBox.h"
using namespace Geometry;
Geometry::BoundingBox::BoundingBox()
{
}
Geometry::BoundingBox::BoundingBox(SurfacePoint& sp1, SurfacePoint& sp2)
    :   lowestBound(sp1),
    highestBound(sp2)
{
}

Geometry::BoundingBox::~BoundingBox()
{
}

std::vector<SurfacePoint> Geometry::BoundingBox::getBounds()
{
    std::vector<SurfacePoint> bounds = { lowestBound, highestBound };
    return bounds;
}

//std::vector<std::vector<double>> BoundingBox::generateVertices() const {
//    std::vector<std::vector<double>> boundingBox;
//    boundingBox.reserve(8); // Reserve space for 8 vertices
//
//    boundingBox.emplace_back(xMin, yMin, zMin);
//    boundingBox.emplace_back(xMin, yMin, zMax);
//    boundingBox.emplace_back(xMin, yMax, zMin);
//    boundingBox.emplace_back(xMin, yMax, zMax);
//    boundingBox.emplace_back(xMax, yMin, zMin);
//    boundingBox.emplace_back(xMax, yMin, zMax);
//    boundingBox.emplace_back(xMax, yMax, zMin);
//    boundingBox.emplace_back(xMax, yMax, zMax);
//
//    return boundingBox;
//}