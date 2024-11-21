#pragma once
#include "Triangle.h"
#include <vector>
#include "SurfacePoint.h"
#include "BoundingBox.h"
namespace Geometry
{
    class Triangulation
    {
    public:
        std::vector<double> uniqueNumbers;
        std::vector<Triangle> Triangles;

        BoundingBox b;

        Triangulation();
        ~Triangulation();

        SurfacePoint getRealPoint(const Point&) const;
        BoundingBox box;
    };
}