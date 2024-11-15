#pragma once
#include "SurfacePoint.h"
using namespace Geometry;

class BoundingBox
{
public:
    double Xmin, Xmax;
    double Ymin, Ymax;
    double Zmin, Zmax;


    std::vector<std::vector<SurfacePoint>> triangles;
    BoundingBox();

    void FindMinMax(double xyz[3]);
    std::vector<std::vector<SurfacePoint>> GenerateTriangles();
};