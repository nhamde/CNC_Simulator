#include "SurfacePoint.h"
#include<cmath>
#include <unordered_set>
using namespace Geometry;
 
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
 
 
bool SurfacePoint::operator<(const SurfacePoint& other) const
{
	if (x != other.x) {
		return x < other.x;
	}
	if (y != other.y) {
		return y < other.y;
	}
	return z < other.z;
}
 
bool SurfacePoint::operator==(const SurfacePoint& other) const
{
	return x == other.x && y == other.y && z == other.z;
}
bool SurfacePoint::operator!=(const SurfacePoint& other) const
{
	return !(*this == other);
}
 
SurfacePoint SurfacePoint::CrossProduct(SurfacePoint& p)
{
	double crossX = y * p.Z() - z * p.Y();
	double crossY = z * p.X() - x * p.Z();
	double crossZ = x * p.Y() - y * p.X();
 
	return SurfacePoint(crossX, crossY, crossZ);
}
SurfacePoint SurfacePoint::calculateNormal(SurfacePoint& A,  SurfacePoint& B, SurfacePoint& C) {
	double x = B.X() - A.X();
	double y = B.Y() - A.Y();
	double z = B.Z() - A.Z();
	SurfacePoint AB(x, y, z);
	double x1 = C.X() - A.X();
	double y1 = C.Y() - A.Y();
	double z1 = C.Z() - A.Z();
	SurfacePoint AC(x1, y1, z1);
 
	SurfacePoint normal = AB.CrossProduct(AC);
 
	normal.normalize();
 
	return normal;
}
 
void SurfacePoint::normalize() {
	double length = std::sqrt(x * x + y * y + z * z);
	if (length != 0) {
		x /= length;
		y /= length;
		z /= length;
	}
}

namespace std 
{ 
	template <>     
	struct hash<SurfacePoint>
	{ 
		size_t operator()(SurfacePoint& v)
		{ 
			return hash<double>()(v.X()) ^ hash<double>()(v.Y()) ^ hash<double>()(v.Z());
		} 
	}; 
}