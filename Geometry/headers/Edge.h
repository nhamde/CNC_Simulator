#pragma once
#include "Point.h"

namespace Geometry
{
	class Edge
	{
	private:
		bool operator==(Edge&);
	public:
		Point start;
		Point end;

		Edge(Point&, Point&);
		~Edge();

	};
}