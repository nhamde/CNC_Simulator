#include "PathCreator.h"
#include "Intersector.h"
#include <unordered_map>
#include<stdexcept>
using namespace std;
PathCreator::PathCreator()
{
}

PathCreator::~PathCreator()
{
}

std::vector<std::vector<SurfacePoint>> PathCreator::CreatePath(Triangulation& tri, double y_max, double y_min)
{
	vector<vector<SurfacePoint>> path;
	double y = y_max;
	Intersector in;

	for (; y >= y_min; y = y - 0.1)
	{
		vector<Triangle> yIntersecingTrs;
		for (auto t:tri.Triangles)
		{
			bool intersect = false;

			Point p1 = t.P1();
			Point p2 = t.P2();
			Point p3 = t.P3();

			SurfacePoint sp1 = tri.getRealPoint(p1);
			SurfacePoint sp2 = tri.getRealPoint(p2);
			SurfacePoint sp3 = tri.getRealPoint(p3);

			if ((tri.uniqueNumbers[sp1.Y()] <= y && tri.uniqueNumbers[sp2.Y()] > y) ||
				(tri.uniqueNumbers[sp1.Y()] > y && tri.uniqueNumbers[sp2.Y()] <= y) ||
				(tri.uniqueNumbers[sp1.Y()] <= y && tri.uniqueNumbers[sp3.Y()] > y) ||
				(tri.uniqueNumbers[sp1.Y()] > y && tri.uniqueNumbers[sp3.Y()] <= y) ||
				(tri.uniqueNumbers[sp2.Y()] <= y && tri.uniqueNumbers[sp3.Y()] > y) ||
				(tri.uniqueNumbers[sp2.Y()] > y && tri.uniqueNumbers[sp3.Y()] <= y))
			{ 
				intersect = true; 
			}
			if (intersect)
			{
				yIntersecingTrs.push_back(t);
			}
		}
		vector<Triangle> sortedTriangles = sortTriangles(yIntersecingTrs);
		vector<SurfacePoint> sortedPoints;
		path.push_back(sortedPoints);
	}
	return path;
}

vector<Triangle> PathCreator::sortTriangles(vector<Triangle>& coplanarTriangles)
{
	if (coplanarTriangles.empty()) {
		return {};
	}

	vector<Triangle> sortedLoop;
	sortedLoop.push_back(coplanarTriangles.front());
	coplanarTriangles.erase(coplanarTriangles.begin());

	while (!coplanarTriangles.empty()) {
		bool foundNext = false;

		for (auto it = coplanarTriangles.begin(); it != coplanarTriangles.end(); ++it) {
			if (sortedLoop.back().areAdjacent(*it)) {
				sortedLoop.push_back(*it); 
				coplanarTriangles.erase(it);
				foundNext = true;
				break;
			}
		}

		if (!foundNext) {
			throw runtime_error("Triangles do not form a closed loop!");
		}
	}

	if (!sortedLoop.front().areAdjacent(sortedLoop.back())) {
		throw runtime_error("The sorted triangles do not form a closed loop!");
	}

	return sortedLoop;
}
