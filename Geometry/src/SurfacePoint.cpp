#include "SurfacePoint.h"
#define TOLERANCE 1e-6
using namespace Geometry;

SurfacePoint::SurfacePoint()
	:x(0.0),
	y(0.0),
	z(0.0)
{
}
 
SurfacePoint::SurfacePoint(double _x, double _y, double _z)
	:x(_x),
	y(_y),
	z(_z)
{
}
 
SurfacePoint::~SurfacePoint()
{
}
double SurfacePoint::X()
{
	return x;
}
 
double SurfacePoint::Y()
{
	return y;
}
 
double SurfacePoint::Z()
{
	return z;
}

bool Geometry::SurfacePoint::operator()(const SurfacePoint& other) const
{
	if (x > other.x) return true;
	if (x < other.x) return false;
	return z > other.z;
}

bool SurfacePoint::operator<(const SurfacePoint& other) const
{
	if (x != other.x) return x < other.x;
	if (y != other.y) return y < other.y;
	return z < other.z;
}
 
bool SurfacePoint::operator==(const SurfacePoint& other) const
{
	return fabs(x - other.x) < TOLERANCE && fabs(y - other.y) < TOLERANCE && fabs(z - other.z) < TOLERANCE;
}
bool SurfacePoint::operator!=(const SurfacePoint& other) const
{
	return !(*this == other);
}

std::ostream& Geometry::operator<<(std::ostream& os, const SurfacePoint& sp)
{
	os << "X: " << sp.x << "  Y: " << sp.y << "  Z: " << sp.z << std::endl;
	return os;
}
