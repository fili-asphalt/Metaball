#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include "Dot.h"

class Ball {
   private:
    Dot center;
    double radius;
    int curveDotAmount;
    std::vector<Dot> curve;

   public:
    Ball() : radius(0), curveDotAmount(20), center(Dot()) {}
    void setCenter(Dot newCenter) { this->center = newCenter; }
    void setRadius(double newRadius) { this->radius = newRadius; }
    void setCurveDotAmount(int newAmount) { this->curveDotAmount = newAmount; }
    void moveCenter(double moveX, double moveY);
    void update();
    Dot getCenter() { return this->center; }
    double getRadius() { return this->radius; }
    std::vector<Dot> getCurve() { return this->curve; }
};