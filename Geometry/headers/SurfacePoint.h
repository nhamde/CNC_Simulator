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
		double X() const;
		double Y() const;
		double Z() const;
		bool operator==(const SurfacePoint& other) const;
		bool operator()(const SurfacePoint& other) const;
	};
}