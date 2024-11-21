#pragma once
#include<vector>
#include"SurfacePoint.h"
#include "Triangulation.h"
using namespace Geometry;
class PathCreator
{
public:
	PathCreator();
	~PathCreator();
	std::vector<std::vector<SurfacePoint>> createPath(Triangulation& tri, double, double);
	std::vector<Triangle> sortTriangles(std::vector<Triangle>&);
	std::vector<SurfacePoint> sortPoints(std::vector<Triangle>&, Triangulation&, double);
};

