#pragma once
#include <iostream>

namespace Geometry
{
	class SurfacePoint
	{
	private:
		double x;
		double y;
		double z;
	public:

		SurfacePoint();
		SurfacePoint(double, double, double);
		~SurfacePoint();
		SurfacePoint* next = nullptr;
		double X();
		double Y();
		double Z();
		friend std::ostream& operator<<(std::ostream& os, const SurfacePoint&);
		bool operator==(const SurfacePoint& other) const;
		bool operator!=(const SurfacePoint& other) const;
		bool operator()(const SurfacePoint& other) const;
		bool operator<(const SurfacePoint& other) const;
		friend std::ostream& Geometry::operator<<(std::ostream& os, const SurfacePoint& sp);
	};
}