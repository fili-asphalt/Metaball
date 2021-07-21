#include "BezierObject.h"

void BezierObject::setControlDots(std::vector<Dot> controlDots_down, std::vector<Dot> controlDots_up) {
    std::vector<Dot> temp;
    this->curves.clear();
    this->curves.reserve(curveDotAmount * 2);

    temp = BezierCurve(controlDots_down, this->curveDotAmount);
    this->curves.insert(this->curves.end(), temp.begin(), temp.end());
    temp = BezierCurve(controlDots_up, this->curveDotAmount);
    this->curves.insert(this->curves.end(), temp.rbegin(), temp.rend());
}

void BezierObject::setControlDotsFromBall(Ball cb1, Ball cb2)
{
    double totalRadius = cb1.getRadius() + cb2.getRadius();
    double distance_centers = sqrt(pow(cb1.getCenter().GetPositionX() - cb2.getCenter().GetPositionX(), 2) + pow(cb1.getCenter().GetPositionY() - cb2.getCenter().GetPositionY(), 2));
    double effective_distance = totalRadius * EFFECTIVE_DISTANCE_OFFSET;
    if (distance_centers >= effective_distance || distance_centers <= abs(cb1.getRadius() - cb2.getRadius()))
    {
        this->curves.clear();
        return;
    }
    
    
    double angle_centersLine = atan2(cb2.getCenter().GetPositionY() - cb1.getCenter().GetPositionY(), cb2.getCenter().GetPositionX() - cb1.getCenter().GetPositionX());
    double spread = acos(( cb1.getRadius() - cb2.getRadius() ) / distance_centers);
    double angel_cb1_touch = 0;
    double angel_cb2_touch = 0;
    if (distance_centers < totalRadius)
    {
        angel_cb1_touch = acos(( pow(cb1.getRadius(), 2) + pow(distance_centers, 2) - pow(cb2.getRadius(), 2) ) / ( 2 * cb1.getRadius() * distance_centers ));
        angel_cb2_touch = acos(( pow(cb2.getRadius(), 2) + pow(distance_centers, 2) - pow(cb1.getRadius(), 2) ) / ( 2 * cb2.getRadius() * distance_centers ));
    }
    else
    {
        angel_cb1_touch = 0;
        angel_cb2_touch = 0;
    }

    double angle_cb1_down = angle_centersLine + ( angel_cb1_touch + ( spread - angel_cb1_touch ) * ANGLE_OFFSET );
    double angle_cb1_up = angle_centersLine - ( angel_cb1_touch + ( spread - angel_cb1_touch ) * ANGLE_OFFSET);
    double angle_cb2_down = angle_centersLine + ( M_PI - angel_cb2_touch - ( M_PI - angel_cb2_touch - spread ) * ANGLE_OFFSET );
    double angle_cb2_up = angle_centersLine - ( M_PI - angel_cb2_touch - ( M_PI - angel_cb2_touch - spread ) * ANGLE_OFFSET );

    Dot dot_cb1_down(cb1.getCenter().GetPositionX() + ( cb1.getRadius() * cos(angle_cb1_down) ), cb1.getCenter().GetPositionY() + ( cb1.getRadius() * sin(angle_cb1_down) ));
    Dot dot_cb1_up(cb1.getCenter().GetPositionX() + ( cb1.getRadius() * cos(angle_cb1_up) ), cb1.getCenter().GetPositionY() + ( cb1.getRadius() * sin(angle_cb1_up) ));
    Dot dot_cb2_down(cb2.getCenter().GetPositionX() + ( cb2.getRadius() * cos(angle_cb2_down) ), cb2.getCenter().GetPositionY() + ( cb2.getRadius() * sin(angle_cb2_down) ));
    Dot dot_cb2_up(cb2.getCenter().GetPositionX() + ( cb2.getRadius() * cos(angle_cb2_up) ), cb2.getCenter().GetPositionY() + ( cb2.getRadius() * sin(angle_cb2_up) ));
    
    double distance_proportional_parameter = sqrt(pow(dot_cb1_down.GetPositionX() - dot_cb2_down.GetPositionX(), 2) + pow(dot_cb1_down.GetPositionY() - dot_cb2_down.GetPositionY(), 2)) / totalRadius;
    double distance_cb1_cut = cb1.getRadius() * distance_proportional_parameter;
    double distance_cb2_cut = cb2.getRadius() * distance_proportional_parameter;

    Dot dot_cb1_cut_down(dot_cb1_down.GetPositionX() + ( distance_cb1_cut * cos(angle_cb1_down - M_PI_2) ), dot_cb1_down.GetPositionY() + ( distance_cb1_cut * sin(angle_cb1_down - M_PI_2) ));
    Dot dot_cb1_cut_up(dot_cb1_up.GetPositionX() + ( distance_cb1_cut * cos(angle_cb1_up + M_PI_2) ), dot_cb1_up.GetPositionY() + ( distance_cb1_cut * sin(angle_cb1_up + M_PI_2) ));
    Dot dot_cb2_cut_down(dot_cb2_down.GetPositionX() + ( distance_cb2_cut * cos(angle_cb2_down + M_PI_2) ), dot_cb2_down.GetPositionY() + ( distance_cb2_cut * sin(angle_cb2_down + M_PI_2) ));
    Dot dot_cb2_cut_up(dot_cb2_up.GetPositionX() + ( distance_cb2_cut * cos(angle_cb2_up - M_PI_2) ), dot_cb2_up.GetPositionY() + ( distance_cb2_cut * sin(angle_cb2_up - M_PI_2) ));

    std::vector<Dot> controlDots_down = { dot_cb1_down ,dot_cb1_cut_down, dot_cb2_cut_down ,dot_cb2_down };
    std::vector<Dot> controlDots_up = { dot_cb1_up ,dot_cb1_cut_up ,dot_cb2_cut_up ,dot_cb2_up };

    this->setControlDots(controlDots_down, controlDots_up);
}

Dot BezierObject::BezierDot(std::vector<Dot>& controlDot, double& numberT) {
    if (controlDot.size() == 2) {
        double distanceX =
            controlDot[1].GetPositionX() - controlDot[0].GetPositionX();
        double distanceY =
            controlDot[1].GetPositionY() - controlDot[0].GetPositionY();
        return Dot(controlDot[0].GetPositionX() + distanceX * numberT,
                   controlDot[0].GetPositionY() + distanceY * numberT);
    } else {
        std::vector<Dot> temp(2);
        std::vector<Dot> subControlDot(controlDot.size() - 1);
        for (int i = 0; i < subControlDot.size(); i++) {
            temp[0] = controlDot[i];
            temp[1] = controlDot[i + 1];
            subControlDot[i] = BezierDot(temp, numberT);
        }
        return BezierDot(subControlDot, numberT);
    }
}

std::vector<Dot> BezierObject::BezierCurve(std::vector<Dot> controlDot,
                                           int dotAmount = 10) {
    std::vector<Dot> answer(dotAmount);
    std::vector<double> numberTList(dotAmount);
    dotAmount--;
    double T1 = 1.0 / (dotAmount);
    for (int i = 1; i < dotAmount; i++) {
        numberTList[i] = T1 + numberTList[i - 1];
    }
    numberTList[dotAmount] = 1;

    for (int i = 0; i <= dotAmount; i++) {
        answer[i] = BezierDot(controlDot, numberTList[i]);
    }
    return answer;
}