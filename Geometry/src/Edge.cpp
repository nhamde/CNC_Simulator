#include "Edge.h"

Geometry::Edge::Edge(Point& p1, Point& p2)
	:start(p1),
	end(p2)
{
}

Geometry::Edge::~Edge()
{
}

bool Geometry::Edge::operator==(Edge& other)
{

	return (((this->start == other.start) || (this->start == other.end)) && ((this->end == other.end) || (this->end == other.start)));
}
