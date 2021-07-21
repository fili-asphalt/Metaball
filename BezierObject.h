#define _USE_MATH_DEFINES
#define ANGLE_OFFSET 0.5
#define EFFECTIVE_DISTANCE_OFFSET 1.7

#include <cmath>
#include <vector>
#include "Ball.h"


class BezierObject {
   private:
    int curveDotAmount;
    std::vector<Dot> curves;

   public:
    void setCurveDotAmount(int number) { this->curveDotAmount = number; }
    void setControlDots(std::vector<Dot> controlDots_down, std::vector<Dot> controlDots_up);
    void setControlDotsFromBall(Ball cb1, Ball cb2);
    std::vector<Dot> getCurves() { return this->curves; }
    static Dot BezierDot(std::vector<Dot>& controlDot, double& numberT);
    static std::vector<Dot> BezierCurve(std::vector<Dot> controlDot,
                                        int dotAmount);
};