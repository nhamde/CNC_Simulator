#include "BoundingBox.h"
#include <algorithm>.
using namespace Geometry;
Geometry::BoundingBox::BoundingBox()
{
}

Geometry::BoundingBox::~BoundingBox()
{
}

void Geometry::BoundingBox::findMinMax(double x, double y, double z)
{
    xMin = std::min(xMin, x);
    yMin = std::min(yMin, y);
    zMin = std::min(zMin, z);

    xMax = std::max(xMax, x);
    yMax = std::max(yMax, y);
    zMax = std::max(zMax, z);
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