class Dot {
   private:
    double positionX;
    double positionY;

   public:
    Dot() : positionX(0), positionY(0) {}
    Dot(double posX, double posY) : positionX(posX), positionY(posY) {}
    void SetPositionX(double X) { this->positionX = X; }
    void SetPositionY(double Y) { this->positionY = Y; }
    void MoveDot(double moveX, double moveY);
    double GetPositionX() { return this->positionX; }
    double GetPositionY() { return this->positionY; }
};