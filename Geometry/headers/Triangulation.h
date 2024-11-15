#pragma once
#include "Triangle.h"
#include <vector>
#include "SurfacePoint.h"
namespace Geometry
{
    class Triangle;
    class Triangulation
    {
    public:
        std::vector<double> uniqueNumbers;
        std::vector<Triangle> Triangles;

        Triangulation();
        ~Triangulation();

        SurfacePoint getRealPoint(Point&);
    };
}
