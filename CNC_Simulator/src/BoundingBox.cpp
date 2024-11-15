#include <vector>
#include <iostream>
#include <cfloat>
#include "BoundingBox.h"
#include "Point.h"
#include "Triangle.h"
#include "SurfacePoint.h"
#include <cmath>
#include <Intersector.h>
#include <qpainterpath.h>

using namespace Geometry;

BoundingBox::BoundingBox() : Xmin(DBL_MAX), Xmax(DBL_MIN),
Ymin(DBL_MAX), Ymax(DBL_MIN),
Zmin(DBL_MAX), Zmax(DBL_MIN)
{
}

void BoundingBox::FindMinMax(double xyz[3])
{
    Xmin = std::min(Xmin, xyz[0]);
    Xmax = std::max(Xmax, xyz[0]);
    Ymin = std::min(Ymin, xyz[1]);
    Ymax = std::max(Ymax, xyz[1]);
    Zmin = std::min(Zmin, xyz[2]);
    Zmax = std::max(Zmax, xyz[2]);
}

std::vector<std::vector<SurfacePoint>> BoundingBox::GenerateTriangles()
{
    SurfacePoint v0(Xmin, Ymin, Zmin);
    SurfacePoint v1(Xmin, Ymin, Zmax);
    SurfacePoint v2(Xmin, Ymax, Zmin);
    SurfacePoint v3(Xmin, Ymax, Zmax);
    SurfacePoint v4(Xmax, Ymin, Zmin);
    SurfacePoint v5(Xmax, Ymin, Zmax);
    SurfacePoint v6(Xmax, Ymax, Zmin);
    SurfacePoint v7(Xmax, Ymax, Zmax);


    SurfacePoint normal1 = normal1.calculateNormal(v0, v2, v4);
    triangles.push_back({ v0, v2, v4 });
    SurfacePoint normal2 = normal2.calculateNormal(v2, v6, v4);
    triangles.push_back({ v2, v6, v4 });
    SurfacePoint normal3 = normal3.calculateNormal(v1, v3, v5);
    triangles.push_back({ v1, v3, v5 });
    SurfacePoint normal4 = normal4.calculateNormal(v3, v7, v5);
    triangles.push_back({ v3, v7, v5 });
    SurfacePoint normal5 = normal5.calculateNormal(v0, v2, v1);
    triangles.push_back({ v0, v2, v1 });
    SurfacePoint normal6 = normal6.calculateNormal(v2, v3, v1);
    triangles.push_back({ v2, v3, v1 });
    SurfacePoint normal7 = normal7.calculateNormal(v4, v6, v5);
    triangles.push_back({ v4, v6, v5 });
    SurfacePoint normal8 = normal8.calculateNormal(v6, v7, v5);
    triangles.push_back({ v6, v7, v5 });
    SurfacePoint normal9 = normal9.calculateNormal(v2, v6, v3);
    triangles.push_back({ v2, v6, v3 });
    SurfacePoint normal10 = normal10.calculateNormal(v6, v7, v3);
    triangles.push_back({ v6, v7, v3 });
    SurfacePoint normal11 = normal11.calculateNormal(v0, v4, v1);

    triangles.push_back({ v0, v4, v1 });
    SurfacePoint normal12 = normal12.calculateNormal(v4, v5, v1);
    triangles.push_back({ v4, v5, v1 });

    return triangles;
}
