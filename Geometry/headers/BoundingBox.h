#pragma once
namespace Geometry 
{
    class BoundingBox {

    private:

        // Bounding box limits
        double  xMin;
        double  yMin;
        double  zMin;
        double  xMax;
        double  yMax;
        double  zMax;

    public:

        BoundingBox();
        ~BoundingBox();

        void setMinMax(double x, double y, double z);
        //std::vector<std::vector<double>> generateVertices() const;
    };
}