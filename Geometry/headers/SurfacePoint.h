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
		/*struct Node {
			Geometry::SurfacePoint point; 
			Node* next;          

			Node(const Geometry::SurfacePoint& sp) : point(sp), next(nullptr) {}
		};*/

		SurfacePoint(double, double, double);
		~SurfacePoint();
		SurfacePoint* next = nullptr;
		double X();
		double Y();
		double Z();
		bool operator==(const SurfacePoint& other) const;
		bool operator!=(const SurfacePoint& other) const;
		bool operator<(const SurfacePoint& other) const;
		SurfacePoint CrossProduct(SurfacePoint& p);
		SurfacePoint calculateNormal(SurfacePoint& A, SurfacePoint& B, SurfacePoint& C);
		void normalize();
	};
}