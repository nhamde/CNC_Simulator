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
	std::vector<std::vector<SurfacePoint>> CreatePath(Triangulation& tri, double, double);
	std::vector<Triangle> sortTriangles(std::vector<Triangle>&);
};

