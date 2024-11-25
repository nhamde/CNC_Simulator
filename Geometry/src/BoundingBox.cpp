#include "BoundingBox.h"
using namespace Geometry;
BoundingBox::BoundingBox()
{
}
BoundingBox::BoundingBox(SurfacePoint& sp1, SurfacePoint& sp2)
    :   lowestBound(sp1),
    highestBound(sp2)
{
}

BoundingBox::~BoundingBox()
{
}

std::vector<SurfacePoint> BoundingBox::getBounds()
{
    SurfacePoint TBL = SurfacePoint(lowestBound.X(), highestBound.Y(), lowestBound.Z());
    SurfacePoint TBR = SurfacePoint(highestBound.X(), highestBound.Y(), lowestBound.Z());
    SurfacePoint TFL = SurfacePoint(lowestBound.X(), highestBound.Y(), highestBound.Z());
    SurfacePoint TFR = SurfacePoint(highestBound.X(), highestBound.Y(), highestBound.Z());
    SurfacePoint BBL = SurfacePoint(lowestBound.X(), lowestBound.Y(), lowestBound.Z());
    SurfacePoint BBR = SurfacePoint(highestBound.X(), lowestBound.Y(), lowestBound.Z());
    SurfacePoint BFL = SurfacePoint(lowestBound.X(), lowestBound.Y(), highestBound.Z());
    SurfacePoint BFR = SurfacePoint(highestBound.X(), lowestBound.Y(), highestBound.Z());

    std::vector<SurfacePoint> bounds = { TBL, TBR, TFL, TFR, BBL, BBR, BFL, BFR };
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