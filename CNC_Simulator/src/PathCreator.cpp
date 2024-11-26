#include "PathCreator.h"
#include "Intersector.h"
#include <unordered_map> 
#include <stdexcept>
using namespace std;
PathCreator::PathCreator()
{
}

PathCreator::~PathCreator()
{
}

vector<vector<SurfacePoint>> PathCreator::createPath(Triangulation& triangulation, double smoothnessFactor)
{
	//extracting yMax and yMin values from bounding box
	double yMax = triangulation.boundingBox.getHighestBound().Y();
	double yMin = triangulation.boundingBox.getLowestBound().Y();
	vector<vector<SurfacePoint>> pathOfMesh;

	for (double currentYAxis = yMax; currentYAxis >= yMin; currentYAxis = currentYAxis - 0.05)
	{
		vector<Triangle> trianglesAtYAxis;
		for (auto triangle : triangulation.Triangles)
		{
			bool intersect = false;

			SurfacePoint sp1 = triangulation.getRealPoint(triangle.P1());
			SurfacePoint sp2 = triangulation.getRealPoint(triangle.P2());
			SurfacePoint sp3 = triangulation.getRealPoint(triangle.P3());

			if ((sp1.Y() <= currentYAxis && sp2.Y() > currentYAxis) ||
				(sp1.Y() > currentYAxis && sp2.Y() <= currentYAxis) ||
				(sp1.Y() <= currentYAxis && sp3.Y() > currentYAxis) ||
				(sp1.Y() > currentYAxis && sp3.Y() <= currentYAxis) ||
				(sp2.Y() <= currentYAxis && sp3.Y() > currentYAxis) ||
				(sp2.Y() > currentYAxis && sp3.Y() <= currentYAxis))
			{
				intersect = true;
			}
			if (intersect)
			{
				trianglesAtYAxis.push_back(triangle);
			}
		}
		vector<Triangle> sortedTriangles;
		try {
			sortedTriangles = sortTriangles(trianglesAtYAxis);
		}
		catch (const runtime_error& e) {
			cerr << "Error: " << e.what() << endl;
			continue;
		}
		vector<SurfacePoint> sortedPoints = sortPoints(sortedTriangles, triangulation, currentYAxis);
		pathOfMesh.push_back(sortedPoints);
	}
	return pathOfMesh;
}

vector<Triangle> PathCreator::sortTriangles(vector<Triangle>& triangles)
{
	if (triangles.empty())
	{
		return {};
	}

	vector<Triangle> sortedTriangles;
	sortedTriangles.push_back(triangles.front());
	triangles.erase(triangles.begin());

	while (!triangles.empty())
	{
		bool foundNext = false;

		for (auto it = triangles.begin(); it != triangles.end(); ++it)
		{
			if (sortedTriangles.back().areAdjacent(*it))
			{
				sortedTriangles.push_back(*it);
				triangles.erase(it);
				foundNext = true;
				break;
			}
		}

		if (!foundNext)
		{
			throw runtime_error("Triangles do not form a closed loop!");
		}
	}

	if (!sortedTriangles.front().areAdjacent(sortedTriangles.back()))
	{
		throw runtime_error("The sorted triangles do not form a closed loop!");
	}

	return sortedTriangles;
}

vector<SurfacePoint> PathCreator::sortPoints(vector<Triangle>& sortedTriangles, Triangulation& triangulation, double yAxisOfPlane)
{
	if (sortedTriangles.empty())
	{
		return {};
	}

	vector<vector<SurfacePoint>> intersectionPtsOfEachTrs;
	vector<SurfacePoint> sortedPoints;
	unordered_map<SurfacePoint, int, SurfacePoint> map;

	Intersector intersector;
	for (auto triangle : sortedTriangles)
	{
		SurfacePoint p1 = triangulation.getRealPoint(triangle.P1());
		SurfacePoint p2 = triangulation.getRealPoint(triangle.P2());
		SurfacePoint p3 = triangulation.getRealPoint(triangle.P3());
		intersectionPtsOfEachTrs.push_back(intersector.triangleXZPlaneIntersection(p1, p2, p3, yAxisOfPlane));
	}

	for (auto intersection : intersectionPtsOfEachTrs)
	{
		for (int i = 0; i < intersection.size(); i++)
		{
			auto pair = map.find(intersection[i]);
			if (pair == map.end())
			{
				sortedPoints.push_back(intersection[i]);
				map[intersection[i]] = sortedPoints.size() - 1;
			}
		}
	}
	return sortedPoints;
}
