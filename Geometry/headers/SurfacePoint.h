#pragma once

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
		bool operator==(const SurfacePoint& other) const;
		bool operator!=(const SurfacePoint& other) const;
		bool operator<(const SurfacePoint& other) const;
		bool operator()(const SurfacePoint& other) const;
	};
}