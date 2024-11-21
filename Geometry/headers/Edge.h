#pragma once
#include "Point.h"

namespace Geometry
{
	class Edge
	{
	public:
		Point start;
		Point end;

		Edge(Point& p1, Point& p2);
		~Edge();

		bool operator==(Edge& other);
	};
}