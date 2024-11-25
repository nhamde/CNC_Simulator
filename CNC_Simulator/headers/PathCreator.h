#pragma once
#include "Triangulation.h"
#include <vector>
using namespace Geometry;
using namespace std;
class PathCreator
{
private:
	// To sort triangles which are currently at yAxis of the Plane
	vector<Triangle> sortTriangles(vector<Triangle>& triangles);	
	// To sort intersection points to form polyline
	vector<SurfacePoint> sortPoints(vector<Triangle>& sortedTriangles, Triangulation& triangulation, double yAxisOfPlane);
public:
	PathCreator();
	~PathCreator();
	// Creates polylines for each xz plane
	vector<vector<SurfacePoint>> createPath(Triangulation& triangulation, double yMax, double yMin);	
	
};

