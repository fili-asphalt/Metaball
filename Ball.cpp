#include "Ball.h"

void Ball::update() {
    double posX, posY;
    this->curve.clear();
    this->curve.reserve(curveDotAmount);
    double angel = M_PI * 2 / curveDotAmount;
    for (int i = 0; i < curveDotAmount; i++) {
        double dotAngle = angel * i;
        posX = this->center.GetPositionX() + radius * std::cos(dotAngle);
        posY = this->center.GetPositionY() + radius * std::sin(dotAngle);
        this->curve.push_back(Dot(posX, posY));
    }
}

void Ball::moveCenter(double moveX, double moveY)
{
    this->center.MoveDot(moveX, moveY);
}